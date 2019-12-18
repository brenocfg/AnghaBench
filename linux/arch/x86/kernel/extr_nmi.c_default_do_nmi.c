#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int ip; } ;
struct TYPE_4__ {int /*<<< orphan*/  swallow; int /*<<< orphan*/  external; int /*<<< orphan*/  normal; } ;
struct TYPE_3__ {unsigned char (* get_nmi_reason ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NMI_LOCAL ; 
 unsigned char NMI_REASON_IOCHK ; 
 unsigned char NMI_REASON_MASK ; 
 unsigned char NMI_REASON_SERR ; 
 int /*<<< orphan*/  __this_cpu_add (int /*<<< orphan*/ ,int) ; 
 int __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  io_check_error (unsigned char,struct pt_regs*) ; 
 int /*<<< orphan*/  last_nmi_rip ; 
 int nmi_handle (int /*<<< orphan*/ ,struct pt_regs*) ; 
 int /*<<< orphan*/  nmi_reason_lock ; 
 TYPE_2__ nmi_stats ; 
 int /*<<< orphan*/  pci_serr_error (unsigned char,struct pt_regs*) ; 
 int /*<<< orphan*/  raw_spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reassert_nmi () ; 
 int /*<<< orphan*/  run_crash_ipi_callback (struct pt_regs*) ; 
 unsigned char stub1 () ; 
 int /*<<< orphan*/  swallow_nmi ; 
 int /*<<< orphan*/  unknown_nmi_error (unsigned char,struct pt_regs*) ; 
 TYPE_1__ x86_platform ; 

__attribute__((used)) static void default_do_nmi(struct pt_regs *regs)
{
	unsigned char reason = 0;
	int handled;
	bool b2b = false;

	/*
	 * CPU-specific NMI must be processed before non-CPU-specific
	 * NMI, otherwise we may lose it, because the CPU-specific
	 * NMI can not be detected/processed on other CPUs.
	 */

	/*
	 * Back-to-back NMIs are interesting because they can either
	 * be two NMI or more than two NMIs (any thing over two is dropped
	 * due to NMI being edge-triggered).  If this is the second half
	 * of the back-to-back NMI, assume we dropped things and process
	 * more handlers.  Otherwise reset the 'swallow' NMI behaviour
	 */
	if (regs->ip == __this_cpu_read(last_nmi_rip))
		b2b = true;
	else
		__this_cpu_write(swallow_nmi, false);

	__this_cpu_write(last_nmi_rip, regs->ip);

	handled = nmi_handle(NMI_LOCAL, regs);
	__this_cpu_add(nmi_stats.normal, handled);
	if (handled) {
		/*
		 * There are cases when a NMI handler handles multiple
		 * events in the current NMI.  One of these events may
		 * be queued for in the next NMI.  Because the event is
		 * already handled, the next NMI will result in an unknown
		 * NMI.  Instead lets flag this for a potential NMI to
		 * swallow.
		 */
		if (handled > 1)
			__this_cpu_write(swallow_nmi, true);
		return;
	}

	/*
	 * Non-CPU-specific NMI: NMI sources can be processed on any CPU.
	 *
	 * Another CPU may be processing panic routines while holding
	 * nmi_reason_lock. Check if the CPU issued the IPI for crash dumping,
	 * and if so, call its callback directly.  If there is no CPU preparing
	 * crash dump, we simply loop here.
	 */
	while (!raw_spin_trylock(&nmi_reason_lock)) {
		run_crash_ipi_callback(regs);
		cpu_relax();
	}

	reason = x86_platform.get_nmi_reason();

	if (reason & NMI_REASON_MASK) {
		if (reason & NMI_REASON_SERR)
			pci_serr_error(reason, regs);
		else if (reason & NMI_REASON_IOCHK)
			io_check_error(reason, regs);
#ifdef CONFIG_X86_32
		/*
		 * Reassert NMI in case it became active
		 * meanwhile as it's edge-triggered:
		 */
		reassert_nmi();
#endif
		__this_cpu_add(nmi_stats.external, 1);
		raw_spin_unlock(&nmi_reason_lock);
		return;
	}
	raw_spin_unlock(&nmi_reason_lock);

	/*
	 * Only one NMI can be latched at a time.  To handle
	 * this we may process multiple nmi handlers at once to
	 * cover the case where an NMI is dropped.  The downside
	 * to this approach is we may process an NMI prematurely,
	 * while its real NMI is sitting latched.  This will cause
	 * an unknown NMI on the next run of the NMI processing.
	 *
	 * We tried to flag that condition above, by setting the
	 * swallow_nmi flag when we process more than one event.
	 * This condition is also only present on the second half
	 * of a back-to-back NMI, so we flag that condition too.
	 *
	 * If both are true, we assume we already processed this
	 * NMI previously and we swallow it.  Otherwise we reset
	 * the logic.
	 *
	 * There are scenarios where we may accidentally swallow
	 * a 'real' unknown NMI.  For example, while processing
	 * a perf NMI another perf NMI comes in along with a
	 * 'real' unknown NMI.  These two NMIs get combined into
	 * one (as descibed above).  When the next NMI gets
	 * processed, it will be flagged by perf as handled, but
	 * noone will know that there was a 'real' unknown NMI sent
	 * also.  As a result it gets swallowed.  Or if the first
	 * perf NMI returns two events handled then the second
	 * NMI will get eaten by the logic below, again losing a
	 * 'real' unknown NMI.  But this is the best we can do
	 * for now.
	 */
	if (b2b && __this_cpu_read(swallow_nmi))
		__this_cpu_add(nmi_stats.swallow, 1);
	else
		unknown_nmi_error(reason, regs);
}