#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* winding; TYPE_3__** nodes; struct TYPE_6__** next; } ;
typedef  TYPE_2__ portal_t ;
struct TYPE_7__ {int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; TYPE_2__* portals; } ;
typedef  TYPE_3__ node_t ;
struct TYPE_5__ {int numpoints; int /*<<< orphan*/ * p; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void CalcNodeBounds (node_t *node)
{
	portal_t	*p;
	int			s;
	int			i;

	// calc mins/maxs for both leaves and nodes
	ClearBounds (node->mins, node->maxs);
	for (p = node->portals ; p ; p = p->next[s])	
	{
		s = (p->nodes[1] == node);
		for (i=0 ; i<p->winding->numpoints ; i++)
			AddPointToBounds (p->winding->p[i], node->mins, node->maxs);
	}
}