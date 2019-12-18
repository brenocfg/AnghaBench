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
struct TYPE_3__ {int /*<<< orphan*/  direction; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ ray_t ;

/* Variables and functions */
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VEC_MAX ; 
 float VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

vec_t ray_intersect_point( const ray_t *ray, const vec3_t point, vec_t epsilon, vec_t divergence ){
	vec3_t displacement;
	vec_t depth;

	// calc displacement of test point from ray origin
	VectorSubtract( point, ray->origin, displacement );
	// calc length of displacement vector along ray direction
	depth = DotProduct( displacement, ray->direction );
	if ( depth < 0.0f ) {
		return (vec_t)VEC_MAX;
	}
	// calc position of closest point on ray to test point
	VectorMA( ray->origin, depth, ray->direction, displacement );
	// calc displacement of test point from closest point
	VectorSubtract( point, displacement, displacement );
	// calc length of displacement, subtract depth-dependant epsilon
	if ( VectorLength( displacement ) - ( epsilon + ( depth * divergence ) ) > 0.0f ) {
		return (vec_t)VEC_MAX;
	}
	return depth;
}