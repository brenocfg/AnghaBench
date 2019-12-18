#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_4__ {int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  currentAngles; int /*<<< orphan*/  currentOrigin; } ;
struct TYPE_5__ {TYPE_1__ r; } ;
typedef  TYPE_2__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  BoxRelative (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InverseRotation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static void MoveToEntitySpace(const gentity_t* entity, const vec3_t world_point,
															vec3_t result) {
	vec3_t local_point;
	// Compute the displacement vector of 'world_point' with respect to the
	// entity's origin.
	VectorSubtract(world_point, entity->r.currentOrigin, local_point);
	// Express such displacement vector in the coordinate frame spanned by the
	// entity's bounding box.
	InverseRotation(entity->r.currentAngles, local_point, qtrue);
	BoxRelative(local_point, entity->r.mins, entity->r.maxs, result);
}