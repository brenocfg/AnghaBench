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
struct ssh {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  WNOHANG ; 
 scalar_t__ child_terminated ; 
 int /*<<< orphan*/  debug (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  session_close_by_pid (struct ssh*,scalar_t__,int) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
collect_children(struct ssh *ssh)
{
	pid_t pid;
	sigset_t oset, nset;
	int status;

	/* block SIGCHLD while we check for dead children */
	sigemptyset(&nset);
	sigaddset(&nset, SIGCHLD);
	sigprocmask(SIG_BLOCK, &nset, &oset);
	if (child_terminated) {
		debug("Received SIGCHLD.");
		while ((pid = waitpid(-1, &status, WNOHANG)) > 0 ||
		    (pid < 0 && errno == EINTR))
			if (pid > 0)
				session_close_by_pid(ssh, pid, status);
		child_terminated = 0;
	}
	sigprocmask(SIG_SETMASK, &oset, NULL);
}