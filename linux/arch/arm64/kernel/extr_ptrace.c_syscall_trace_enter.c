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
struct pt_regs {int syscallno; int /*<<< orphan*/ * regs; int /*<<< orphan*/  orig_x0; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_SYSCALL_ENTER ; 
 int /*<<< orphan*/  TIF_SYSCALL_EMU ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACEPOINT ; 
 int /*<<< orphan*/  audit_syscall_entry (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_syscall (struct pt_regs*) ; 
 int secure_computing (int /*<<< orphan*/ *) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_sys_enter (struct pt_regs*,int) ; 
 int /*<<< orphan*/  tracehook_report_syscall (struct pt_regs*,int /*<<< orphan*/ ) ; 

int syscall_trace_enter(struct pt_regs *regs)
{
	if (test_thread_flag(TIF_SYSCALL_TRACE) ||
		test_thread_flag(TIF_SYSCALL_EMU)) {
		tracehook_report_syscall(regs, PTRACE_SYSCALL_ENTER);
		if (!in_syscall(regs) || test_thread_flag(TIF_SYSCALL_EMU))
			return -1;
	}

	/* Do the secure computing after ptrace; failures should be fast. */
	if (secure_computing(NULL) == -1)
		return -1;

	if (test_thread_flag(TIF_SYSCALL_TRACEPOINT))
		trace_sys_enter(regs, regs->syscallno);

	audit_syscall_entry(regs->syscallno, regs->orig_x0, regs->regs[1],
			    regs->regs[2], regs->regs[3]);

	return regs->syscallno;
}