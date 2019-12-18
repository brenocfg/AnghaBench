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
typedef  double* vec3_t ;
struct TYPE_4__ {size_t firstVert; int numVerts; } ;
typedef  TYPE_1__ q3_dsurface_t ;
struct TYPE_5__ {float* xyz; } ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (double*,double*,double*) ; 
 float DotProduct (float*,double*) ; 
 int /*<<< orphan*/  Log_Print (char*,int,float,float,float) ; 
 double VectorLength (double*) ; 
 int /*<<< orphan*/  VectorNormalize (double*) ; 
 int /*<<< orphan*/  VectorSubtract (float*,float*,double*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int q3_drawSurfaces ; 
 TYPE_2__* q3_drawVerts ; 

void Q3_SurfacePlane(q3_dsurface_t *surface, vec3_t normal, float *dist)
{
	int i;
	float *p0, *p1, *p2;
	vec3_t t1, t2;

	p0 = q3_drawVerts[surface->firstVert].xyz;
	for (i = 1; i < surface->numVerts-1; i++)
	{
		p1 = q3_drawVerts[surface->firstVert + ((i) % surface->numVerts)].xyz;
		p2 = q3_drawVerts[surface->firstVert + ((i+1) % surface->numVerts)].xyz;
		VectorSubtract(p0, p1, t1);
		VectorSubtract(p2, p1, t2);
		CrossProduct(t1, t2, normal);
		VectorNormalize(normal);
		if (VectorLength(normal)) break;
	} //end for*/
/*
	float dot;
	for (i = 0; i < surface->numVerts; i++)
	{
		p0 = q3_drawVerts[surface->firstVert + ((i) % surface->numVerts)].xyz;
		p1 = q3_drawVerts[surface->firstVert + ((i+1) % surface->numVerts)].xyz;
		p2 = q3_drawVerts[surface->firstVert + ((i+2) % surface->numVerts)].xyz;
		VectorSubtract(p0, p1, t1);
		VectorSubtract(p2, p1, t2);
		VectorNormalize(t1);
		VectorNormalize(t2);
		dot = DotProduct(t1, t2);
		if (dot > -0.9 && dot < 0.9 &&
			VectorLength(t1) > 0.1 && VectorLength(t2) > 0.1) break;
	} //end for
	CrossProduct(t1, t2, normal);
	VectorNormalize(normal);
*/
	if (VectorLength(normal) < 0.9)
	{
		printf("surface %td bogus normal vector %f %f %f\n", surface - q3_drawSurfaces, normal[0], normal[1], normal[2]);
		printf("t1 = %f %f %f, t2 = %f %f %f\n", t1[0], t1[1], t1[2], t2[0], t2[1], t2[2]);
		for (i = 0; i < surface->numVerts; i++)
		{
			p1 = q3_drawVerts[surface->firstVert + ((i) % surface->numVerts)].xyz;
			Log_Print("p%d = %f %f %f\n", i, p1[0], p1[1], p1[2]);
		} //end for
	} //end if
	*dist = DotProduct(p0, normal);
}