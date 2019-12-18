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
struct cpufreq_policy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_HIGH ; 
 int /*<<< orphan*/  CPUFREQ_LOW ; 
 unsigned long cur_freq ; 
 int /*<<< orphan*/  do_set_cpu_speed (struct cpufreq_policy*,int /*<<< orphan*/ ) ; 
 unsigned long get_speed_proc () ; 
 scalar_t__ low_freq ; 
 scalar_t__ no_schedule ; 
 unsigned long ppc_proc_freq ; 
 scalar_t__ sleep_freq ; 

__attribute__((used)) static int pmac_cpufreq_resume(struct cpufreq_policy *policy)
{
	/* If we resume, first check if we have a get() function */
	if (get_speed_proc)
		cur_freq = get_speed_proc();
	else
		cur_freq = 0;

	/* We don't, hrm... we don't really know our speed here, best
	 * is that we force a switch to whatever it was, which is
	 * probably high speed due to our suspend() routine
	 */
	do_set_cpu_speed(policy, sleep_freq == low_freq ?
			 CPUFREQ_LOW : CPUFREQ_HIGH);

	ppc_proc_freq = cur_freq * 1000ul;

	no_schedule = 0;
	return 0;
}