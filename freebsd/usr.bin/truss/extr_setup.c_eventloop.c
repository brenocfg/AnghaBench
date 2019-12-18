#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct trussinfo {int flags; TYPE_5__* curthread; int /*<<< orphan*/  proclist; } ;
struct ptrace_lwpinfo {int pl_flags; int /*<<< orphan*/  pl_lwpid; } ;
struct TYPE_8__ {scalar_t__ si_signo; int si_code; int si_status; int /*<<< orphan*/  si_pid; } ;
typedef  TYPE_1__ siginfo_t ;
typedef  int /*<<< orphan*/  pl ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_10__ {int /*<<< orphan*/ * abi; } ;
struct TYPE_9__ {int /*<<< orphan*/  proc; } ;

/* Variables and functions */
#define  CLD_CONTINUED 133 
#define  CLD_DUMPED 132 
#define  CLD_EXITED 131 
#define  CLD_KILLED 130 
#define  CLD_STOPPED 129 
#define  CLD_TRAPPED 128 
 int COUNTONLY ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_7__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int NOSIGS ; 
 int PL_FLAG_BORN ; 
 int PL_FLAG_CHILD ; 
 int PL_FLAG_EXITED ; 
 int PL_FLAG_SCE ; 
 int PL_FLAG_SCX ; 
 int /*<<< orphan*/  PT_LWPINFO ; 
 int /*<<< orphan*/  PT_SYSCALL ; 
 int /*<<< orphan*/  P_ALL ; 
 scalar_t__ SIGCHLD ; 
 int SIGTRAP ; 
 int WEXITED ; 
 int WTRAPPED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  detach_all_procs (struct trussinfo*) ; 
 scalar_t__ detaching ; 
 int /*<<< orphan*/  enter_syscall (struct trussinfo*,TYPE_5__*,struct ptrace_lwpinfo*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit_syscall (struct trussinfo*,struct ptrace_lwpinfo*) ; 
 int /*<<< orphan*/  find_exit_thread (struct trussinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_proc (struct trussinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_thread (struct trussinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_proc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_thread (TYPE_5__*) ; 
 int /*<<< orphan*/  new_proc (struct trussinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  report_exit (struct trussinfo*,TYPE_1__*) ; 
 int /*<<< orphan*/  report_new_child (struct trussinfo*) ; 
 int /*<<< orphan*/  report_signal (struct trussinfo*,TYPE_1__*,struct ptrace_lwpinfo*) ; 
 int /*<<< orphan*/  report_thread_birth (struct trussinfo*) ; 
 int /*<<< orphan*/  report_thread_death (struct trussinfo*) ; 
 int /*<<< orphan*/  thread_exit_syscall (struct trussinfo*) ; 
 int waitid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

void
eventloop(struct trussinfo *info)
{
	struct ptrace_lwpinfo pl;
	siginfo_t si;
	int pending_signal;

	while (!LIST_EMPTY(&info->proclist)) {
		if (detaching) {
			detach_all_procs(info);
			return;
		}

		if (waitid(P_ALL, 0, &si, WTRAPPED | WEXITED) == -1) {
			if (errno == EINTR)
				continue;
			err(1, "Unexpected error from waitid");
		}

		assert(si.si_signo == SIGCHLD);

		switch (si.si_code) {
		case CLD_EXITED:
		case CLD_KILLED:
		case CLD_DUMPED:
			find_exit_thread(info, si.si_pid);
			if ((info->flags & COUNTONLY) == 0) {
				if (si.si_code == CLD_EXITED)
					thread_exit_syscall(info);
				report_exit(info, &si);
			}
			free_proc(info->curthread->proc);
			info->curthread = NULL;
			break;
		case CLD_TRAPPED:
			if (ptrace(PT_LWPINFO, si.si_pid, (caddr_t)&pl,
			    sizeof(pl)) == -1)
				err(1, "ptrace(PT_LWPINFO)");

			if (pl.pl_flags & PL_FLAG_CHILD) {
				new_proc(info, si.si_pid, pl.pl_lwpid);
				assert(LIST_FIRST(&info->proclist)->abi !=
				    NULL);
			} else if (pl.pl_flags & PL_FLAG_BORN)
				new_thread(find_proc(info, si.si_pid),
				    pl.pl_lwpid);
			find_thread(info, si.si_pid, pl.pl_lwpid);

			if (si.si_status == SIGTRAP &&
			    (pl.pl_flags & (PL_FLAG_BORN|PL_FLAG_EXITED|
			    PL_FLAG_SCE|PL_FLAG_SCX)) != 0) {
				if (pl.pl_flags & PL_FLAG_BORN) {
					if ((info->flags & COUNTONLY) == 0)
						report_thread_birth(info);
				} else if (pl.pl_flags & PL_FLAG_EXITED) {
					if ((info->flags & COUNTONLY) == 0)
						report_thread_death(info);
					free_thread(info->curthread);
					info->curthread = NULL;
				} else if (pl.pl_flags & PL_FLAG_SCE)
					enter_syscall(info, info->curthread, &pl);
				else if (pl.pl_flags & PL_FLAG_SCX)
					exit_syscall(info, &pl);
				pending_signal = 0;
			} else if (pl.pl_flags & PL_FLAG_CHILD) {
				if ((info->flags & COUNTONLY) == 0)
					report_new_child(info);
				pending_signal = 0;
			} else {
				if ((info->flags & NOSIGS) == 0)
					report_signal(info, &si, &pl);
				pending_signal = si.si_status;
			}
			ptrace(PT_SYSCALL, si.si_pid, (caddr_t)1,
			    pending_signal);
			break;
		case CLD_STOPPED:
			errx(1, "waitid reported CLD_STOPPED");
		case CLD_CONTINUED:
			break;
		}
	}
}