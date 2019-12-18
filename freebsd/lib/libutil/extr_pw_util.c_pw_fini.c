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
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  close (int) ; 
 int editpid ; 
 int errno ; 
 scalar_t__ initialized ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int lockfd ; 
 char* tempname ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  waitpid (int,int*,int /*<<< orphan*/ ) ; 

void
pw_fini(void)
{
	int serrno, status;

	if (!initialized)
		return;
	initialized = 0;
	serrno = errno;
	if (editpid != -1) {
		kill(editpid, SIGTERM);
		kill(editpid, SIGCONT);
		waitpid(editpid, &status, 0);
		editpid = -1;
	}
	if (*tempname != '\0') {
		unlink(tempname);
		*tempname = '\0';
	}
	if (lockfd != -1)
		close(lockfd);
	errno = serrno;
}