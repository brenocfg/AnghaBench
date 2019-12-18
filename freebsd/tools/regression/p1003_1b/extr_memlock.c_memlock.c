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
 int MCL_CURRENT ; 
 int MCL_FUTURE ; 
 int /*<<< orphan*/  _SC_MEMLOCK ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int mlockall (int) ; 
 int munlockall () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  quit (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int sysconf (int /*<<< orphan*/ ) ; 

int memlock(int argc, char *argv[])
{
	int e = 0;

	/* Is memory locking configured?
	 */
	errno = 0;
	if (sysconf(_SC_MEMLOCK) == -1) {
		if (errno != 0) {
			/* This isn't valid - may be a standard violation
			 */
			quit("(should not happen) sysconf(_SC_MEMLOCK)");
		}
		else {
			fprintf(stderr,
			"Memory locking is not supported in this environment.\n");
			e = -1;
		}
	}

	/* Lock yourself in memory:
	 */
	if (mlockall(MCL_CURRENT | MCL_FUTURE) == -1) {
		perror("mlockall(MCL_CURRENT | MCL_FUTURE)");
		e = errno;
	}
	else if (munlockall() == -1) {
		perror("munlockall");
		e = errno;
	}

	return e;
}