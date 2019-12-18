#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cpuidle_driver {TYPE_2__* states; } ;
struct cpuidle_device {TYPE_1__* states_usage; } ;
struct TYPE_4__ {unsigned int target_residency; scalar_t__ disabled; } ;
struct TYPE_3__ {scalar_t__ disable; } ;

/* Variables and functions */

__attribute__((used)) static int teo_find_shallower_state(struct cpuidle_driver *drv,
				    struct cpuidle_device *dev, int state_idx,
				    unsigned int duration_us)
{
	int i;

	for (i = state_idx - 1; i >= 0; i--) {
		if (drv->states[i].disabled || dev->states_usage[i].disable)
			continue;

		state_idx = i;
		if (drv->states[i].target_residency <= duration_us)
			break;
	}
	return state_idx;
}