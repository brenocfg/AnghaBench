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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  SLEEP_FREQ ; 
 int /*<<< orphan*/  cpufreq_cpu_get (int /*<<< orphan*/ ) ; 
 int cpufreq_driver_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int no_cpufreq_access ; 

__attribute__((used)) static int s5pv210_cpufreq_reboot_notifier_event(struct notifier_block *this,
						 unsigned long event, void *ptr)
{
	int ret;

	ret = cpufreq_driver_target(cpufreq_cpu_get(0), SLEEP_FREQ, 0);
	if (ret < 0)
		return NOTIFY_BAD;

	no_cpufreq_access = true;
	return NOTIFY_DONE;
}