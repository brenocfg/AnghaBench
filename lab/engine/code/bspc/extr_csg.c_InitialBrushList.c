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
struct TYPE_8__ {int numsides; TYPE_1__* sides; struct TYPE_8__* next; } ;
typedef  TYPE_2__ bspbrush_t ;
struct TYPE_7__ {int flags; struct TYPE_7__* original; } ;

/* Variables and functions */
 TYPE_2__* CopyBrush (TYPE_2__*) ; 
 int SFL_VISIBLE ; 

bspbrush_t *InitialBrushList (bspbrush_t *list)
{
	bspbrush_t *b;
	bspbrush_t	*out, *newb;
	int			i;

	// only return brushes that have visible faces
	out = NULL;
	for (b=list ; b ; b=b->next)
	{
#if 0
		for (i=0 ; i<b->numsides ; i++)
			if (b->sides[i].flags & SFL_VISIBLE)
				break;
		if (i == b->numsides)
			continue;
#endif
		newb = CopyBrush (b);
		newb->next = out;
		out = newb;

		// clear visible, so it must be set by MarkVisibleFaces_r
		// to be used in the optimized list
		for (i=0 ; i<b->numsides ; i++)
		{
			newb->sides[i].original = &b->sides[i];
//			newb->sides[i].visible = true;
			b->sides[i].flags &= ~SFL_VISIBLE;
		}
	}

	return out;
}