#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ bspbrush_t ;

/* Variables and functions */

bspbrush_t *AddBrushListToTail (bspbrush_t *list, bspbrush_t *tail)
{
	bspbrush_t	*walk, *next;

	for (walk=list ; walk ; walk=next)
	{	// add to end of list
		next = walk->next;
		walk->next = NULL;
		tail->next = walk;
		tail = walk;
	} //end for
	return tail;
}