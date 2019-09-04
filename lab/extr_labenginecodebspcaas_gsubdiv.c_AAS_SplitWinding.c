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
struct TYPE_6__ {int planenum; TYPE_2__* frontarea; struct TYPE_6__** next; } ;
typedef  TYPE_1__ tmp_face_t ;
struct TYPE_7__ {TYPE_1__* tmpfaces; } ;
typedef  TYPE_2__ tmp_area_t ;
struct TYPE_8__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_3__ plane_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BaseWindingForPlane (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ChopWindingInPlace (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* mapplanes ; 

winding_t *AAS_SplitWinding(tmp_area_t *tmparea, int planenum)
{
	tmp_face_t *face;
	plane_t *plane;
	int side;
	winding_t *splitwinding;

	//
	plane = &mapplanes[planenum];
	//create a split winding, first base winding for plane
	splitwinding = BaseWindingForPlane(plane->normal, plane->dist);
	//chop with all the faces of the area
	for (face = tmparea->tmpfaces; face && splitwinding; face = face->next[side])
	{
		//side of the face the original area was on
		side = face->frontarea != tmparea;
		plane = &mapplanes[face->planenum ^ side];
		ChopWindingInPlace(&splitwinding, plane->normal, plane->dist, 0); // PLANESIDE_EPSILON);
	} //end for
	return splitwinding;
}