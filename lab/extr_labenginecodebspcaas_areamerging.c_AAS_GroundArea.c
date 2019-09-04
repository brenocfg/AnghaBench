#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int faceflags; TYPE_2__* frontarea; struct TYPE_4__** next; } ;
typedef  TYPE_1__ tmp_face_t ;
struct TYPE_5__ {TYPE_1__* tmpfaces; } ;
typedef  TYPE_2__ tmp_area_t ;

/* Variables and functions */
 int FACE_GROUND ; 

int AAS_GroundArea(tmp_area_t *tmparea)
{
	tmp_face_t *face;
	int side;

	for (face = tmparea->tmpfaces; face; face = face->next[side])
	{
		side = (face->frontarea != tmparea);
		if (face->faceflags & FACE_GROUND) return true;
	} //end for
	return false;
}