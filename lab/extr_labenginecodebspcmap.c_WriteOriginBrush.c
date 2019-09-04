#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__** p; } ;
typedef  TYPE_1__ winding_t ;
typedef  int* vec3_t ;
typedef  int qboolean ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__* BaseWindingForPlane (int*,float) ; 
 int /*<<< orphan*/  FreeWinding (TYPE_1__*) ; 
 scalar_t__ MAPTYPE_HALFLIFE ; 
 scalar_t__ MAPTYPE_QUAKE2 ; 
 scalar_t__ MAPTYPE_SIN ; 
 int /*<<< orphan*/  VectorClear (int*) ; 
 int /*<<< orphan*/  c_writtenbrushes ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ loadedmaptype ; 

qboolean WriteOriginBrush(FILE *fp, vec3_t origin)
{
	vec3_t normal;
	float dist;
	int i, s;
	winding_t *w;

	if (fprintf(fp, " {\n") < 0) return false;
	//
	for (i = 0; i < 3; i++)
	{
		for (s = -1; s <= 1; s += 2)
		{
			//
			VectorClear(normal);
			normal[i] = s;
			dist = origin[i] * s + 16;
			//
			w = BaseWindingForPlane(normal, dist);
			//three non-colinear points to define the plane
			if (fprintf(fp,"  ( %5i %5i %5i ) ", (int)w->p[0][0], (int)w->p[0][1], (int)w->p[0][2]) < 0) return false;
			if (fprintf(fp,"( %5i %5i %5i ) ", (int)w->p[1][0], (int)w->p[1][1], (int)w->p[1][2]) < 0) return false;
			if (fprintf(fp,"( %5i %5i %5i ) ", (int)w->p[2][0], (int)w->p[2][1], (int)w->p[2][2]) < 0) return false;
			//free the winding
			FreeWinding(w);
			//write origin texture:
			// CONTENTS_ORIGIN = 16777216
			// SURF_NODRAW = 128
			if (loadedmaptype == MAPTYPE_SIN)
			{
				if (fprintf(fp, "generic/misc/origin 0 0 0 1 1") < 0) return false;
			} //end if
			else if (loadedmaptype == MAPTYPE_HALFLIFE)
			{
				if (fprintf(fp, "origin 0 0 0 1 1") < 0) return false;
			} //end if
			else
			{
				if (fprintf(fp, "e1u1/origin 0 0 0 1 1") < 0) return false;
			} //end else
			//Quake2 extra brush side info
			if (loadedmaptype == MAPTYPE_QUAKE2)
			{
				//if (fprintf(fp, " 16777216 128 0") < 0) return false;
			} //end if
			if (fprintf(fp, "\n") < 0) return false;
		} //end for
	} //end for
	if (fprintf(fp, " }\n") < 0) return false;
	c_writtenbrushes++;
	return true;
}