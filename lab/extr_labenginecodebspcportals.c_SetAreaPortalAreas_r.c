#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ planenum; scalar_t__ contents; int /*<<< orphan*/  area; TYPE_4__* brushlist; struct TYPE_8__** children; } ;
typedef  TYPE_2__ node_t ;
struct TYPE_9__ {int /*<<< orphan*/ * portalareas; } ;
typedef  TYPE_3__ entity_t ;
struct TYPE_10__ {TYPE_1__* original; } ;
typedef  TYPE_4__ bspbrush_t ;
struct TYPE_7__ {size_t entitynum; } ;

/* Variables and functions */
 scalar_t__ CONTENTS_AREAPORTAL ; 
 int /*<<< orphan*/  Log_Print (char*,size_t) ; 
 scalar_t__ PLANENUM_LEAF ; 
 TYPE_3__* entities ; 

void SetAreaPortalAreas_r (node_t *node)
{
	bspbrush_t	*b;
	entity_t	*e;

	if (node->planenum != PLANENUM_LEAF)
	{
		SetAreaPortalAreas_r (node->children[0]);
		SetAreaPortalAreas_r (node->children[1]);
		return;
	} //end if

	if (node->contents == CONTENTS_AREAPORTAL)
	{
		if (node->area)
			return;		// allready set

		b = node->brushlist;
		e = &entities[b->original->entitynum];
		node->area = e->portalareas[0];
		if (!e->portalareas[1])
		{
			Log_Print("WARNING: areaportal entity %i doesn't touch two areas\n", b->original->entitynum);
			return;
		} //end if
	} //end if
}