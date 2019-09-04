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
struct TYPE_5__ {TYPE_2__* frontarea; struct TYPE_5__** next; } ;
typedef  TYPE_1__ tmp_face_t ;
struct TYPE_6__ {TYPE_1__* tmpfaces; scalar_t__ invalid; struct TYPE_6__* l_next; } ;
typedef  TYPE_2__ tmp_area_t ;
struct TYPE_7__ {TYPE_2__* areas; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_CheckFaceWindingPlane (TYPE_1__*) ; 
 int /*<<< orphan*/  Log_Write (char*) ; 
 TYPE_3__ tmpaasworld ; 

void AAS_CheckAreaWindingPlanes(void)
{
	int side;
	tmp_area_t *tmparea;
	tmp_face_t *face;

	Log_Write("AAS_CheckAreaWindingPlanes:\r\n");
	for (tmparea = tmpaasworld.areas; tmparea; tmparea = tmparea->l_next)
	{
		if (tmparea->invalid) continue;
		for (face = tmparea->tmpfaces; face; face = face->next[side])
		{
			side = face->frontarea != tmparea;
			AAS_CheckFaceWindingPlane(face);
		} //end for
	} //end for
}