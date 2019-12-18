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
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  sanitize_stdfds () ; 
 int setsid () ; 

int daemonize(void)
{
#ifdef NO_POSIX_GOODIES
	errno = ENOSYS;
	return -1;
#else
	switch (fork()) {
		case 0:
			break;
		case -1:
			die_errno(_("fork failed"));
		default:
			exit(0);
	}
	if (setsid() == -1)
		die_errno(_("setsid failed"));
	close(0);
	close(1);
	close(2);
	sanitize_stdfds();
	return 0;
#endif
}