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
struct cpuidle_driver {int /*<<< orphan*/  state_count; } ;
struct cpuidle_device {scalar_t__ poll_limit_ns; scalar_t__ last_state_idx; int poll_time_limit; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int cpuidle_governor_latency_req (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int haltpoll_select(struct cpuidle_driver *drv,
			   struct cpuidle_device *dev,
			   bool *stop_tick)
{
	int latency_req = cpuidle_governor_latency_req(dev->cpu);

	if (!drv->state_count || latency_req == 0) {
		*stop_tick = false;
		return 0;
	}

	if (dev->poll_limit_ns == 0)
		return 1;

	/* Last state was poll? */
	if (dev->last_state_idx == 0) {
		/* Halt if no event occurred on poll window */
		if (dev->poll_time_limit == true)
			return 1;

		*stop_tick = false;
		/* Otherwise, poll again */
		return 0;
	}

	*stop_tick = false;
	/* Last state was halt: poll */
	return 0;
}