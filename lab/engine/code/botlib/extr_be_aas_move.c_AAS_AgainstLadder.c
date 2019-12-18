#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_7__ {scalar_t__ dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ aas_plane_t ;
struct TYPE_8__ {int faceflags; int planenum; } ;
typedef  TYPE_3__ aas_face_t ;
struct TYPE_9__ {int numfaces; int firstface; } ;
typedef  TYPE_4__ aas_area_t ;
struct TYPE_10__ {int* faceindex; TYPE_2__* planes; TYPE_3__* faces; TYPE_4__* areas; TYPE_1__* areasettings; } ;
struct TYPE_6__ {int areaflags; int presencetype; } ;

/* Variables and functions */
 int AAS_PointAreaNum (int*) ; 
 scalar_t__ AAS_PointInsideFace (size_t,int*,float) ; 
 int AREA_LADDER ; 
 scalar_t__ DotProduct (int /*<<< orphan*/ ,int*) ; 
 int FACE_LADDER ; 
 int PRESENCE_NORMAL ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 TYPE_5__ aasworld ; 
 size_t abs (int) ; 
 int fabsf (scalar_t__) ; 
 int qfalse ; 
 int qtrue ; 

int AAS_AgainstLadder(vec3_t origin)
{
	int areanum, i, facenum, side;
	vec3_t org;
	aas_plane_t *plane;
	aas_face_t *face;
	aas_area_t *area;

	VectorCopy(origin, org);
	areanum = AAS_PointAreaNum(org);
	if (!areanum)
	{
		org[0] += 1;
		areanum = AAS_PointAreaNum(org);
		if (!areanum)
		{
			org[1] += 1;
			areanum = AAS_PointAreaNum(org);
			if (!areanum)
			{
				org[0] -= 2;
				areanum = AAS_PointAreaNum(org);
				if (!areanum)
				{
					org[1] -= 2;
					areanum = AAS_PointAreaNum(org);
				} //end if
			} //end if
		} //end if
	} //end if
	//if in solid... wrrr shouldn't happen
	if (!areanum) return qfalse;
	//if not in a ladder area
	if (!(aasworld.areasettings[areanum].areaflags & AREA_LADDER)) return qfalse;
	//if a crouch only area
	if (!(aasworld.areasettings[areanum].presencetype & PRESENCE_NORMAL)) return qfalse;
	//
	area = &aasworld.areas[areanum];
	for (i = 0; i < area->numfaces; i++)
	{
		facenum = aasworld.faceindex[area->firstface + i];
		side = facenum < 0;
		face = &aasworld.faces[abs(facenum)];
		//if the face isn't a ladder face
		if (!(face->faceflags & FACE_LADDER)) continue;
		//get the plane the face is in
		plane = &aasworld.planes[face->planenum ^ side];
		//if the origin is pretty close to the plane
		if (fabsf(DotProduct(plane->normal, origin) - plane->dist) < 3)
		{
			if (AAS_PointInsideFace(abs(facenum), origin, 0.1f)) return qtrue;
		} //end if
	} //end for
	return qfalse;
}