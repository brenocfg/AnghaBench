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
typedef  int u64 ;
struct cpuidle_driver {int state_count; TYPE_2__* states; } ;
struct cpuidle_device {int poll_limit_ns; TYPE_1__* states_usage; } ;
struct TYPE_4__ {scalar_t__ target_residency; scalar_t__ disabled; } ;
struct TYPE_3__ {scalar_t__ disable; } ;

/* Variables and functions */
 int NSEC_PER_USEC ; 
 int TICK_NSEC ; 

u64 cpuidle_poll_time(struct cpuidle_driver *drv,
		      struct cpuidle_device *dev)
{
	int i;
	u64 limit_ns;

	if (dev->poll_limit_ns)
		return dev->poll_limit_ns;

	limit_ns = TICK_NSEC;
	for (i = 1; i < drv->state_count; i++) {
		if (drv->states[i].disabled || dev->states_usage[i].disable)
			continue;

		limit_ns = (u64)drv->states[i].target_residency * NSEC_PER_USEC;
	}

	dev->poll_limit_ns = limit_ns;

	return dev->poll_limit_ns;
}