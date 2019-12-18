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

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_UMWAIT_CONTROL ; 
 int /*<<< orphan*/  orig_umwait_control_cached ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int umwait_cpu_offline(unsigned int cpu)
{
	/*
	 * This code is protected by the CPU hotplug already and
	 * orig_umwait_control_cached is never changed after it caches
	 * the original control MSR value in umwait_init(). So there
	 * is no race condition here.
	 */
	wrmsr(MSR_IA32_UMWAIT_CONTROL, orig_umwait_control_cached, 0);

	return 0;
}