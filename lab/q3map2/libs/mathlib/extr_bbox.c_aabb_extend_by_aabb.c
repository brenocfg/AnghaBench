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
typedef  scalar_t__ vec_t ;
struct TYPE_4__ {scalar_t__* origin; scalar_t__* extents; } ;
typedef  TYPE_1__ aabb_t ;

/* Variables and functions */
 scalar_t__ fabs (scalar_t__) ; 

void aabb_extend_by_aabb( aabb_t *aabb, const aabb_t *aabb_src ){
	int i;
	vec_t min, max, displacement, difference;
	for ( i = 0; i < 3; i++ )
	{
		displacement = aabb_src->origin[i] - aabb->origin[i];
		difference = aabb_src->extents[i] - aabb->extents[i];
		if ( aabb->extents[i] < 0
			 || difference >= fabs( displacement ) ) {
			// 2nd contains 1st
			aabb->extents[i] = aabb_src->extents[i];
			aabb->origin[i] = aabb_src->origin[i];
		}
		else if ( aabb_src->extents[i] < 0
				  || -difference >= fabs( displacement ) ) {
			// 1st contains 2nd
			continue;
		}
		else
		{
			// not contained
			if ( displacement > 0 ) {
				min = aabb->origin[i] - aabb->extents[i];
				max = aabb_src->origin[i] + aabb_src->extents[i];
			}
			else
			{
				min = aabb_src->origin[i] - aabb_src->extents[i];
				max = aabb->origin[i] + aabb->extents[i];
			}
			aabb->origin[i] = ( min + max ) * 0.5f;
			aabb->extents[i] = max - aabb->origin[i];
		}
	}
}