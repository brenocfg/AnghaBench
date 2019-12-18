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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_IO_APIC () ; 
 int /*<<< orphan*/  cpu_crash_vmclear_loaded_vmcss () ; 
 int /*<<< orphan*/  cpu_emergency_stop_pt () ; 
 int /*<<< orphan*/  cpu_emergency_svm_disable () ; 
 int /*<<< orphan*/  cpu_emergency_vmxoff () ; 
 int /*<<< orphan*/  crash_save_cpu (struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crash_smp_send_stop () ; 
 int /*<<< orphan*/  hpet_disable () ; 
 int /*<<< orphan*/  ioapic_zap_locks () ; 
 int /*<<< orphan*/  lapic_shutdown () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  restore_boot_irq_mode () ; 
 int /*<<< orphan*/  safe_smp_processor_id () ; 

void native_machine_crash_shutdown(struct pt_regs *regs)
{
	/* This function is only called after the system
	 * has panicked or is otherwise in a critical state.
	 * The minimum amount of code to allow a kexec'd kernel
	 * to run successfully needs to happen here.
	 *
	 * In practice this means shooting down the other cpus in
	 * an SMP system.
	 */
	/* The kernel is broken so disable interrupts */
	local_irq_disable();

	crash_smp_send_stop();

	/*
	 * VMCLEAR VMCSs loaded on this cpu if needed.
	 */
	cpu_crash_vmclear_loaded_vmcss();

	/* Booting kdump kernel with VMX or SVM enabled won't work,
	 * because (among other limitations) we can't disable paging
	 * with the virt flags.
	 */
	cpu_emergency_vmxoff();
	cpu_emergency_svm_disable();

	/*
	 * Disable Intel PT to stop its logging
	 */
	cpu_emergency_stop_pt();

#ifdef CONFIG_X86_IO_APIC
	/* Prevent crash_kexec() from deadlocking on ioapic_lock. */
	ioapic_zap_locks();
	clear_IO_APIC();
#endif
	lapic_shutdown();
	restore_boot_irq_mode();
#ifdef CONFIG_HPET_TIMER
	hpet_disable();
#endif
	crash_save_cpu(regs, safe_smp_processor_id());
}