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
struct child {int /*<<< orphan*/  status; int /*<<< orphan*/  done; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 scalar_t__ WEXITSTATUS (int /*<<< orphan*/ ) ; 
 scalar_t__ WIFEXITED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delchild (struct child*) ; 
 struct child* findchild (int,int) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_status ; 
 int waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
wait_child(pid_t pid)
{
	struct child *cp;
	sigset_t nset, oset;
	pid_t rv = 0;

	(void)sigemptyset(&nset);
	(void)sigaddset(&nset, SIGCHLD);
	(void)sigprocmask(SIG_BLOCK, &nset, &oset);
	/*
	 * If we have not already waited on the pid (via sigchild)
	 * wait on it now.  Otherwise, use the wait status stashed
	 * by sigchild.
	 */
	cp = findchild(pid, 1);
	if (cp == NULL || !cp->done)
		rv = waitpid(pid, &wait_status, 0);
	else
		wait_status = cp->status;
	if (cp != NULL)
		delchild(cp);
	(void)sigprocmask(SIG_SETMASK, &oset, NULL);
	if (rv == -1 || (WIFEXITED(wait_status) && WEXITSTATUS(wait_status)))
		return -1;
	else
		return 0;
}