#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_t ;
typedef  int /*<<< orphan*/  vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float MELT_ON_EPSILON ; 
 double VectorNormalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int PointOnWinding(winding_t *w, vec3_t normal, float dist, vec3_t point, int *spot)
{
	int i, j;
	vec3_t v1, v2;
	vec3_t edgenormal, edgevec;
	float edgedist, dot;

	*spot = 0;
	//the point must be on the winding plane
	dot = DotProduct(point, normal) - dist;
	if (dot < -MELT_ON_EPSILON || dot > MELT_ON_EPSILON) return false;
	//
	for (i = 0; i < w->numpoints; i++)
	{
		j = (i+1) % w->numpoints;
		//get a plane orthogonal to the winding plane through the edge
		VectorSubtract(w->p[j], w->p[i], edgevec);
		CrossProduct(normal, edgevec, edgenormal);
		VectorNormalize(edgenormal);
		edgedist = DotProduct(edgenormal, w->p[i]);
		//point must be not too far from the plane
		dot = DotProduct(point, edgenormal) - edgedist;
		if (dot < -MELT_ON_EPSILON || dot > MELT_ON_EPSILON) continue;
		//vector from first point of winding to the point to test
		VectorSubtract(point, w->p[i], v1);
		//vector from second point of winding to the point to test
		VectorSubtract(point, w->p[j], v2);
		//if the length of the vector is not larger than 0.5 units then
		//the point is assumend to be the same as one of the winding points
		if (VectorNormalize(v1) < 0.5) return false;
		if (VectorNormalize(v2) < 0.5) return false;
		//point must be between the two winding points
		//(the two vectors must be directed towards each other, and on the
		//same straight line)
		if (DotProduct(v1, v2) < -0.99)
		{
			*spot = i + 1;
			return true;
		} //end if
	} //end for
	return false;
}