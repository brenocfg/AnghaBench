#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
struct TYPE_6__ {scalar_t__* mins; scalar_t__* maxs; int numsides; TYPE_1__* sides; } ;
typedef  TYPE_2__ bspbrush_t ;
struct TYPE_5__ {int planenum; } ;

/* Variables and functions */

qboolean BrushesDisjoint (bspbrush_t *a, bspbrush_t *b)
{
	int		i, j;

	// check bounding boxes
	for (i=0 ; i<3 ; i++)
		if (a->mins[i] >= b->maxs[i]
		|| a->maxs[i] <= b->mins[i])
			return true;	// bounding boxes don't overlap

	// check for opposing planes
	for (i=0 ; i<a->numsides ; i++)
	{
		for (j=0 ; j<b->numsides ; j++)
		{
			if (a->sides[i].planenum ==
			(b->sides[j].planenum^1) )
				return true;	// opposite planes, so not touching
		}
	}

	return false;	// might intersect
}