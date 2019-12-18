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

/* Variables and functions */
 int SIGCHLD ; 
 int SIGHUP ; 
 int /*<<< orphan*/  WNOHANG ; 
 int /*<<< orphan*/  children ; 
 int errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_securenets () ; 
 int /*<<< orphan*/  unregister () ; 
 scalar_t__ wait3 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yp_flush_all () ; 

__attribute__((used)) static void
reaper(int sig)
{
	int			status;
	int			saved_errno;

	saved_errno = errno;

	if (sig == SIGHUP) {
		load_securenets();
#ifdef DB_CACHE
		yp_flush_all();
#endif
		errno = saved_errno;
		return;
	}

	if (sig == SIGCHLD) {
		while (wait3(&status, WNOHANG, NULL) > 0)
			children--;
	} else {
		unregister();
		exit(0);
	}
	errno = saved_errno;
	return;
}