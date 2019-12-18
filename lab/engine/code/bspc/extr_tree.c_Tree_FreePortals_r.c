#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* winding; TYPE_2__** nodes; struct TYPE_8__** next; } ;
typedef  TYPE_1__ portal_t ;
struct TYPE_9__ {scalar_t__ planenum; TYPE_1__* portals; struct TYPE_9__** children; } ;
typedef  TYPE_2__ node_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreePortal (TYPE_1__*) ; 
 scalar_t__ MemorySize (TYPE_1__*) ; 
 scalar_t__ PLANENUM_LEAF ; 
 int /*<<< orphan*/  RemovePortalFromNode (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  freedtreemem ; 

void Tree_FreePortals_r (node_t *node)
{
	portal_t	*p, *nextp;
	int			s;

	// free children
	if (node->planenum != PLANENUM_LEAF)
	{
		Tree_FreePortals_r(node->children[0]);
		Tree_FreePortals_r(node->children[1]);
	}

	// free portals
	for (p = node->portals; p; p = nextp)
	{
		s = (p->nodes[1] == node);
		nextp = p->next[s];

		RemovePortalFromNode (p, p->nodes[!s]);
#ifdef ME
		if (p->winding) freedtreemem += MemorySize(p->winding);
		freedtreemem += MemorySize(p);
#endif //ME
		FreePortal(p);
	}
	node->portals = NULL;
}