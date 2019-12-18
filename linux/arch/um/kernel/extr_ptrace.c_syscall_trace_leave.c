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
struct pt_regs {int /*<<< orphan*/  regs; } ;
struct TYPE_2__ {int ptrace; } ;

/* Variables and functions */
 int PT_DTRACE ; 
 int PT_PTRACED ; 
 int /*<<< orphan*/  TIF_SIGPENDING ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 int /*<<< orphan*/  audit_syscall_exit (struct pt_regs*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  send_sigtrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracehook_report_syscall_exit (struct pt_regs*,int /*<<< orphan*/ ) ; 

void syscall_trace_leave(struct pt_regs *regs)
{
	int ptraced = current->ptrace;

	audit_syscall_exit(regs);

	/* Fake a debug trap */
	if (ptraced & PT_DTRACE)
		send_sigtrap(&regs->regs, 0);

	if (!test_thread_flag(TIF_SYSCALL_TRACE))
		return;

	tracehook_report_syscall_exit(regs, 0);
	/* force do_signal() --> is_syscall() */
	if (ptraced & PT_PTRACED)
		set_thread_flag(TIF_SIGPENDING);
}