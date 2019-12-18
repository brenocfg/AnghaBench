#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
struct TYPE_8__ {scalar_t__ dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ q3_dplane_t ;
struct TYPE_9__ {size_t planeNum; } ;
typedef  TYPE_2__ q3_dbrushside_t ;
struct TYPE_10__ {int numSides; int firstSide; } ;
typedef  TYPE_3__ q3_dbrush_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BaseWindingForPlane (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ChopWindingInPlace (int /*<<< orphan*/ **,int /*<<< orphan*/ ,scalar_t__,double) ; 
 double DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double fabs (scalar_t__) ; 
 TYPE_2__* q3_dbrushsides ; 
 TYPE_1__* q3_dplanes ; 

winding_t *Q3_BrushSideWinding(q3_dbrush_t *brush, q3_dbrushside_t *baseside)
{
	int i;
	q3_dplane_t *baseplane, *plane;
	winding_t *w;
	q3_dbrushside_t *side;
	
	//create a winding for the brush side with the given planenumber
	baseplane = &q3_dplanes[baseside->planeNum];
	w = BaseWindingForPlane(baseplane->normal, baseplane->dist);
	for (i = 0; i < brush->numSides && w; i++)
	{
		side = &q3_dbrushsides[brush->firstSide + i];
		//don't chop with the base plane
		if (side->planeNum == baseside->planeNum) continue;
		//also don't use planes that are almost equal
		plane = &q3_dplanes[side->planeNum];
		if (DotProduct(baseplane->normal, plane->normal) > 0.999
				&& fabs(baseplane->dist - plane->dist) < 0.01) continue;
		//
		plane = &q3_dplanes[side->planeNum^1];
		ChopWindingInPlace(&w, plane->normal, plane->dist, -0.1); //CLIP_EPSILON);
	} //end for
	return w;
}