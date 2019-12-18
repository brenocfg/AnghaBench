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
struct powernv_smp_call_data {void* gpstate_id; void* pstate_id; } ;
struct global_pstate_info {unsigned int last_sampled_time; unsigned int highest_lpstate_idx; unsigned int last_gpstate_idx; unsigned int elapsed_time; unsigned int last_lpstate_idx; int /*<<< orphan*/  gpstate_lock; int /*<<< orphan*/  timer; } ;
struct cpufreq_policy {int /*<<< orphan*/  cpus; struct global_pstate_info* driver_data; } ;

/* Variables and functions */
 scalar_t__ MAX_RAMP_DOWN_TIME ; 
 unsigned int calc_global_pstate (scalar_t__,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_jiffies_64 () ; 
 unsigned int get_nominal_index () ; 
 void* idx_to_pstate (unsigned int) ; 
 unsigned int jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powernv_cpufreq_throttle_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  queue_gpstate_timer (struct global_pstate_info*) ; 
 int /*<<< orphan*/  rebooting ; 
 int /*<<< orphan*/  reset_gpstates (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  set_pstate ; 
 int /*<<< orphan*/  smp_call_function_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct powernv_smp_call_data*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throttled ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int powernv_cpufreq_target_index(struct cpufreq_policy *policy,
					unsigned int new_index)
{
	struct powernv_smp_call_data freq_data;
	unsigned int cur_msec, gpstate_idx;
	struct global_pstate_info *gpstates = policy->driver_data;

	if (unlikely(rebooting) && new_index != get_nominal_index())
		return 0;

	if (!throttled) {
		/* we don't want to be preempted while
		 * checking if the CPU frequency has been throttled
		 */
		preempt_disable();
		powernv_cpufreq_throttle_check(NULL);
		preempt_enable();
	}

	cur_msec = jiffies_to_msecs(get_jiffies_64());

	freq_data.pstate_id = idx_to_pstate(new_index);
	if (!gpstates) {
		freq_data.gpstate_id = freq_data.pstate_id;
		goto no_gpstate;
	}

	spin_lock(&gpstates->gpstate_lock);

	if (!gpstates->last_sampled_time) {
		gpstate_idx = new_index;
		gpstates->highest_lpstate_idx = new_index;
		goto gpstates_done;
	}

	if (gpstates->last_gpstate_idx < new_index) {
		gpstates->elapsed_time += cur_msec -
						 gpstates->last_sampled_time;

		/*
		 * If its has been ramping down for more than MAX_RAMP_DOWN_TIME
		 * we should be resetting all global pstate related data. Set it
		 * equal to local pstate to start fresh.
		 */
		if (gpstates->elapsed_time > MAX_RAMP_DOWN_TIME) {
			reset_gpstates(policy);
			gpstates->highest_lpstate_idx = new_index;
			gpstate_idx = new_index;
		} else {
		/* Elaspsed_time is less than 5 seconds, continue to rampdown */
			gpstate_idx = calc_global_pstate(gpstates->elapsed_time,
							 gpstates->highest_lpstate_idx,
							 new_index);
		}
	} else {
		reset_gpstates(policy);
		gpstates->highest_lpstate_idx = new_index;
		gpstate_idx = new_index;
	}

	/*
	 * If local pstate is equal to global pstate, rampdown is over
	 * So timer is not required to be queued.
	 */
	if (gpstate_idx != new_index)
		queue_gpstate_timer(gpstates);
	else
		del_timer_sync(&gpstates->timer);

gpstates_done:
	freq_data.gpstate_id = idx_to_pstate(gpstate_idx);
	gpstates->last_sampled_time = cur_msec;
	gpstates->last_gpstate_idx = gpstate_idx;
	gpstates->last_lpstate_idx = new_index;

	spin_unlock(&gpstates->gpstate_lock);

no_gpstate:
	/*
	 * Use smp_call_function to send IPI and execute the
	 * mtspr on target CPU.  We could do that without IPI
	 * if current CPU is within policy->cpus (core)
	 */
	smp_call_function_any(policy->cpus, set_pstate, &freq_data, 1);
	return 0;
}