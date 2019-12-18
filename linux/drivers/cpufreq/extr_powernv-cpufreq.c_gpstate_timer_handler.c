#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct powernv_smp_call_data {scalar_t__ gpstate_id; scalar_t__ pstate_id; } ;
struct TYPE_2__ {scalar_t__ expires; } ;
struct global_pstate_info {unsigned int last_sampled_time; scalar_t__ elapsed_time; int highest_lpstate_idx; int last_gpstate_idx; int last_lpstate_idx; int /*<<< orphan*/  gpstate_lock; TYPE_1__ timer; struct cpufreq_policy* policy; } ;
struct cpufreq_policy {int /*<<< orphan*/  cpus; } ;

/* Variables and functions */
 scalar_t__ MAX_RAMP_DOWN_TIME ; 
 int /*<<< orphan*/  SPRN_PMCR ; 
 int /*<<< orphan*/  add_timer_on (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int calc_global_pstate (scalar_t__,int,int) ; 
 int /*<<< orphan*/  cpumask_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ extract_global_pstate (unsigned long) ; 
 scalar_t__ extract_local_pstate (unsigned long) ; 
 struct global_pstate_info* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 unsigned long get_pmspr (int /*<<< orphan*/ ) ; 
 struct global_pstate_info* gpstates ; 
 scalar_t__ idx_to_pstate (int) ; 
 scalar_t__ jiffies ; 
 unsigned int jiffies_to_msecs (scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int pstate_to_idx (scalar_t__) ; 
 int /*<<< orphan*/  queue_gpstate_timer (struct global_pstate_info*) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 int /*<<< orphan*/  reset_gpstates (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  set_pstate (struct powernv_smp_call_data*) ; 
 int /*<<< orphan*/  spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 

void gpstate_timer_handler(struct timer_list *t)
{
	struct global_pstate_info *gpstates = from_timer(gpstates, t, timer);
	struct cpufreq_policy *policy = gpstates->policy;
	int gpstate_idx, lpstate_idx;
	unsigned long val;
	unsigned int time_diff = jiffies_to_msecs(jiffies)
					- gpstates->last_sampled_time;
	struct powernv_smp_call_data freq_data;

	if (!spin_trylock(&gpstates->gpstate_lock))
		return;
	/*
	 * If the timer has migrated to the different cpu then bring
	 * it back to one of the policy->cpus
	 */
	if (!cpumask_test_cpu(raw_smp_processor_id(), policy->cpus)) {
		gpstates->timer.expires = jiffies + msecs_to_jiffies(1);
		add_timer_on(&gpstates->timer, cpumask_first(policy->cpus));
		spin_unlock(&gpstates->gpstate_lock);
		return;
	}

	/*
	 * If PMCR was last updated was using fast_swtich then
	 * We may have wrong in gpstate->last_lpstate_idx
	 * value. Hence, read from PMCR to get correct data.
	 */
	val = get_pmspr(SPRN_PMCR);
	freq_data.gpstate_id = extract_global_pstate(val);
	freq_data.pstate_id = extract_local_pstate(val);
	if (freq_data.gpstate_id  == freq_data.pstate_id) {
		reset_gpstates(policy);
		spin_unlock(&gpstates->gpstate_lock);
		return;
	}

	gpstates->last_sampled_time += time_diff;
	gpstates->elapsed_time += time_diff;

	if (gpstates->elapsed_time > MAX_RAMP_DOWN_TIME) {
		gpstate_idx = pstate_to_idx(freq_data.pstate_id);
		lpstate_idx = gpstate_idx;
		reset_gpstates(policy);
		gpstates->highest_lpstate_idx = gpstate_idx;
	} else {
		lpstate_idx = pstate_to_idx(freq_data.pstate_id);
		gpstate_idx = calc_global_pstate(gpstates->elapsed_time,
						 gpstates->highest_lpstate_idx,
						 lpstate_idx);
	}
	freq_data.gpstate_id = idx_to_pstate(gpstate_idx);
	gpstates->last_gpstate_idx = gpstate_idx;
	gpstates->last_lpstate_idx = lpstate_idx;
	/*
	 * If local pstate is equal to global pstate, rampdown is over
	 * So timer is not required to be queued.
	 */
	if (gpstate_idx != gpstates->last_lpstate_idx)
		queue_gpstate_timer(gpstates);

	set_pstate(&freq_data);
	spin_unlock(&gpstates->gpstate_lock);
}