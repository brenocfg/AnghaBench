#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ plane_t ;
struct TYPE_9__ {int numsides; int /*<<< orphan*/ * maxs; int /*<<< orphan*/ * mins; TYPE_1__* sides; } ;
typedef  TYPE_3__ bspbrush_t ;
struct TYPE_7__ {size_t planenum; int /*<<< orphan*/  winding; } ;

/* Variables and functions */
 int /*<<< orphan*/  BoundBrush (TYPE_3__*) ; 
 int /*<<< orphan*/  Log_Print (char*,...) ; 
 int /*<<< orphan*/  MAX_MAP_BOUNDS ; 
 scalar_t__ WindingsNonConvex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* mapplanes ; 

void CheckBSPBrush(bspbrush_t *brush)
{
	int i, j;
	plane_t *plane1, *plane2;

	//check if the brush is convex... flipped planes make a brush non-convex
	for (i = 0; i < brush->numsides; i++)
	{
		for (j = 0; j < brush->numsides; j++)
		{
			if (i == j) continue;
			plane1 = &mapplanes[brush->sides[i].planenum];
			plane2 = &mapplanes[brush->sides[j].planenum];
			//
			if (WindingsNonConvex(brush->sides[i].winding,
									brush->sides[j].winding,
									plane1->normal, plane2->normal,
									plane1->dist, plane2->dist))
			{
				Log_Print("non convex brush");
				break;
			} //end if
		} //end for
	} //end for
	BoundBrush(brush);
	//check for out of bound brushes
	for (i = 0; i < 3; i++)
	{
		if (brush->mins[i] < -MAX_MAP_BOUNDS || brush->maxs[i] > MAX_MAP_BOUNDS)
		{
			Log_Print("brush: bounds out of range\n");
			Log_Print("ob->mins[%d] = %f, ob->maxs[%d] = %f\n", i, brush->mins[i], i, brush->maxs[i]);
			break;
		} //end if
		if (brush->mins[i] > MAX_MAP_BOUNDS || brush->maxs[i] < -MAX_MAP_BOUNDS)
		{
			Log_Print("brush: no visible sides on brush\n");
			Log_Print("ob->mins[%d] = %f, ob->maxs[%d] = %f\n", i, brush->mins[i], i, brush->maxs[i]);
			break;
		} //end if
	} //end for
}