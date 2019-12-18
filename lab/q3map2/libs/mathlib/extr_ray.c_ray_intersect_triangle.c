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
typedef  float vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_3__ {float* direction; int /*<<< orphan*/  const origin; } ;
typedef  TYPE_1__ ray_t ;
typedef  scalar_t__ qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (float*,float*,float*) ; 
 float DotProduct (float*,float*) ; 
 float EPSILON ; 
 int /*<<< orphan*/  VEC_MAX ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/  const,int /*<<< orphan*/  const,float*) ; 
 scalar_t__ qtrue ; 

vec_t ray_intersect_triangle( const ray_t *ray, qboolean bCullBack, const vec3_t vert0, const vec3_t vert1, const vec3_t vert2 ){
	float edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
	float det,inv_det;
	float u, v;
	vec_t depth = (vec_t)VEC_MAX;

	/* find vectors for two edges sharing vert0 */
	VectorSubtract( vert1, vert0, edge1 );
	VectorSubtract( vert2, vert0, edge2 );

	/* begin calculating determinant - also used to calculate U parameter */
	CrossProduct( ray->direction, edge2, pvec );

	/* if determinant is near zero, ray lies in plane of triangle */
	det = DotProduct( edge1, pvec );

	if ( bCullBack == qtrue ) {
		if ( det < EPSILON ) {
			return depth;
		}

		// calculate distance from vert0 to ray origin
		VectorSubtract( ray->origin, vert0, tvec );

		// calculate U parameter and test bounds
		u = DotProduct( tvec, pvec );
		if ( u < 0.0 || u > det ) {
			return depth;
		}

		// prepare to test V parameter
		CrossProduct( tvec, edge1, qvec );

		// calculate V parameter and test bounds
		v = DotProduct( ray->direction, qvec );
		if ( v < 0.0 || u + v > det ) {
			return depth;
		}

		// calculate t, scale parameters, ray intersects triangle
		depth = DotProduct( edge2, qvec );
		inv_det = 1.0f / det;
		depth *= inv_det;
		//u *= inv_det;
		//v *= inv_det;
	}
	else
	{
		/* the non-culling branch */
		if ( det > -EPSILON && det < EPSILON ) {
			return depth;
		}
		inv_det = 1.0f / det;

		/* calculate distance from vert0 to ray origin */
		VectorSubtract( ray->origin, vert0, tvec );

		/* calculate U parameter and test bounds */
		u = DotProduct( tvec, pvec ) * inv_det;
		if ( u < 0.0 || u > 1.0 ) {
			return depth;
		}

		/* prepare to test V parameter */
		CrossProduct( tvec, edge1, qvec );

		/* calculate V parameter and test bounds */
		v = DotProduct( ray->direction, qvec ) * inv_det;
		if ( v < 0.0 || u + v > 1.0 ) {
			return depth;
		}

		/* calculate t, ray intersects triangle */
		depth = DotProduct( edge2, qvec ) * inv_det;
	}
	return depth;
}