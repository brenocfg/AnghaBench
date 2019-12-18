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
struct cpufreq_policy {struct cpufreq_governor* governor; int /*<<< orphan*/  policy; void* max; void* min; int /*<<< orphan*/  cached_target_freq; int /*<<< orphan*/  constraints; int /*<<< orphan*/  cpuinfo; int /*<<< orphan*/  cpu; } ;
struct cpufreq_governor {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int (* verify ) (struct cpufreq_policy*) ;int (* setpolicy ) (struct cpufreq_policy*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FREQ_QOS_MAX ; 
 int /*<<< orphan*/  FREQ_QOS_MIN ; 
 int /*<<< orphan*/  UINT_MAX ; 
 TYPE_1__* cpufreq_driver ; 
 int /*<<< orphan*/  cpufreq_exit_governor (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  cpufreq_governor_limits (struct cpufreq_policy*) ; 
 int cpufreq_init_governor (struct cpufreq_policy*) ; 
 int cpufreq_start_governor (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  cpufreq_stop_governor (struct cpufreq_policy*) ; 
 void* freq_qos_read_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  sched_cpufreq_governor_change (struct cpufreq_policy*,struct cpufreq_governor*) ; 
 int stub1 (struct cpufreq_policy*) ; 
 int stub2 (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  trace_cpu_frequency_limits (struct cpufreq_policy*) ; 

int cpufreq_set_policy(struct cpufreq_policy *policy,
		       struct cpufreq_policy *new_policy)
{
	struct cpufreq_governor *old_gov;
	int ret;

	pr_debug("setting new policy for CPU %u: %u - %u kHz\n",
		 new_policy->cpu, new_policy->min, new_policy->max);

	memcpy(&new_policy->cpuinfo, &policy->cpuinfo, sizeof(policy->cpuinfo));

	/*
	 * PM QoS framework collects all the requests from users and provide us
	 * the final aggregated value here.
	 */
	new_policy->min = freq_qos_read_value(&policy->constraints, FREQ_QOS_MIN);
	new_policy->max = freq_qos_read_value(&policy->constraints, FREQ_QOS_MAX);

	/* verify the cpu speed can be set within this limit */
	ret = cpufreq_driver->verify(new_policy);
	if (ret)
		return ret;

	policy->min = new_policy->min;
	policy->max = new_policy->max;
	trace_cpu_frequency_limits(policy);

	policy->cached_target_freq = UINT_MAX;

	pr_debug("new min and max freqs are %u - %u kHz\n",
		 policy->min, policy->max);

	if (cpufreq_driver->setpolicy) {
		policy->policy = new_policy->policy;
		pr_debug("setting range\n");
		return cpufreq_driver->setpolicy(policy);
	}

	if (new_policy->governor == policy->governor) {
		pr_debug("governor limits update\n");
		cpufreq_governor_limits(policy);
		return 0;
	}

	pr_debug("governor switch\n");

	/* save old, working values */
	old_gov = policy->governor;
	/* end old governor */
	if (old_gov) {
		cpufreq_stop_governor(policy);
		cpufreq_exit_governor(policy);
	}

	/* start new governor */
	policy->governor = new_policy->governor;
	ret = cpufreq_init_governor(policy);
	if (!ret) {
		ret = cpufreq_start_governor(policy);
		if (!ret) {
			pr_debug("governor change\n");
			sched_cpufreq_governor_change(policy, old_gov);
			return 0;
		}
		cpufreq_exit_governor(policy);
	}

	/* new governor failed, so re-start old one */
	pr_debug("starting governor %s failed\n", policy->governor->name);
	if (old_gov) {
		policy->governor = old_gov;
		if (cpufreq_init_governor(policy))
			policy->governor = NULL;
		else
			cpufreq_start_governor(policy);
	}

	return ret;
}