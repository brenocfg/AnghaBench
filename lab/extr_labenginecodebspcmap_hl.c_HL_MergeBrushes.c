#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ side; struct TYPE_8__* next; } ;
typedef  TYPE_1__ bspbrush_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBrush (TYPE_1__*) ; 
 TYPE_1__* TryMergeBrushes (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 

bspbrush_t *HL_MergeBrushes(bspbrush_t *brushlist, int modelnum)
{
	int nummerges, merged;
	bspbrush_t *b1, *b2, *tail, *newbrush, *newbrushlist;
	bspbrush_t *lastb2;

	if (!brushlist) return NULL;

	if (!modelnum) qprintf("%5d brushes merged", nummerges = 0);
	do
	{
		for (tail = brushlist; tail; tail = tail->next)
		{
			if (!tail->next) break;
		} //end for
		merged = 0;
		newbrushlist = NULL;
		for (b1 = brushlist; b1; b1 = brushlist)
		{
			lastb2 = b1;
			for (b2 = b1->next; b2; b2 = b2->next)
			{
				//can't merge brushes with different contents
				if (b1->side != b2->side) newbrush = NULL;
				else newbrush = TryMergeBrushes(b1, b2);
				//if a merged brush is created
				if (newbrush)
				{
					//copy the brush contents
					newbrush->side = b1->side;
					//add the new brush to the end of the list
					tail->next = newbrush;
					//remove the second brush from the list
					lastb2->next = b2->next;
					//remove the first brush from the list
					brushlist = brushlist->next;
					//free the merged brushes
					FreeBrush(b1);
					FreeBrush(b2);
					//get a new tail brush
					for (tail = brushlist; tail; tail = tail->next)
					{
						if (!tail->next) break;
					} //end for
					merged++;
					if (!modelnum) qprintf("\r%5d", nummerges++);
					break;
				} //end if
				lastb2 = b2;
			} //end for
			//if b1 can't be merged with any of the other brushes
			if (!b2)
			{
				brushlist = brushlist->next;
				//keep b1
				b1->next = newbrushlist;
				newbrushlist = b1;
			} //end else
		} //end for
		brushlist = newbrushlist;
	} while(merged);
	if (!modelnum) qprintf("\n");
	return newbrushlist;
}