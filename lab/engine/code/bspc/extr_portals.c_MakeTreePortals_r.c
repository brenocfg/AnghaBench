#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ planenum; struct TYPE_6__** children; int /*<<< orphan*/ * maxs; int /*<<< orphan*/ * mins; } ;
typedef  TYPE_1__ node_t ;

/* Variables and functions */
 int /*<<< orphan*/  CalcNodeBounds (TYPE_1__*) ; 
 int /*<<< orphan*/  Log_Print (char*) ; 
 int /*<<< orphan*/  MAX_MAP_BOUNDS ; 
 int /*<<< orphan*/  MakeNodePortal (TYPE_1__*) ; 
 scalar_t__ PLANENUM_LEAF ; 
 int /*<<< orphan*/  SplitNodePortals (TYPE_1__*) ; 
 int /*<<< orphan*/  c_numportalizednodes ; 
 scalar_t__ cancelconversion ; 
 int /*<<< orphan*/  qprintf (char*,int /*<<< orphan*/ ) ; 

void MakeTreePortals_r (node_t *node)
{
	int		i;

#ifdef ME
	qprintf("\r%6d", ++c_numportalizednodes);
	if (cancelconversion) return;
#endif //ME

	CalcNodeBounds (node);
	if (node->mins[0] >= node->maxs[0])
	{
		Log_Print("WARNING: node without a volume\n");
	}

	for (i=0 ; i<3 ; i++)
	{
		if (node->mins[i] < -MAX_MAP_BOUNDS || node->maxs[i] > MAX_MAP_BOUNDS)
		{
			Log_Print("WARNING: node with unbounded volume\n");
			break;
		}
	}
	if (node->planenum == PLANENUM_LEAF)
		return;

	MakeNodePortal (node);
	SplitNodePortals (node);

	MakeTreePortals_r (node->children[0]);
	MakeTreePortals_r (node->children[1]);
}