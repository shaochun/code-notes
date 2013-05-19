//==========================================================================================
//RENAME SELECTED NODES
//==========================================================================================
string $sel[] = `ls -sl -tr`;
select -cl;
select $sel;
string $newName = $sel[0];
renameSelectionList($newName);

//==========================================================================================
//HEIRARCHYSELECT
//==========================================================================================
string $sel[] = `ls -sl`;
int $size = `size($sel)`;
for($i = 0; $i < $size; $i++)
{
	select -add -hi $sel[$i];
	select -d $sel[$i];
}
string $selection[] = `ls -sl -tr`;
select -cl;
select $selection;

//==========================================================================================
//GROUP SELECTED NODES UNDER THEIR OWN WORLD GROUP
//==========================================================================================
string $sel[] = `ls -sl`;
select -hi $sel[0];
select -d $sel[0];
string $toMove[] = `ls -sl -tr`;
select -cl;
select $toMove;

for($i = 0; $i < size($toMove); $i++)
{
    string $gName = $toMove[$i] + "g";
    group -em -name $gName -parent $sel[0]; //create an empty(-em) group, parent under parentName
    parent $toMove[$i] $gName;	//parent obj1 to obj2	
}

//==========================================================================================
//DELETE CHILDREN
//==========================================================================================
string $sel[] = `ls -sl`;
select -hi $sel[0];
select -d $sel[0];

string $newSel[] = `ls -sl -tr`;
delete $newSel;

//==========================================================================================
//IMPORT MULTIPLE FILES
//==========================================================================================
string $myFiles[] = `fileDialog2 -fileMode 4`;
int $fileno = size($myFiles);

for($i = 0; $i < $fileno; $i++)
{
    print($myFiles[$i] + " imported\n");
    file -import $myFiles[$i];
}
//==========================================================================================
//EXPORT MULTIPLE FILES
//==========================================================================================
string $loc = `workspace -rd -q`;
string $parent[] = `ls -sl -tr`;
string $sel[] = `listRelatives -c $parent[0]`;

for($i = 0; $i < size($sel); $i++)
{
    select -cl;
    select $sel[$i];
    file -force -options "" -typ "OBJexport" -es ($loc + $sel[$i] + ".obj");
}
print(">>> " + $loc + " <<<");

//==========================================================================================
//CONVERT ARRAY OF 16 FLOATS TO MATRIX
//==========================================================================================
proc matrix ArrayToMatrix (float $values[])
{
	matrix $mat[4][4];
	int $index = 0;
	for(int $r = 0; $r < 4; $r++)
	{
		for(int $c = 0; $c < 4; $c++)
		{
			$mat[$r][$c] = $values[$index];
			$index++;
		}
	}
	return $mat;
}

//==========================================================================================
//AUTO LOAD A PLUGIN
//==========================================================================================
loadPlugin "C:\\Users\\Tani\\Desktop\\MayaPluginBase\\Debug\\mayaplugin.mll";
print("LOADED!");