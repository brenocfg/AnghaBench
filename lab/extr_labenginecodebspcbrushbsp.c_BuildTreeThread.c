#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int planenum; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_12__ {int contents; int planenum; struct TYPE_12__** children; int /*<<< orphan*/ * volume; int /*<<< orphan*/ * brushlist; struct TYPE_12__* parent; TYPE_1__* side; } ;
typedef  TYPE_2__ node_t ;
typedef  int /*<<< orphan*/  bspbrush_t ;

/* Variables and functions */
 int /*<<< orphan*/  AddNodeToList (TYPE_2__*) ; 
 TYPE_2__* AllocNode () ; 
 int CONTENTS_SOLID ; 
 int /*<<< orphan*/  CheckBrushLists (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DrawBrushList (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  FreeBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBrushList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IncreaseNodeCounter () ; 
 int /*<<< orphan*/  LeafNode (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* NextNodeFromList () ; 
 int /*<<< orphan*/  RemoveThread (int) ; 
 TYPE_1__* SelectSplitSide (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SplitBrush (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SplitBrushList (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int WindingMemory () ; 
 int c_brushmemory ; 
 int c_nodememory ; 
 int /*<<< orphan*/  c_nodes ; 
 int c_peak_totalbspmemory ; 
 int /*<<< orphan*/  c_solidleafnodes ; 
 scalar_t__ cancelconversion ; 
 scalar_t__ create_aas ; 
 scalar_t__ drawflag ; 
 int numthreads ; 

void BuildTreeThread(int threadid)
{
	node_t *newnode, *node;
	side_t *bestside;
	int i, totalmem;
	bspbrush_t *brushes;

	for (node = NextNodeFromList(); node; )
	{
		//if the nodelist isn't empty try to add another thread
		//if (NodeListSize() > 10) AddThread(BuildTreeThread);
		//display the number of nodes processed so far
		if (numthreads == 1)
			IncreaseNodeCounter();

		brushes = node->brushlist;

		if (numthreads == 1)
		{
			totalmem = WindingMemory() + c_nodememory + c_brushmemory;
			if (totalmem > c_peak_totalbspmemory)
			{
				c_peak_totalbspmemory = totalmem;
			} //end if
			c_nodes++;
		} //endif

		if (drawflag)
		{
			DrawBrushList(brushes, node);
		} //end if

		if (cancelconversion)
		{
			bestside = NULL;
		} //end if
		else
		{
			// find the best plane to use as a splitter
			bestside = SelectSplitSide(brushes, node);
		} //end else
		//if there's no split side left
		if (!bestside)
		{
			//create a leaf out of the node
			LeafNode(node, brushes);
			if (node->contents & CONTENTS_SOLID) c_solidleafnodes++;
			if (create_aas)
			{
				//free up memory!!!
				FreeBrushList(node->brushlist);
				node->brushlist = NULL;
			} //end if
			//free the node volume brush (it is not used anymore)
			if (node->volume)
			{
				FreeBrush(node->volume);
				node->volume = NULL;
			} //end if
			node = NextNodeFromList();
			continue;
		} //end if

		// this is a splitplane node
		node->side = bestside;
		node->planenum = bestside->planenum & ~1;	//always use front facing

		//allocate children
		for (i = 0; i < 2; i++)
		{
			newnode = AllocNode();
			newnode->parent = node;
			node->children[i] = newnode;
		} //end for

		//split the brush list in two for both children
		SplitBrushList(brushes, node, &node->children[0]->brushlist, &node->children[1]->brushlist);

		CheckBrushLists(node->children[0]->brushlist, node->children[1]->brushlist);
		//free the old brush list
		FreeBrushList(brushes);
		node->brushlist = NULL;

		//split the volume brush of the node for the children
		SplitBrush(node->volume, node->planenum, &node->children[0]->volume,
								&node->children[1]->volume);

		if (!node->children[0]->volume || !node->children[1]->volume)
		{
			Error("child without volume brush");
		} //end if

		//free the volume brush
		if (node->volume)
		{
			FreeBrush(node->volume);
			node->volume = NULL;
		} //end if
		//add both children to the node list
		//AddNodeToList(node->children[0]);
		AddNodeToList(node->children[1]);
		node = node->children[0];
	} //end while
	RemoveThread(threadid);
}