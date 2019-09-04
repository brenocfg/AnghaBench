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
typedef  scalar_t__* vec3_t ;
struct TYPE_3__ {scalar_t__* extents; scalar_t__* origin; } ;
typedef  TYPE_1__ aabb_t ;

/* Variables and functions */
 scalar_t__ fabs (scalar_t__) ; 

int aabb_intersect_point( const aabb_t *aabb, const vec3_t point ){
	int i;
	for ( i = 0; i < 3; i++ )
		if ( fabs( point[i] - aabb->origin[i] ) >= aabb->extents[i] ) {
			return 0;
		}
	return 1;
}