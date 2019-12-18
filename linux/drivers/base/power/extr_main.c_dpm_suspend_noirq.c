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
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpuidle_pause () ; 
 int /*<<< orphan*/  device_wakeup_arm_wake_irqs () ; 
 int dpm_noirq_suspend_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpm_resume_noirq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resume_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  suspend_device_irqs () ; 

int dpm_suspend_noirq(pm_message_t state)
{
	int ret;

	cpuidle_pause();

	device_wakeup_arm_wake_irqs();
	suspend_device_irqs();

	ret = dpm_noirq_suspend_devices(state);
	if (ret)
		dpm_resume_noirq(resume_event(state));

	return ret;
}