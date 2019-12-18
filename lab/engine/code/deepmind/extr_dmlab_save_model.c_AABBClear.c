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
struct TYPE_3__ {int* extents; scalar_t__* origin; } ;
typedef  TYPE_1__ aabb_t ;

/* Variables and functions */

__attribute__((used)) static void AABBClear(aabb_t *aabb) {
  aabb->origin[0] = aabb->origin[1] = aabb->origin[2] = 0;
  aabb->extents[0] = aabb->extents[1] = aabb->extents[2] = -1;
}