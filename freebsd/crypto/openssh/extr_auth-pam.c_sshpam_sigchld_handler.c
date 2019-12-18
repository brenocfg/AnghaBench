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
struct TYPE_2__ {int /*<<< orphan*/  pam_thread; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  SIGCHLD ; 
 scalar_t__ SIGTERM ; 
 int /*<<< orphan*/  SIG_DFL ; 
 scalar_t__ WEXITSTATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIFEXITED (int /*<<< orphan*/ ) ; 
 scalar_t__ WIFSIGNALED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WNOHANG ; 
 scalar_t__ WTERMSIG (int /*<<< orphan*/ ) ; 
 TYPE_1__* cleanup_ctxt ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sigdie (char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshpam_thread_status ; 
 int waitpid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sshpam_sigchld_handler(int sig)
{
	signal(SIGCHLD, SIG_DFL);
	if (cleanup_ctxt == NULL)
		return;	/* handler called after PAM cleanup, shouldn't happen */
	if (waitpid(cleanup_ctxt->pam_thread, &sshpam_thread_status, WNOHANG)
	    <= 0) {
		/* PAM thread has not exitted, privsep slave must have */
		kill(cleanup_ctxt->pam_thread, SIGTERM);
		while (waitpid(cleanup_ctxt->pam_thread,
		    &sshpam_thread_status, 0) == -1) {
			if (errno == EINTR)
				continue;
			return;
		}
	}
	if (WIFSIGNALED(sshpam_thread_status) &&
	    WTERMSIG(sshpam_thread_status) == SIGTERM)
		return;	/* terminated by pthread_cancel */
	if (!WIFEXITED(sshpam_thread_status))
		sigdie("PAM: authentication thread exited unexpectedly");
	if (WEXITSTATUS(sshpam_thread_status) != 0)
		sigdie("PAM: authentication thread exited uncleanly");
}