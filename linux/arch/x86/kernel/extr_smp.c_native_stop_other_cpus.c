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
 int /*<<< orphan*/  NMI_VECTOR ; 
 int /*<<< orphan*/  REBOOT_VECTOR ; 
 int USEC_PER_MSEC ; 
 unsigned long USEC_PER_SEC ; 
 int /*<<< orphan*/  apic_send_IPI_allbutself (int /*<<< orphan*/ ) ; 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_info ; 
 int /*<<< orphan*/  disable_local_APIC () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mcheck_cpu_clear (int /*<<< orphan*/ ) ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 
 scalar_t__ reboot_force ; 
 int /*<<< orphan*/  register_stop_handler () ; 
 int /*<<< orphan*/  safe_smp_processor_id () ; 
 int /*<<< orphan*/  smp_no_nmi_ipi ; 
 int /*<<< orphan*/  stopping_cpu ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void native_stop_other_cpus(int wait)
{
	unsigned long flags;
	unsigned long timeout;

	if (reboot_force)
		return;

	/*
	 * Use an own vector here because smp_call_function
	 * does lots of things not suitable in a panic situation.
	 */

	/*
	 * We start by using the REBOOT_VECTOR irq.
	 * The irq is treated as a sync point to allow critical
	 * regions of code on other cpus to release their spin locks
	 * and re-enable irqs.  Jumping straight to an NMI might
	 * accidentally cause deadlocks with further shutdown/panic
	 * code.  By syncing, we give the cpus up to one second to
	 * finish their work before we force them off with the NMI.
	 */
	if (num_online_cpus() > 1) {
		/* did someone beat us here? */
		if (atomic_cmpxchg(&stopping_cpu, -1, safe_smp_processor_id()) != -1)
			return;

		/* sync above data before sending IRQ */
		wmb();

		apic_send_IPI_allbutself(REBOOT_VECTOR);

		/*
		 * Don't wait longer than a second for IPI completion. The
		 * wait request is not checked here because that would
		 * prevent an NMI shutdown attempt in case that not all
		 * CPUs reach shutdown state.
		 */
		timeout = USEC_PER_SEC;
		while (num_online_cpus() > 1 && timeout--)
			udelay(1);
	}

	/* if the REBOOT_VECTOR didn't work, try with the NMI */
	if (num_online_cpus() > 1) {
		/*
		 * If NMI IPI is enabled, try to register the stop handler
		 * and send the IPI. In any case try to wait for the other
		 * CPUs to stop.
		 */
		if (!smp_no_nmi_ipi && !register_stop_handler()) {
			/* Sync above data before sending IRQ */
			wmb();

			pr_emerg("Shutting down cpus with NMI\n");

			apic_send_IPI_allbutself(NMI_VECTOR);
		}
		/*
		 * Don't wait longer than 10 ms if the caller didn't
		 * reqeust it. If wait is true, the machine hangs here if
		 * one or more CPUs do not reach shutdown state.
		 */
		timeout = USEC_PER_MSEC * 10;
		while (num_online_cpus() > 1 && (wait || timeout--))
			udelay(1);
	}

	local_irq_save(flags);
	disable_local_APIC();
	mcheck_cpu_clear(this_cpu_ptr(&cpu_info));
	local_irq_restore(flags);
}