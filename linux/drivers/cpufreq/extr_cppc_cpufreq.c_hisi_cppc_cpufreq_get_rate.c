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
typedef  int /*<<< orphan*/  u64 ;
struct cppc_cpudata {int dummy; } ;

/* Variables and functions */
 unsigned int EIO ; 
 struct cppc_cpudata** all_cpu_data ; 
 unsigned int cppc_cpufreq_perf_to_khz (struct cppc_cpudata*,int /*<<< orphan*/ ) ; 
 int cppc_get_desired_perf (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int hisi_cppc_cpufreq_get_rate(unsigned int cpunum)
{
	struct cppc_cpudata *cpudata = all_cpu_data[cpunum];
	u64 desired_perf;
	int ret;

	ret = cppc_get_desired_perf(cpunum, &desired_perf);
	if (ret < 0)
		return -EIO;

	return cppc_cpufreq_perf_to_khz(cpudata, desired_perf);
}