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
struct pt_regs {unsigned long compat_sp; unsigned long sp; unsigned long x19; unsigned long x20; unsigned long pc; int /*<<< orphan*/  pmr_save; int /*<<< orphan*/  pstate; scalar_t__* regs; } ;
struct TYPE_3__ {scalar_t__ tp_value; } ;
struct TYPE_4__ {struct pt_regs cpu_context; TYPE_1__ uw; } ;
struct task_struct {int flags; TYPE_2__ thread; } ;
struct cpu_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM64_HAS_UAO ; 
 scalar_t__ ARM64_SSBD_FORCE_DISABLE ; 
 unsigned long CLONE_SETTLS ; 
 int /*<<< orphan*/  CONFIG_ARM64_UAO ; 
 int /*<<< orphan*/  GIC_PRIO_IRQON ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PF_KTHREAD ; 
 int /*<<< orphan*/  PSR_MODE_EL1h ; 
 int /*<<< orphan*/  PSR_UAO_BIT ; 
 scalar_t__ arm64_get_ssbd_state () ; 
 scalar_t__ cpus_have_const_cap (int /*<<< orphan*/ ) ; 
 struct pt_regs* current_pt_regs () ; 
 int /*<<< orphan*/  fpsimd_flush_task_state (struct task_struct*) ; 
 scalar_t__ is_compat_thread (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptrace_hw_copy_thread (struct task_struct*) ; 
 int /*<<< orphan*/  read_sysreg (int /*<<< orphan*/ ) ; 
 scalar_t__ ret_from_fork ; 
 int /*<<< orphan*/  set_ssbs_bit (struct pt_regs*) ; 
 scalar_t__ system_uses_irq_prio_masking () ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 
 int /*<<< orphan*/  task_thread_info (struct task_struct*) ; 
 int /*<<< orphan*/ * task_user_tls (struct task_struct*) ; 
 int /*<<< orphan*/  tpidr_el0 ; 

int copy_thread(unsigned long clone_flags, unsigned long stack_start,
		unsigned long stk_sz, struct task_struct *p)
{
	struct pt_regs *childregs = task_pt_regs(p);

	memset(&p->thread.cpu_context, 0, sizeof(struct cpu_context));

	/*
	 * In case p was allocated the same task_struct pointer as some
	 * other recently-exited task, make sure p is disassociated from
	 * any cpu that may have run that now-exited task recently.
	 * Otherwise we could erroneously skip reloading the FPSIMD
	 * registers for p.
	 */
	fpsimd_flush_task_state(p);

	if (likely(!(p->flags & PF_KTHREAD))) {
		*childregs = *current_pt_regs();
		childregs->regs[0] = 0;

		/*
		 * Read the current TLS pointer from tpidr_el0 as it may be
		 * out-of-sync with the saved value.
		 */
		*task_user_tls(p) = read_sysreg(tpidr_el0);

		if (stack_start) {
			if (is_compat_thread(task_thread_info(p)))
				childregs->compat_sp = stack_start;
			else
				childregs->sp = stack_start;
		}

		/*
		 * If a TLS pointer was passed to clone (4th argument), use it
		 * for the new thread.
		 */
		if (clone_flags & CLONE_SETTLS)
			p->thread.uw.tp_value = childregs->regs[3];
	} else {
		memset(childregs, 0, sizeof(struct pt_regs));
		childregs->pstate = PSR_MODE_EL1h;
		if (IS_ENABLED(CONFIG_ARM64_UAO) &&
		    cpus_have_const_cap(ARM64_HAS_UAO))
			childregs->pstate |= PSR_UAO_BIT;

		if (arm64_get_ssbd_state() == ARM64_SSBD_FORCE_DISABLE)
			set_ssbs_bit(childregs);

		if (system_uses_irq_prio_masking())
			childregs->pmr_save = GIC_PRIO_IRQON;

		p->thread.cpu_context.x19 = stack_start;
		p->thread.cpu_context.x20 = stk_sz;
	}
	p->thread.cpu_context.pc = (unsigned long)ret_from_fork;
	p->thread.cpu_context.sp = (unsigned long)childregs;

	ptrace_hw_copy_thread(p);

	return 0;
}