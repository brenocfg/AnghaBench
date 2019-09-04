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
typedef  void* vec_t ;
typedef  int* m4x4_t ;
struct TYPE_4__ {int* extents; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ aabb_t ;

/* Variables and functions */
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fabs (int) ; 
 int /*<<< orphan*/  m4x4_transform_point (int* const,int /*<<< orphan*/ ) ; 

void aabb_for_transformed_aabb( aabb_t* dst, const aabb_t* src, const m4x4_t transform ){
	VectorCopy( src->origin, dst->origin );
	m4x4_transform_point( transform, dst->origin );

	dst->extents[0] = (vec_t)( fabs( transform[0]  * src->extents[0] )
							   + fabs( transform[4]  * src->extents[1] )
							   + fabs( transform[8]  * src->extents[2] ) );
	dst->extents[1] = (vec_t)( fabs( transform[1]  * src->extents[0] )
							   + fabs( transform[5]  * src->extents[1] )
							   + fabs( transform[9]  * src->extents[2] ) );
	dst->extents[2] = (vec_t)( fabs( transform[2]  * src->extents[0] )
							   + fabs( transform[6]  * src->extents[1] )
							   + fabs( transform[10] * src->extents[2] ) );
}