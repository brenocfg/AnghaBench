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
struct cpufreq_policy {unsigned int cur; int /*<<< orphan*/  update; scalar_t__ fast_switch_enabled; int /*<<< orphan*/  cpu; } ;
struct TYPE_2__ {unsigned int (* get ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* cpufreq_driver ; 
 int /*<<< orphan*/  cpufreq_out_of_sync (struct cpufreq_policy*,unsigned int) ; 
 int /*<<< orphan*/  has_target () ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 unsigned int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int cpufreq_verify_current_freq(struct cpufreq_policy *policy, bool update)
{
	unsigned int new_freq;

	new_freq = cpufreq_driver->get(policy->cpu);
	if (!new_freq)
		return 0;

	/*
	 * If fast frequency switching is used with the given policy, the check
	 * against policy->cur is pointless, so skip it in that case.
	 */
	if (policy->fast_switch_enabled || !has_target())
		return new_freq;

	if (policy->cur != new_freq) {
		cpufreq_out_of_sync(policy, new_freq);
		if (update)
			schedule_work(&policy->update);
	}

	return new_freq;
}