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
struct cpufreq_policy {int dummy; } ;
struct TYPE_2__ {scalar_t__ get; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct cpufreq_policy* cpufreq_cpu_acquire (unsigned int) ; 
 int /*<<< orphan*/  cpufreq_cpu_release (struct cpufreq_policy*) ; 
 TYPE_1__* cpufreq_driver ; 
 scalar_t__ cpufreq_suspended ; 
 int /*<<< orphan*/  cpufreq_verify_current_freq (struct cpufreq_policy*,int) ; 
 scalar_t__ has_target () ; 
 int /*<<< orphan*/  refresh_frequency_limits (struct cpufreq_policy*) ; 

void cpufreq_update_policy(unsigned int cpu)
{
	struct cpufreq_policy *policy = cpufreq_cpu_acquire(cpu);

	if (!policy)
		return;

	/*
	 * BIOS might change freq behind our back
	 * -> ask driver for current freq and notify governors about a change
	 */
	if (cpufreq_driver->get && has_target() &&
	    (cpufreq_suspended || WARN_ON(!cpufreq_verify_current_freq(policy, false))))
		goto unlock;

	refresh_frequency_limits(policy);

unlock:
	cpufreq_cpu_release(policy);
}