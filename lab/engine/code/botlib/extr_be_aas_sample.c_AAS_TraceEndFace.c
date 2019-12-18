#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t lastarea; int planenum; int /*<<< orphan*/  endpos; scalar_t__ startsolid; } ;
typedef  TYPE_2__ aas_trace_t ;
struct TYPE_11__ {int planenum; } ;
typedef  TYPE_3__ aas_face_t ;
struct TYPE_12__ {int numfaces; int firstface; } ;
typedef  TYPE_4__ aas_area_t ;
struct TYPE_13__ {int* faceindex; TYPE_1__* planes; TYPE_3__* faces; TYPE_4__* areas; int /*<<< orphan*/  loaded; } ;
struct TYPE_9__ {int /*<<< orphan*/  normal; } ;

/* Variables and functions */
 scalar_t__ AAS_InsideFace (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 TYPE_5__ aasworld ; 
 size_t abs (int) ; 

aas_face_t *AAS_TraceEndFace(aas_trace_t *trace)
{
	int i, facenum;
	aas_area_t *area;
	aas_face_t *face, *firstface = NULL;

	if (!aasworld.loaded) return NULL;

	//if started in solid no face was hit
	if (trace->startsolid) return NULL;
	//trace->lastarea is the last area the trace was in
	area = &aasworld.areas[trace->lastarea];
	//check which face the trace.endpos was in
	for (i = 0; i < area->numfaces; i++)
	{
		facenum = aasworld.faceindex[area->firstface + i];
		face = &aasworld.faces[abs(facenum)];
		//if the face is in the same plane as the trace end point
		if ((face->planenum & ~1) == (trace->planenum & ~1))
		{
			//firstface is used for optimization, if theres only one
			//face in the plane then it has to be the good one
			//if there are more faces in the same plane then always
			//check the one with the fewest edges first
/*			if (firstface)
			{
				if (firstface->numedges < face->numedges)
				{
					if (AAS_InsideFace(firstface,
						aasworld.planes[face->planenum].normal, trace->endpos))
					{
						return firstface;
					} //end if
					firstface = face;
				} //end if
				else
				{
					if (AAS_InsideFace(face,
						aasworld.planes[face->planenum].normal, trace->endpos))
					{
						return face;
					} //end if
				} //end else
			} //end if
			else
			{
				firstface = face;
			} //end else*/
			if (AAS_InsideFace(face,
						aasworld.planes[face->planenum].normal, trace->endpos, 0.01f)) return face;
		} //end if
	} //end for
	return firstface;
}