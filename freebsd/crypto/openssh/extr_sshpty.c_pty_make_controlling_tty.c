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
 int O_RDWR ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  TIOCNOTTY ; 
 int /*<<< orphan*/  TIOCSCTTY ; 
 char const* _PATH_TTY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int open (char const*,int) ; 
 scalar_t__ setpgrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ setsid () ; 
 char* strerror (int /*<<< orphan*/ ) ; 

void
pty_make_controlling_tty(int *ttyfd, const char *tty)
{
	int fd;

	/* First disconnect from the old controlling tty. */
#ifdef TIOCNOTTY
	fd = open(_PATH_TTY, O_RDWR | O_NOCTTY);
	if (fd >= 0) {
		(void) ioctl(fd, TIOCNOTTY, NULL);
		close(fd);
	}
#endif /* TIOCNOTTY */
	if (setsid() < 0)
		error("setsid: %.100s", strerror(errno));

	/*
	 * Verify that we are successfully disconnected from the controlling
	 * tty.
	 */
	fd = open(_PATH_TTY, O_RDWR | O_NOCTTY);
	if (fd >= 0) {
		error("Failed to disconnect from controlling tty.");
		close(fd);
	}
	/* Make it our controlling tty. */
#ifdef TIOCSCTTY
	debug("Setting controlling tty using TIOCSCTTY.");
	if (ioctl(*ttyfd, TIOCSCTTY, NULL) < 0)
		error("ioctl(TIOCSCTTY): %.100s", strerror(errno));
#endif /* TIOCSCTTY */
#ifdef NEED_SETPGRP
	if (setpgrp(0,0) < 0)
		error("SETPGRP %s",strerror(errno));
#endif /* NEED_SETPGRP */
	fd = open(tty, O_RDWR);
	if (fd < 0)
		error("%.100s: %.100s", tty, strerror(errno));
	else
		close(fd);

	/* Verify that we now have a controlling tty. */
	fd = open(_PATH_TTY, O_WRONLY);
	if (fd < 0)
		error("open /dev/tty failed - could not set controlling tty: %.100s",
		    strerror(errno));
	else
		close(fd);
}