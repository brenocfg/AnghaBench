#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vec_t ;
typedef  int /*<<< orphan*/ * vec3_t ;
struct TYPE_6__ {int /*<<< orphan*/ * extents; int /*<<< orphan*/  origin; } ;
struct TYPE_7__ {TYPE_1__ aabb; int /*<<< orphan*/ * axes; } ;
typedef  TYPE_2__ bbox_t ;
struct TYPE_8__ {scalar_t__* extents; int /*<<< orphan*/  origin; } ;
typedef  TYPE_3__ aabb_t ;

/* Variables and functions */
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ fabs (int /*<<< orphan*/ ) ; 

void aabb_for_bbox( aabb_t *aabb, const bbox_t *bbox ){
	int i;
	vec3_t temp[3];

	VectorCopy( bbox->aabb.origin, aabb->origin );

	// calculate the AABB extents in local coord space from the OBB extents and axes
	VectorScale( bbox->axes[0], bbox->aabb.extents[0], temp[0] );
	VectorScale( bbox->axes[1], bbox->aabb.extents[1], temp[1] );
	VectorScale( bbox->axes[2], bbox->aabb.extents[2], temp[2] );
	for ( i = 0; i < 3; i++ ) aabb->extents[i] = (vec_t)( fabs( temp[0][i] ) + fabs( temp[1][i] ) + fabs( temp[2][i] ) );
}