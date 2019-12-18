#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_7__ {int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; TYPE_2__* headnode; } ;
typedef  TYPE_1__ tree_t ;
struct TYPE_8__ {int /*<<< orphan*/  contents; int /*<<< orphan*/  planenum; } ;
typedef  TYPE_2__ node_t ;
typedef  int /*<<< orphan*/  bspbrush_t ;

/* Variables and functions */
 TYPE_2__* AllocNode () ; 
 TYPE_1__* BrushBSP (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  CONTENTS_SOLID ; 
 int /*<<< orphan*/ * ChopBrushes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBrushList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MakeBspBrushList (int,int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  PLANENUM_LEAF ; 
 int /*<<< orphan*/  ResetBrushBSP () ; 
 TYPE_1__* Tree_Alloc () ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ cancelconversion ; 
 scalar_t__* map_maxs ; 
 scalar_t__* map_mins ; 
 int /*<<< orphan*/  nocsg ; 

tree_t *ProcessWorldBrushes(int brush_start, int brush_end)
{
	bspbrush_t *brushes;
	tree_t *tree;
	node_t *node;
	vec3_t mins, maxs;

	//take the whole world
	mins[0] = map_mins[0] - 8;
	mins[1] = map_mins[1] - 8;
	mins[2] = map_mins[2] - 8;

	maxs[0] = map_maxs[0] + 8;
	maxs[1] = map_maxs[1] + 8;
	maxs[2] = map_maxs[2] + 8;

	//reset the brush bsp
	ResetBrushBSP();

	// the makelist and chopbrushes could be cached between the passes...

	//create a list with brushes that are within the given mins/maxs
	//some brushes will be cut and only the part that falls within the
	//mins/maxs will be in the bush list
	brushes = MakeBspBrushList(brush_start, brush_end, mins, maxs);
	//

	if (!brushes)
	{
		node = AllocNode ();
		node->planenum = PLANENUM_LEAF;
		node->contents = CONTENTS_SOLID;

		tree = Tree_Alloc();
		tree->headnode = node;
		VectorCopy(mins, tree->mins);
		VectorCopy(maxs, tree->maxs);
	} //end if
	else
	{
		//Carves any intersecting solid brushes into the minimum number
		//of non-intersecting brushes. 
		if (!nocsg)
		{
			brushes = ChopBrushes(brushes);
			/*
			if (create_aas)
			{
				brushes = MergeBrushes(brushes);
			} //end if*/
		} //end if
		//if the conversion is cancelled
		if (cancelconversion)
		{
			FreeBrushList(brushes);
			return NULL;
		} //end if
		//create the actual bsp tree
		tree = BrushBSP(brushes, mins, maxs);
	} //end else
	//return the tree
	return tree;
}