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

/* Variables and functions */

__attribute__((used)) static
int uniform_vlarb_weight_value(unsigned *weight, unsigned count)
{
	int i, v = weight[0];

	for (i = 1; i < count; i++) {
		if (v != weight[i])
			return -1;
	}
	return v;
}