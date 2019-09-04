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
struct TYPE_5__ {int numpoints; scalar_t__** p; } ;
typedef  TYPE_1__ winding_t ;
typedef  scalar_t__* vec3_t ;
struct TYPE_6__ {TYPE_1__* winding; } ;
typedef  TYPE_2__ side_t ;
struct TYPE_7__ {int numsides; TYPE_2__* sides; } ;
typedef  TYPE_3__ bspbrush_t ;

/* Variables and functions */

int BrushOutOfBounds(bspbrush_t *brush, vec3_t mins, vec3_t maxs, float epsilon)
{
	int i, j, n;
	winding_t *w;
	side_t *side;

	for (i = 0; i < brush->numsides; i++)
	{
		side = &brush->sides[i];
		w = side->winding;
		for (j = 0; j < w->numpoints; j++)
		{
			for (n = 0; n < 3; n++)
			{
				if (w->p[j][n] < (mins[n] + epsilon) || w->p[j][n] > (maxs[n] - epsilon)) return true;
			} //end for
		} //end for
	} //end for
	return false;
}