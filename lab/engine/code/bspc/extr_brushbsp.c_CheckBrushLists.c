#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ bspbrush_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void CheckBrushLists(bspbrush_t *brushlist1, bspbrush_t *brushlist2)
{
	bspbrush_t *brush1, *brush2;

	for (brush1 = brushlist1; brush1; brush1 = brush1->next)
	{
		for (brush2 = brushlist2; brush2; brush2 = brush2->next)
		{
			assert(brush1 != brush2);
		} //end for
	} //end for
}