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
typedef  float vec_t ;
typedef  float* vec3_t ;
struct TYPE_5__ {float* origin; float* direction; } ;
typedef  TYPE_1__ ray_t ;
struct TYPE_6__ {float* origin; float* extents; } ;
typedef  TYPE_2__ aabb_t ;

/* Variables and functions */
 float fabs (float) ; 

int aabb_test_ray( const aabb_t* aabb, const ray_t* ray ){
	vec3_t displacement, ray_absolute;
	vec_t f;

	displacement[0] = ray->origin[0] - aabb->origin[0];
	if ( fabs( displacement[0] ) > aabb->extents[0] && displacement[0] * ray->direction[0] >= 0.0f ) {
		return 0;
	}

	displacement[1] = ray->origin[1] - aabb->origin[1];
	if ( fabs( displacement[1] ) > aabb->extents[1] && displacement[1] * ray->direction[1] >= 0.0f ) {
		return 0;
	}

	displacement[2] = ray->origin[2] - aabb->origin[2];
	if ( fabs( displacement[2] ) > aabb->extents[2] && displacement[2] * ray->direction[2] >= 0.0f ) {
		return 0;
	}

	ray_absolute[0] = (float)fabs( ray->direction[0] );
	ray_absolute[1] = (float)fabs( ray->direction[1] );
	ray_absolute[2] = (float)fabs( ray->direction[2] );

	f = ray->direction[1] * displacement[2] - ray->direction[2] * displacement[1];
	if ( (float)fabs( f ) > aabb->extents[1] * ray_absolute[2] + aabb->extents[2] * ray_absolute[1] ) {
		return 0;
	}

	f = ray->direction[2] * displacement[0] - ray->direction[0] * displacement[2];
	if ( (float)fabs( f ) > aabb->extents[0] * ray_absolute[2] + aabb->extents[2] * ray_absolute[0] ) {
		return 0;
	}

	f = ray->direction[0] * displacement[1] - ray->direction[1] * displacement[0];
	if ( (float)fabs( f ) > aabb->extents[0] * ray_absolute[1] + aabb->extents[1] * ray_absolute[0] ) {
		return 0;
	}

	return 1;
}