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
struct ptrace_lwpinfo32 {int /*<<< orphan*/  pl_syscall_narg; int /*<<< orphan*/  pl_syscall_code; int /*<<< orphan*/  pl_child_pid; int /*<<< orphan*/  pl_tdname; int /*<<< orphan*/  pl_siginfo; int /*<<< orphan*/  pl_siglist; int /*<<< orphan*/  pl_sigmask; int /*<<< orphan*/  pl_flags; int /*<<< orphan*/  pl_event; int /*<<< orphan*/  pl_lwpid; } ;
struct ptrace_lwpinfo {int /*<<< orphan*/  pl_syscall_narg; int /*<<< orphan*/  pl_syscall_code; int /*<<< orphan*/  pl_child_pid; int /*<<< orphan*/  pl_tdname; int /*<<< orphan*/  pl_siginfo; int /*<<< orphan*/  pl_siglist; int /*<<< orphan*/  pl_sigmask; int /*<<< orphan*/  pl_flags; int /*<<< orphan*/  pl_event; int /*<<< orphan*/  pl_lwpid; } ;

/* Variables and functions */
 int /*<<< orphan*/  elf_convert_siginfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
elf_convert_lwpinfo(struct ptrace_lwpinfo32 *pld, struct ptrace_lwpinfo *pls)
{

	pld->pl_lwpid = pls->pl_lwpid;
	pld->pl_event = pls->pl_event;
	pld->pl_flags = pls->pl_flags;
	pld->pl_sigmask = pls->pl_sigmask;
	pld->pl_siglist = pls->pl_siglist;
	elf_convert_siginfo(&pld->pl_siginfo, &pls->pl_siginfo);
	memcpy(pld->pl_tdname, pls->pl_tdname, sizeof(pld->pl_tdname));
	pld->pl_child_pid = pls->pl_child_pid;
	pld->pl_syscall_code = pls->pl_syscall_code;
	pld->pl_syscall_narg = pls->pl_syscall_narg;
}