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
struct TYPE_8__ {int numsides; struct TYPE_8__* next; TYPE_1__* sides; } ;
typedef  TYPE_2__ bspbrush_t ;
struct TYPE_7__ {int flags; } ;

/* Variables and functions */
 TYPE_2__* CopyBrush (TYPE_2__*) ; 
 int SFL_VISIBLE ; 

bspbrush_t *OptimizedBrushList (bspbrush_t *list)
{
	bspbrush_t *b;
	bspbrush_t	*out, *newb;
	int			i;

	// only return brushes that have visible faces
	out = NULL;
	for (b=list ; b ; b=b->next)
	{
		for (i=0 ; i<b->numsides ; i++)
			if (b->sides[i].flags & SFL_VISIBLE)
				break;
		if (i == b->numsides)
			continue;
		newb = CopyBrush (b);
		newb->next = out;
		out = newb;
	} //end for

//	WriteBrushList ("vis.gl", out, true);
	return out;
}