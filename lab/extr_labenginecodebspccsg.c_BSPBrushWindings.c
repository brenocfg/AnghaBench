#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
struct TYPE_7__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ plane_t ;
struct TYPE_8__ {int numsides; TYPE_1__* sides; } ;
typedef  TYPE_3__ bspbrush_t ;
struct TYPE_6__ {size_t planenum; int /*<<< orphan*/ * winding; } ;

/* Variables and functions */
 int /*<<< orphan*/ * BaseWindingForPlane (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ChopWindingInPlace (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* mapplanes ; 

void BSPBrushWindings(bspbrush_t *brush)
{
	int i, j;
	winding_t *w;
	plane_t *plane;

	for (i = 0; i < brush->numsides; i++)
	{
		plane = &mapplanes[brush->sides[i].planenum];
		w = BaseWindingForPlane(plane->normal, plane->dist);
		for (j = 0; j < brush->numsides && w; j++)
		{
			if (i == j) continue;
			plane = &mapplanes[brush->sides[j].planenum^1];
			ChopWindingInPlace(&w, plane->normal, plane->dist, 0); //CLIP_EPSILON);
		} //end for
		brush->sides[i].winding = w;
	} //end for
}