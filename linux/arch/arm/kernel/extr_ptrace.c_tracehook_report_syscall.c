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
struct pt_regs {unsigned long ARM_ip; } ;
typedef  enum ptrace_syscall_dir { ____Placeholder_ptrace_syscall_dir } ptrace_syscall_dir ;
struct TYPE_2__ {int syscall; } ;

/* Variables and functions */
 int PTRACE_SYSCALL_EXIT ; 
 TYPE_1__* current_thread_info () ; 
 scalar_t__ tracehook_report_syscall_entry (struct pt_regs*) ; 
 int /*<<< orphan*/  tracehook_report_syscall_exit (struct pt_regs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tracehook_report_syscall(struct pt_regs *regs,
				    enum ptrace_syscall_dir dir)
{
	unsigned long ip;

	/*
	 * IP is used to denote syscall entry/exit:
	 * IP = 0 -> entry, =1 -> exit
	 */
	ip = regs->ARM_ip;
	regs->ARM_ip = dir;

	if (dir == PTRACE_SYSCALL_EXIT)
		tracehook_report_syscall_exit(regs, 0);
	else if (tracehook_report_syscall_entry(regs))
		current_thread_info()->syscall = -1;

	regs->ARM_ip = ip;
}