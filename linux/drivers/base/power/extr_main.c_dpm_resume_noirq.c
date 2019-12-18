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
 int /*<<< orphan*/  cpuidle_resume () ; 
 int /*<<< orphan*/  device_wakeup_disarm_wake_irqs () ; 
 int /*<<< orphan*/  dpm_noirq_resume_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resume_device_irqs () ; 

void dpm_resume_noirq(pm_message_t state)
{
	dpm_noirq_resume_devices(state);

	resume_device_irqs();
	device_wakeup_disarm_wake_irqs();

	cpuidle_resume();
}