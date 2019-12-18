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
 int O_NOCTTY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  _PATH_TTY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  debug3 (char*) ; 
 scalar_t__ getpid () ; 
 int getppid () ; 
 scalar_t__ getsid (int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int) ; 

int
daemonized(void)
{
	int fd;

	if ((fd = open(_PATH_TTY, O_RDONLY | O_NOCTTY)) >= 0) {
		close(fd);
		return 0;	/* have controlling terminal */
	}
	if (getppid() != 1)
		return 0;	/* parent is not init */
	if (getsid(0) != getpid())
		return 0;	/* not session leader */
	debug3("already daemonized");
	return 1;
}