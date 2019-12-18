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
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIGTTIN ; 
 int /*<<< orphan*/  SIGTTOU ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int create_exclusive (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  handle_pending_signals () ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  usleep (unsigned int) ; 

int
dot_lock(const char *fname, int pollinterval)
{
	char path[MAXPATHLEN];
	sigset_t nset, oset;
	int retval;

	(void)sigemptyset(&nset);
	(void)sigaddset(&nset, SIGHUP);
	(void)sigaddset(&nset, SIGINT);
	(void)sigaddset(&nset, SIGQUIT);
	(void)sigaddset(&nset, SIGTERM);
	(void)sigaddset(&nset, SIGTTIN);
	(void)sigaddset(&nset, SIGTTOU);
	(void)sigaddset(&nset, SIGTSTP);
	(void)sigaddset(&nset, SIGCHLD);

	(void)snprintf(path, sizeof(path), "%s.lock", fname);

	retval = -1;
	for (;;) {
		handle_pending_signals();
		(void)sigprocmask(SIG_BLOCK, &nset, &oset);
		if (create_exclusive(path) != -1) {
			(void)sigprocmask(SIG_SETMASK, &oset, NULL);
			retval = 0;
			break;
		}
		else
			(void)sigprocmask(SIG_SETMASK, &oset, NULL);

		if (errno != EEXIST)
			break;

		if (pollinterval) {
			if (pollinterval == -1) {
				errno = EEXIST;
				break;
			}
			(void)usleep((unsigned int)pollinterval * 1000);
		}
	}
	handle_pending_signals();
	return retval;
}