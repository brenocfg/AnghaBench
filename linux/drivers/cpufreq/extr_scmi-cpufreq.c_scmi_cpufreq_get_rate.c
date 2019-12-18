#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scmi_perf_ops {int (* freq_get ) (TYPE_1__*,int /*<<< orphan*/ ,unsigned long*,int) ;} ;
struct scmi_data {int /*<<< orphan*/  domain_id; } ;
struct cpufreq_policy {struct scmi_data* driver_data; } ;
struct TYPE_3__ {struct scmi_perf_ops* perf_ops; } ;

/* Variables and functions */
 struct cpufreq_policy* cpufreq_cpu_get_raw (unsigned int) ; 
 TYPE_1__* handle ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,unsigned long*,int) ; 

__attribute__((used)) static unsigned int scmi_cpufreq_get_rate(unsigned int cpu)
{
	struct cpufreq_policy *policy = cpufreq_cpu_get_raw(cpu);
	struct scmi_perf_ops *perf_ops = handle->perf_ops;
	struct scmi_data *priv = policy->driver_data;
	unsigned long rate;
	int ret;

	ret = perf_ops->freq_get(handle, priv->domain_id, &rate, false);
	if (ret)
		return 0;
	return rate / 1000;
}