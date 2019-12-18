#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_5__ {int /*<<< orphan*/ * extents; } ;
typedef  TYPE_1__ aabb_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLT_MAX ; 
 int /*<<< orphan*/  aabb_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  aabb_extend_by_point (TYPE_1__*,int /*<<< orphan*/ ) ; 

void aabb_for_area( aabb_t *aabb, vec3_t area_tl, vec3_t area_br, int axis ){
	aabb_clear( aabb );
	aabb->extents[axis] = FLT_MAX;
	aabb_extend_by_point( aabb, area_tl );
	aabb_extend_by_point( aabb, area_br );
}