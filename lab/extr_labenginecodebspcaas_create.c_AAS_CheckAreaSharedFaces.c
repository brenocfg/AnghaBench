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
struct TYPE_5__ {TYPE_2__* backarea; TYPE_2__* frontarea; int /*<<< orphan*/  planenum; int /*<<< orphan*/  num; struct TYPE_5__** next; } ;
typedef  TYPE_1__ tmp_face_t ;
struct TYPE_6__ {int /*<<< orphan*/  areanum; TYPE_1__* tmpfaces; scalar_t__ invalid; } ;
typedef  TYPE_2__ tmp_area_t ;

/* Variables and functions */
 int /*<<< orphan*/  Log_Write (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 

void AAS_CheckAreaSharedFaces(tmp_area_t *tmparea1, tmp_area_t *tmparea2)
{
	int numsharedfaces, side;
	tmp_face_t *face1, *sharedface;

	if (tmparea1->invalid || tmparea2->invalid) return;

	sharedface = NULL;
	numsharedfaces = 0;
	for (face1 = tmparea1->tmpfaces; face1; face1 = face1->next[side])
	{
		side = face1->frontarea != tmparea1;
		if (face1->backarea == tmparea2 || face1->frontarea == tmparea2)
		{
			sharedface = face1;
			numsharedfaces++;
		} //end if
	} //end if
	if (!sharedface) return;
	//the areas should only have one shared face
	if (numsharedfaces > 1)
	{
		Log_Write("---- tmp area %d and %d have %d shared faces\r\n",
									tmparea1->areanum, tmparea2->areanum, numsharedfaces);
		for (face1 = tmparea1->tmpfaces; face1; face1 = face1->next[side])
		{
			side = face1->frontarea != tmparea1;
			if (face1->backarea == tmparea2 || face1->frontarea == tmparea2)
			{
				Log_Write("face %d, planenum = %d, face->frontarea = %d face->backarea = %d\r\n",
								face1->num, face1->planenum, face1->frontarea->areanum, face1->backarea->areanum);
			} //end if
		} //end if
	} //end if
}