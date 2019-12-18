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
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_3__ {int /*<<< orphan*/  extents; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ aabb_t ;

/* Variables and functions */
 int /*<<< orphan*/  VectorMid (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void aabb_construct_for_vec3( aabb_t *aabb, const vec3_t min, const vec3_t max ){
	VectorMid( min, max, aabb->origin );
	VectorSubtract( max, aabb->origin, aabb->extents );
}