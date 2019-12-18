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
struct cpuidle_driver {int dummy; } ;
struct cpuidle_device {int /*<<< orphan*/  next_hrtimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cpuidle_enter_state (struct cpuidle_device*,struct cpuidle_driver*,int) ; 
 int cpuidle_enter_state_coupled (struct cpuidle_device*,struct cpuidle_driver*,int) ; 
 scalar_t__ cpuidle_state_is_coupled (struct cpuidle_driver*,int) ; 
 int /*<<< orphan*/  tick_nohz_get_next_hrtimer () ; 

int cpuidle_enter(struct cpuidle_driver *drv, struct cpuidle_device *dev,
		  int index)
{
	int ret = 0;

	/*
	 * Store the next hrtimer, which becomes either next tick or the next
	 * timer event, whatever expires first. Additionally, to make this data
	 * useful for consumers outside cpuidle, we rely on that the governor's
	 * ->select() callback have decided, whether to stop the tick or not.
	 */
	WRITE_ONCE(dev->next_hrtimer, tick_nohz_get_next_hrtimer());

	if (cpuidle_state_is_coupled(drv, index))
		ret = cpuidle_enter_state_coupled(dev, drv, index);
	else
		ret = cpuidle_enter_state(dev, drv, index);

	WRITE_ONCE(dev->next_hrtimer, 0);
	return ret;
}