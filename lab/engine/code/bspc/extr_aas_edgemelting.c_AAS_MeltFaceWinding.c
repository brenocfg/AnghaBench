#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_t ;
struct TYPE_12__ {size_t planenum; TYPE_1__* winding; int /*<<< orphan*/  num; } ;
typedef  TYPE_2__ tmp_face_t ;
struct TYPE_13__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_3__ plane_t ;

/* Variables and functions */
 TYPE_1__* AddWindingPoint (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeWinding (TYPE_1__*) ; 
 scalar_t__ PointOnWinding (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 TYPE_3__* mapplanes ; 

int AAS_MeltFaceWinding(tmp_face_t *face1, tmp_face_t *face2)
{
	int i, n;
	int splits = 0;
	winding_t *w2, *neww;
	plane_t *plane1;

#ifdef DEBUG
	if (!face1->winding) Error("face1 %d without winding", face1->num);
	if (!face2->winding) Error("face2 %d without winding", face2->num);
#endif //DEBUG
	w2 = face2->winding;
	plane1 = &mapplanes[face1->planenum];
	for (i = 0; i < w2->numpoints; i++)
	{
		if (PointOnWinding(face1->winding, plane1->normal, plane1->dist, w2->p[i], &n))
		{
			neww = AddWindingPoint(face1->winding, w2->p[i], n);
			FreeWinding(face1->winding);
			face1->winding = neww;

			splits++;
		} //end if
	} //end for
	return splits;
}