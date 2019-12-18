#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int faceflags; int frontarea; int backarea; } ;
typedef  TYPE_1__ aas_face_t ;
struct TYPE_5__ {int numfaces; int firstface; } ;
typedef  TYPE_2__ aas_area_t ;
struct TYPE_6__ {TYPE_1__* faces; int /*<<< orphan*/ * faceindex; TYPE_2__* areas; } ;

/* Variables and functions */
 int FACE_SOLID ; 
 TYPE_3__ aasworld ; 
 int abs (int /*<<< orphan*/ ) ; 
 int qtrue ; 

void AAS_ConnectedAreas_r(int *areanums, int numareas, int *connectedareas, int curarea)
{
	int i, j, otherareanum, facenum;
	aas_area_t *area;
	aas_face_t *face;

	connectedareas[curarea] = qtrue;
	area = &aasworld.areas[areanums[curarea]];
	for (i = 0; i < area->numfaces; i++)
	{
		facenum = abs(aasworld.faceindex[area->firstface + i]);
		face = &aasworld.faces[facenum];
		//if the face is solid
		if (face->faceflags & FACE_SOLID) continue;
		//get the area at the other side of the face
		if (face->frontarea != areanums[curarea]) otherareanum = face->frontarea;
		else otherareanum = face->backarea;
		//check if the face is leading to one of the other areas
		for (j = 0; j < numareas; j++)
		{
			if (areanums[j] == otherareanum) break;
		} //end for
		//if the face isn't leading to one of the other areas
		if (j == numareas) continue;
		//if the other area is already connected
		if (connectedareas[j]) continue;
		//recursively proceed with the other area
		AAS_ConnectedAreas_r(areanums, numareas, connectedareas, j);
	} //end for
}