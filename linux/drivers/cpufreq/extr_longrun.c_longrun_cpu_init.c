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
struct TYPE_2__ {int /*<<< orphan*/  max_freq; int /*<<< orphan*/  min_freq; } ;
struct cpufreq_policy {scalar_t__ cpu; TYPE_1__ cpuinfo; } ;

/* Variables and functions */
 int ENODEV ; 
 int longrun_determine_freqs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  longrun_get_policy (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  longrun_high_freq ; 
 int /*<<< orphan*/  longrun_low_freq ; 

__attribute__((used)) static int longrun_cpu_init(struct cpufreq_policy *policy)
{
	int result = 0;

	/* capability check */
	if (policy->cpu != 0)
		return -ENODEV;

	/* detect low and high frequency */
	result = longrun_determine_freqs(&longrun_low_freq, &longrun_high_freq);
	if (result)
		return result;

	/* cpuinfo and default policy values */
	policy->cpuinfo.min_freq = longrun_low_freq;
	policy->cpuinfo.max_freq = longrun_high_freq;
	longrun_get_policy(policy);

	return 0;
}