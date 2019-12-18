#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int promotion_time; scalar_t__ promotion_count; int demotion_time; scalar_t__ demotion_count; } ;
struct TYPE_7__ {scalar_t__ promotion_count; scalar_t__ demotion_count; } ;
struct ladder_device_state {TYPE_4__ threshold; TYPE_3__ stats; } ;
struct ladder_device {struct ladder_device_state* states; } ;
struct cpuidle_driver {int state_count; TYPE_2__* states; } ;
struct cpuidle_device {int last_state_idx; int last_residency; TYPE_1__* states_usage; int /*<<< orphan*/  cpu; } ;
struct TYPE_6__ {int flags; int exit_latency; scalar_t__ disabled; } ;
struct TYPE_5__ {scalar_t__ disable; } ;

/* Variables and functions */
 int CPUIDLE_FLAG_POLLING ; 
 int cpuidle_governor_latency_req (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ladder_devices ; 
 int /*<<< orphan*/  ladder_do_selection (struct cpuidle_device*,struct ladder_device*,int,int) ; 
 struct ladder_device* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ladder_select_state(struct cpuidle_driver *drv,
			       struct cpuidle_device *dev, bool *dummy)
{
	struct ladder_device *ldev = this_cpu_ptr(&ladder_devices);
	struct ladder_device_state *last_state;
	int last_residency, last_idx = dev->last_state_idx;
	int first_idx = drv->states[0].flags & CPUIDLE_FLAG_POLLING ? 1 : 0;
	int latency_req = cpuidle_governor_latency_req(dev->cpu);

	/* Special case when user has set very strict latency requirement */
	if (unlikely(latency_req == 0)) {
		ladder_do_selection(dev, ldev, last_idx, 0);
		return 0;
	}

	last_state = &ldev->states[last_idx];

	last_residency = dev->last_residency - drv->states[last_idx].exit_latency;

	/* consider promotion */
	if (last_idx < drv->state_count - 1 &&
	    !drv->states[last_idx + 1].disabled &&
	    !dev->states_usage[last_idx + 1].disable &&
	    last_residency > last_state->threshold.promotion_time &&
	    drv->states[last_idx + 1].exit_latency <= latency_req) {
		last_state->stats.promotion_count++;
		last_state->stats.demotion_count = 0;
		if (last_state->stats.promotion_count >= last_state->threshold.promotion_count) {
			ladder_do_selection(dev, ldev, last_idx, last_idx + 1);
			return last_idx + 1;
		}
	}

	/* consider demotion */
	if (last_idx > first_idx &&
	    (drv->states[last_idx].disabled ||
	    dev->states_usage[last_idx].disable ||
	    drv->states[last_idx].exit_latency > latency_req)) {
		int i;

		for (i = last_idx - 1; i > first_idx; i--) {
			if (drv->states[i].exit_latency <= latency_req)
				break;
		}
		ladder_do_selection(dev, ldev, last_idx, i);
		return i;
	}

	if (last_idx > first_idx &&
	    last_residency < last_state->threshold.demotion_time) {
		last_state->stats.demotion_count++;
		last_state->stats.promotion_count = 0;
		if (last_state->stats.demotion_count >= last_state->threshold.demotion_count) {
			ladder_do_selection(dev, ldev, last_idx, last_idx - 1);
			return last_idx - 1;
		}
	}

	/* otherwise remain at the current state */
	return last_idx;
}