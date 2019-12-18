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
struct TYPE_5__ {int numpoints; int /*<<< orphan*/ ** p; } ;
typedef  TYPE_1__ winding_t ;
typedef  int /*<<< orphan*/  vec_t ;
typedef  int /*<<< orphan*/ * vec3_t ;
struct TYPE_6__ {int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ dplane_t ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float DotProduct (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float WCONVEX_EPSILON ; 
 TYPE_2__* dplanes ; 

int InsideWinding(winding_t *w, vec3_t point, int planenum)
{
	int i;
	float dist;
	vec_t *v1, *v2;
	vec3_t normal, edgevec;
	dplane_t *plane;

	for (i = 1; i <= w->numpoints; i++)
	{
		v1 = w->p[i % w->numpoints];
		v2 = w->p[(i + 1) % w->numpoints];

		VectorSubtract(v2, v1, edgevec);
		plane = &dplanes[planenum];
		CrossProduct(plane->normal, edgevec, normal);
		VectorNormalize(normal);
		dist = DotProduct(normal, v1);
		//
		if (DotProduct(normal, point) - dist > WCONVEX_EPSILON) return false;
	} //end for
	return true;
}