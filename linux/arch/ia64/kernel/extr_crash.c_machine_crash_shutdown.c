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
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ia64_set_psr_mc () ; 
 int /*<<< orphan*/  kdump_cpu_freeze ; 
 int /*<<< orphan*/  kdump_in_progress ; 
 int /*<<< orphan*/  kdump_smp_send_init () ; 
 int /*<<< orphan*/  kdump_smp_send_stop () ; 
 scalar_t__ kdump_wait_cpu_freeze () ; 
 int /*<<< orphan*/  kexec_disable_iosapic () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  unw_init_running (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
machine_crash_shutdown(struct pt_regs *pt)
{
	/* This function is only called after the system
	 * has paniced or is otherwise in a critical state.
	 * The minimum amount of code to allow a kexec'd kernel
	 * to run successfully needs to happen here.
	 *
	 * In practice this means shooting down the other cpus in
	 * an SMP system.
	 */
	kexec_disable_iosapic();
#ifdef CONFIG_SMP
	/*
	 * If kdump_on_init is set and an INIT is asserted here, kdump will
	 * be started again via INIT monarch.
	 */
	local_irq_disable();
	ia64_set_psr_mc();	/* mask MCA/INIT */
	if (atomic_inc_return(&kdump_in_progress) != 1)
		unw_init_running(kdump_cpu_freeze, NULL);

	/*
	 * Now this cpu is ready for kdump.
	 * Stop all others by IPI or INIT.  They could receive INIT from
	 * outside and might be INIT monarch, but only thing they have to
	 * do is falling into kdump_cpu_freeze().
	 *
	 * If an INIT is asserted here:
	 * - All receivers might be slaves, since some of cpus could already
	 *   be frozen and INIT might be masked on monarch.  In this case,
	 *   all slaves will be frozen soon since kdump_in_progress will let
	 *   them into DIE_INIT_SLAVE_LEAVE.
	 * - One might be a monarch, but INIT rendezvous will fail since
	 *   at least this cpu already have INIT masked so it never join
	 *   to the rendezvous.  In this case, all slaves and monarch will
	 *   be frozen soon with no wait since the INIT rendezvous is skipped
	 *   by kdump_in_progress.
	 */
	kdump_smp_send_stop();
	/* not all cpu response to IPI, send INIT to freeze them */
	if (kdump_wait_cpu_freeze()) {
		kdump_smp_send_init();
		/* wait again, don't go ahead if possible */
		kdump_wait_cpu_freeze();
	}
#endif
}