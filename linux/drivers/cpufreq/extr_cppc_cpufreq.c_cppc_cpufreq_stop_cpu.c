#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cpufreq_policy {int cpu; } ;
struct TYPE_3__ {int /*<<< orphan*/  lowest_perf; } ;
struct TYPE_4__ {int /*<<< orphan*/  desired_perf; } ;
struct cppc_cpudata {TYPE_1__ perf_caps; TYPE_2__ perf_ctrls; } ;

/* Variables and functions */
 struct cppc_cpudata** all_cpu_data ; 
 int cppc_set_perf (int,TYPE_2__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void cppc_cpufreq_stop_cpu(struct cpufreq_policy *policy)
{
	int cpu_num = policy->cpu;
	struct cppc_cpudata *cpu = all_cpu_data[cpu_num];
	int ret;

	cpu->perf_ctrls.desired_perf = cpu->perf_caps.lowest_perf;

	ret = cppc_set_perf(cpu_num, &cpu->perf_ctrls);
	if (ret)
		pr_debug("Err setting perf value:%d on CPU:%d. ret:%d\n",
				cpu->perf_caps.lowest_perf, cpu_num, ret);
}