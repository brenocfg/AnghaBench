#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* next; TYPE_1__* original; } ;
typedef  TYPE_2__ bspbrush_t ;
struct TYPE_9__ {scalar_t__ contents; scalar_t__ expansionbbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBrush (TYPE_2__*) ; 
 TYPE_2__* TryMergeBrushes (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 

bspbrush_t *MergeBrushes(bspbrush_t *brushlist)
{
	int nummerges, merged;
	bspbrush_t *b1, *b2, *tail, *newbrush, *newbrushlist;
	bspbrush_t *lastb2;

	if (!brushlist) return NULL;

	qprintf("%5d brushes merged", nummerges = 0);
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
				//if the brushes don't have the same contents
				if (b1->original->contents != b2->original->contents ||
					b1->original->expansionbbox != b2->original->expansionbbox) newbrush = NULL;
				else newbrush = TryMergeBrushes(b1, b2);
				if (newbrush)
				{
					tail->next = newbrush;
					lastb2->next = b2->next;
					brushlist = brushlist->next;
					FreeBrush(b1);
					FreeBrush(b2);
					for (tail = brushlist; tail; tail = tail->next)
					{
						if (!tail->next) break;
					} //end for
					merged++;
					qprintf("\r%5d", nummerges++);
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
	qprintf("\n");
	return newbrushlist;
}