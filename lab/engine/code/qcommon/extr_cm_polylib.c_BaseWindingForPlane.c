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
struct TYPE_4__ {int** p; int numpoints; } ;
typedef  TYPE_1__ winding_t ;
typedef  int /*<<< orphan*/  vec_t ;
typedef  int* vec3_t ;

/* Variables and functions */
 TYPE_1__* AllocWinding (int) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CrossProduct (int*,int*,int*) ; 
 int /*<<< orphan*/  DotProduct (int*,int*) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  MAX_MAP_BOUNDS ; 
 int /*<<< orphan*/  VectorAdd (int*,int*,int*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  VectorMA (int*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  VectorNormalize2 (int*,int*) ; 
 int /*<<< orphan*/  VectorScale (int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  VectorSubtract (int*,int*,int*) ; 
 int /*<<< orphan*/  fabs (int) ; 
 int /*<<< orphan*/  vec3_origin ; 

winding_t *BaseWindingForPlane (vec3_t normal, vec_t dist)
{
	int		i, x;
	vec_t	max, v;
	vec3_t	org, vright, vup;
	winding_t	*w;
	
// find the major axis

	max = -MAX_MAP_BOUNDS;
	x = -1;
	for (i=0 ; i<3; i++)
	{
		v = fabs(normal[i]);
		if (v > max)
		{
			x = i;
			max = v;
		}
	}
	if (x==-1)
		Com_Error (ERR_DROP, "BaseWindingForPlane: no axis found");
		
	VectorCopy (vec3_origin, vup);	
	switch (x)
	{
	case 0:
	case 1:
		vup[2] = 1;
		break;		
	case 2:
		vup[0] = 1;
		break;		
	}

	v = DotProduct (vup, normal);
	VectorMA (vup, -v, normal, vup);
	VectorNormalize2(vup, vup);
		
	VectorScale (normal, dist, org);
	
	CrossProduct (vup, normal, vright);
	
	VectorScale (vup, MAX_MAP_BOUNDS, vup);
	VectorScale (vright, MAX_MAP_BOUNDS, vright);

// project a really big	axis aligned box onto the plane
	w = AllocWinding (4);
	
	VectorSubtract (org, vright, w->p[0]);
	VectorAdd (w->p[0], vup, w->p[0]);
	
	VectorAdd (org, vright, w->p[1]);
	VectorAdd (w->p[1], vup, w->p[1]);
	
	VectorAdd (org, vright, w->p[2]);
	VectorSubtract (w->p[2], vup, w->p[2]);
	
	VectorSubtract (org, vright, w->p[3]);
	VectorSubtract (w->p[3], vup, w->p[3]);
	
	w->numpoints = 4;
	
	return w;	
}