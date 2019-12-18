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
struct pt_regs {int /*<<< orphan*/  sp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SMP ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int NMI_EXECUTING ; 
 int NMI_LATCHED ; 
 scalar_t__ NMI_NOT_RUNNING ; 
 int /*<<< orphan*/  __nmi_count ; 
 scalar_t__ cpu_is_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_stack_reset () ; 
 int /*<<< orphan*/  debug_stack_set_zero () ; 
 int /*<<< orphan*/  default_do_nmi (struct pt_regs*) ; 
 int /*<<< orphan*/  ignore_nmis ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 int is_debug_stack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mds_user_clear_cpu_buffers () ; 
 int /*<<< orphan*/  nmi_cr2 ; 
 int /*<<< orphan*/  nmi_enter () ; 
 int /*<<< orphan*/  nmi_exit () ; 
 int /*<<< orphan*/  nmi_state ; 
 scalar_t__ read_cr2 () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ this_cpu_dec_return (int /*<<< orphan*/ ) ; 
 scalar_t__ this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_debug_stack ; 
 scalar_t__ user_mode (struct pt_regs*) ; 
 int /*<<< orphan*/  write_cr2 (scalar_t__) ; 

void
do_nmi(struct pt_regs *regs, long error_code)
{
	if (IS_ENABLED(CONFIG_SMP) && cpu_is_offline(smp_processor_id()))
		return;

	if (this_cpu_read(nmi_state) != NMI_NOT_RUNNING) {
		this_cpu_write(nmi_state, NMI_LATCHED);
		return;
	}
	this_cpu_write(nmi_state, NMI_EXECUTING);
	this_cpu_write(nmi_cr2, read_cr2());
nmi_restart:

#ifdef CONFIG_X86_64
	/*
	 * If we interrupted a breakpoint, it is possible that
	 * the nmi handler will have breakpoints too. We need to
	 * change the IDT such that breakpoints that happen here
	 * continue to use the NMI stack.
	 */
	if (unlikely(is_debug_stack(regs->sp))) {
		debug_stack_set_zero();
		this_cpu_write(update_debug_stack, 1);
	}
#endif

	nmi_enter();

	inc_irq_stat(__nmi_count);

	if (!ignore_nmis)
		default_do_nmi(regs);

	nmi_exit();

#ifdef CONFIG_X86_64
	if (unlikely(this_cpu_read(update_debug_stack))) {
		debug_stack_reset();
		this_cpu_write(update_debug_stack, 0);
	}
#endif

	if (unlikely(this_cpu_read(nmi_cr2) != read_cr2()))
		write_cr2(this_cpu_read(nmi_cr2));
	if (this_cpu_dec_return(nmi_state))
		goto nmi_restart;

	if (user_mode(regs))
		mds_user_clear_cpu_buffers();
}