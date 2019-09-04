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
struct TYPE_5__ {int faceflags; } ;
typedef  TYPE_1__ aas_face_t ;
struct TYPE_6__ {int numfaces; int firstface; } ;
typedef  TYPE_2__ aas_area_t ;
struct TYPE_7__ {int /*<<< orphan*/ * faceindex; TYPE_1__* faces; TYPE_2__* areas; } ;

/* Variables and functions */
 scalar_t__ AAS_FaceArea (TYPE_1__*) ; 
 int FACE_GROUND ; 
 TYPE_3__ aasworld ; 
 size_t abs (int /*<<< orphan*/ ) ; 

float AAS_AreaGroundFaceArea(int areanum)
{
	int i;
	float total;
	aas_area_t *area;
	aas_face_t *face;

	total = 0;
	area = &aasworld.areas[areanum];
	for (i = 0; i < area->numfaces; i++)
	{
		face = &aasworld.faces[abs(aasworld.faceindex[area->firstface + i])];
		if (!(face->faceflags & FACE_GROUND)) continue;
		//
		total += AAS_FaceArea(face);
	} //end for
	return total;
}