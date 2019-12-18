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
struct cpuidle_device {int last_state_idx; } ;

/* Variables and functions */

__attribute__((used)) static void ladder_reflect(struct cpuidle_device *dev, int index)
{
	if (index > 0)
		dev->last_state_idx = index;
}