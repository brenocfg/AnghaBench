#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* frontarea; struct TYPE_6__** next; } ;
typedef  TYPE_1__ tmp_face_t ;
struct TYPE_7__ {TYPE_1__* tmpfaces; } ;
typedef  TYPE_2__ tmp_area_t ;

/* Variables and functions */
 scalar_t__ AAS_MeltFaceWinding (TYPE_1__*,TYPE_1__*) ; 

int AAS_MeltFaceWindingsOfArea(tmp_area_t *tmparea)
{
	int side1, side2, num_windingsplits = 0;
	tmp_face_t *face1, *face2;

	for (face1 = tmparea->tmpfaces; face1; face1 = face1->next[side1])
	{
		side1 = face1->frontarea != tmparea;
		for (face2 = tmparea->tmpfaces; face2; face2 = face2->next[side2])
		{
			side2 = face2->frontarea != tmparea;
			if (face1 == face2) continue;
			num_windingsplits += AAS_MeltFaceWinding(face1, face2);
		} //end for
	} //end for
	return num_windingsplits;
}