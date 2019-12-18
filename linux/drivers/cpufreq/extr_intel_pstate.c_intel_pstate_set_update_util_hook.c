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
struct TYPE_2__ {scalar_t__ time; } ;
struct cpudata {int update_util_set; int /*<<< orphan*/  update_util; TYPE_1__ sample; } ;

/* Variables and functions */
 struct cpudata** all_cpu_data ; 
 int /*<<< orphan*/  cpufreq_add_update_util_hook (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hwp_active ; 
 int /*<<< orphan*/  hwp_boost ; 
 int /*<<< orphan*/  intel_pstate_update_util ; 
 int /*<<< orphan*/  intel_pstate_update_util_hwp ; 

__attribute__((used)) static void intel_pstate_set_update_util_hook(unsigned int cpu_num)
{
	struct cpudata *cpu = all_cpu_data[cpu_num];

	if (hwp_active && !hwp_boost)
		return;

	if (cpu->update_util_set)
		return;

	/* Prevent intel_pstate_update_util() from using stale data. */
	cpu->sample.time = 0;
	cpufreq_add_update_util_hook(cpu_num, &cpu->update_util,
				     (hwp_active ?
				      intel_pstate_update_util_hwp :
				      intel_pstate_update_util));
	cpu->update_util_set = true;
}