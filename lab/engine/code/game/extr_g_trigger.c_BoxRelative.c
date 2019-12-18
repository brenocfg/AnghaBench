#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int* vec3_t ;

/* Variables and functions */

__attribute__((used)) static void BoxRelative(const vec3_t point, const vec3_t box_min,
												const vec3_t box_max, vec3_t result) {
	result[0] = (point[0] - box_min[0])/(box_max[0] - box_min[0]);
	result[1] = (point[1] - box_min[1])/(box_max[1] - box_min[1]);
	result[2] = (point[2] - box_min[2])/(box_max[2] - box_min[2]);
}