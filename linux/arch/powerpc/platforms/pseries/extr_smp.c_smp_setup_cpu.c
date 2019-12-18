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
 int /*<<< orphan*/  CPU_STATE_ONLINE ; 
 int /*<<< orphan*/  FW_FEATURE_SPLPAR ; 
 int boot_cpuid ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ ) ; 
 scalar_t__ firmware_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_spin_mask ; 
 int /*<<< orphan*/  set_cpu_current_state (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_default_offline_state (int) ; 
 int /*<<< orphan*/  vpa_init (int) ; 
 int /*<<< orphan*/  xics_setup_cpu () ; 
 scalar_t__ xive_enabled () ; 
 int /*<<< orphan*/  xive_smp_setup_cpu () ; 

__attribute__((used)) static void smp_setup_cpu(int cpu)
{
	if (xive_enabled())
		xive_smp_setup_cpu();
	else if (cpu != boot_cpuid)
		xics_setup_cpu();

	if (firmware_has_feature(FW_FEATURE_SPLPAR))
		vpa_init(cpu);

	cpumask_clear_cpu(cpu, of_spin_mask);
#ifdef CONFIG_HOTPLUG_CPU
	set_cpu_current_state(cpu, CPU_STATE_ONLINE);
	set_default_offline_state(cpu);
#endif
}