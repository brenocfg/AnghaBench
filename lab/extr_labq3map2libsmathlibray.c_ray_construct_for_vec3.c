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
struct TYPE_3__ {int /*<<< orphan*/  direction; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ ray_t ;

/* Variables and functions */
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

void ray_construct_for_vec3( ray_t *ray, const vec3_t origin, const vec3_t direction ){
	VectorCopy( origin, ray->origin );
	VectorCopy( direction, ray->direction );
}