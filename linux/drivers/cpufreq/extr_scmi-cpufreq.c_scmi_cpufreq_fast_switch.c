#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scmi_perf_ops {int /*<<< orphan*/  (* freq_set ) (TYPE_2__*,int /*<<< orphan*/ ,unsigned int,int) ;} ;
struct scmi_data {int /*<<< orphan*/  domain_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_freq; } ;
struct cpufreq_policy {TYPE_1__ cpuinfo; int /*<<< orphan*/  related_cpus; struct scmi_data* driver_data; } ;
struct TYPE_5__ {struct scmi_perf_ops* perf_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_set_freq_scale (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_2__* handle ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static unsigned int scmi_cpufreq_fast_switch(struct cpufreq_policy *policy,
					     unsigned int target_freq)
{
	struct scmi_data *priv = policy->driver_data;
	struct scmi_perf_ops *perf_ops = handle->perf_ops;

	if (!perf_ops->freq_set(handle, priv->domain_id,
				target_freq * 1000, true)) {
		arch_set_freq_scale(policy->related_cpus, target_freq,
				    policy->cpuinfo.max_freq);
		return target_freq;
	}

	return 0;
}