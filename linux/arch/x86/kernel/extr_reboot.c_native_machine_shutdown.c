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
struct TYPE_2__ {int /*<<< orphan*/  (* iommu_shutdown ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clear_IO_APIC () ; 
 int /*<<< orphan*/  hpet_disable () ; 
 int /*<<< orphan*/  lapic_shutdown () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  restore_boot_irq_mode () ; 
 int /*<<< orphan*/  stop_other_cpus () ; 
 int /*<<< orphan*/  stub1 () ; 
 TYPE_1__ x86_platform ; 

void native_machine_shutdown(void)
{
	/* Stop the cpus and apics */
#ifdef CONFIG_X86_IO_APIC
	/*
	 * Disabling IO APIC before local APIC is a workaround for
	 * erratum AVR31 in "Intel Atom Processor C2000 Product Family
	 * Specification Update". In this situation, interrupts that target
	 * a Logical Processor whose Local APIC is either in the process of
	 * being hardware disabled or software disabled are neither delivered
	 * nor discarded. When this erratum occurs, the processor may hang.
	 *
	 * Even without the erratum, it still makes sense to quiet IO APIC
	 * before disabling Local APIC.
	 */
	clear_IO_APIC();
#endif

#ifdef CONFIG_SMP
	/*
	 * Stop all of the others. Also disable the local irq to
	 * not receive the per-cpu timer interrupt which may trigger
	 * scheduler's load balance.
	 */
	local_irq_disable();
	stop_other_cpus();
#endif

	lapic_shutdown();
	restore_boot_irq_mode();

#ifdef CONFIG_HPET_TIMER
	hpet_disable();
#endif

#ifdef CONFIG_X86_64
	x86_platform.iommu_shutdown();
#endif
}