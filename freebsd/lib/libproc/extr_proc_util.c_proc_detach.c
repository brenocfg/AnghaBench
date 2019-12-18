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
struct proc_handle {int flags; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 int EINVAL ; 
 scalar_t__ ESRCH ; 
 int PATTACH_RDONLY ; 
 int PRELEASE_HANG ; 
 int PRELEASE_KILL ; 
 int /*<<< orphan*/  PT_DETACH ; 
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  WUNTRACED ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_free (struct proc_handle*) ; 
 int /*<<< orphan*/  proc_getpid (struct proc_handle*) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

int
proc_detach(struct proc_handle *phdl, int reason)
{
	int status;
	pid_t pid;

	if (phdl == NULL)
		return (EINVAL);
	if (reason == PRELEASE_HANG)
		return (EINVAL);
	if (reason == PRELEASE_KILL) {
		kill(proc_getpid(phdl), SIGKILL);
		goto free;
	}
	if ((phdl->flags & PATTACH_RDONLY) != 0)
		goto free;
	pid = proc_getpid(phdl);
	if (ptrace(PT_DETACH, pid, 0, 0) != 0 && errno == ESRCH)
		goto free;
	if (errno == EBUSY) {
		kill(pid, SIGSTOP);
		waitpid(pid, &status, WUNTRACED);
		ptrace(PT_DETACH, pid, 0, 0);
		kill(pid, SIGCONT);
	}
free:
	proc_free(phdl);
	return (0);
}