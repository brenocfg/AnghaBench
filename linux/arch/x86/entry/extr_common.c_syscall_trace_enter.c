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
typedef  int u32 ;
struct thread_info {int /*<<< orphan*/  flags; } ;
struct seccomp_data {int arch; long nr; int /*<<< orphan*/ * args; int /*<<< orphan*/  instruction_pointer; } ;
struct pt_regs {long orig_ax; int /*<<< orphan*/  bp; int /*<<< orphan*/  di; int /*<<< orphan*/  si; int /*<<< orphan*/  dx; int /*<<< orphan*/  cx; int /*<<< orphan*/  bx; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  r10; int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int AUDIT_ARCH_I386 ; 
 int AUDIT_ARCH_X86_64 ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CONFIG_DEBUG_ENTRY ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACEPOINT ; 
 int _TIF_SECCOMP ; 
 int _TIF_SYSCALL_EMU ; 
 int _TIF_SYSCALL_TRACE ; 
 unsigned long __secure_computing (struct seccomp_data*) ; 
 int /*<<< orphan*/  current ; 
 struct thread_info* current_thread_info () ; 
 int /*<<< orphan*/  do_audit_syscall_entry (struct pt_regs*,int) ; 
 scalar_t__ in_ia32_syscall () ; 
 struct pt_regs* task_pt_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_sys_enter (struct pt_regs*,long) ; 
 unsigned long tracehook_report_syscall_entry (struct pt_regs*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long syscall_trace_enter(struct pt_regs *regs)
{
	u32 arch = in_ia32_syscall() ? AUDIT_ARCH_I386 : AUDIT_ARCH_X86_64;

	struct thread_info *ti = current_thread_info();
	unsigned long ret = 0;
	u32 work;

	if (IS_ENABLED(CONFIG_DEBUG_ENTRY))
		BUG_ON(regs != task_pt_regs(current));

	work = READ_ONCE(ti->flags);

	if (work & (_TIF_SYSCALL_TRACE | _TIF_SYSCALL_EMU)) {
		ret = tracehook_report_syscall_entry(regs);
		if (ret || (work & _TIF_SYSCALL_EMU))
			return -1L;
	}

#ifdef CONFIG_SECCOMP
	/*
	 * Do seccomp after ptrace, to catch any tracer changes.
	 */
	if (work & _TIF_SECCOMP) {
		struct seccomp_data sd;

		sd.arch = arch;
		sd.nr = regs->orig_ax;
		sd.instruction_pointer = regs->ip;
#ifdef CONFIG_X86_64
		if (arch == AUDIT_ARCH_X86_64) {
			sd.args[0] = regs->di;
			sd.args[1] = regs->si;
			sd.args[2] = regs->dx;
			sd.args[3] = regs->r10;
			sd.args[4] = regs->r8;
			sd.args[5] = regs->r9;
		} else
#endif
		{
			sd.args[0] = regs->bx;
			sd.args[1] = regs->cx;
			sd.args[2] = regs->dx;
			sd.args[3] = regs->si;
			sd.args[4] = regs->di;
			sd.args[5] = regs->bp;
		}

		ret = __secure_computing(&sd);
		if (ret == -1)
			return ret;
	}
#endif

	if (unlikely(test_thread_flag(TIF_SYSCALL_TRACEPOINT)))
		trace_sys_enter(regs, regs->orig_ax);

	do_audit_syscall_entry(regs, arch);

	return ret ?: regs->orig_ax;
}