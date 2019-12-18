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
struct termios {int /*<<< orphan*/  c_oflag; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CATCH_EINTR (int) ; 
 int /*<<< orphan*/  OPOST ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int errno ; 
 int generic_write (int,char const*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ isatty (int) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int tcgetattr (int,struct termios*) ; 
 int tcsetattr (int,int /*<<< orphan*/ ,struct termios*) ; 

int generic_console_write(int fd, const char *buf, int n)
{
	sigset_t old, no_sigio;
	struct termios save, new;
	int err;

	if (isatty(fd)) {
		sigemptyset(&no_sigio);
		sigaddset(&no_sigio, SIGIO);
		if (sigprocmask(SIG_BLOCK, &no_sigio, &old))
			goto error;

		CATCH_EINTR(err = tcgetattr(fd, &save));
		if (err)
			goto error;
		new = save;
		/*
		 * The terminal becomes a bit less raw, to handle \n also as
		 * "Carriage Return", not only as "New Line". Otherwise, the new
		 * line won't start at the first column.
		 */
		new.c_oflag |= OPOST;
		CATCH_EINTR(err = tcsetattr(fd, TCSAFLUSH, &new));
		if (err)
			goto error;
	}
	err = generic_write(fd, buf, n, NULL);
	/*
	 * Restore raw mode, in any case; we *must* ignore any error apart
	 * EINTR, except for debug.
	 */
	if (isatty(fd)) {
		CATCH_EINTR(tcsetattr(fd, TCSAFLUSH, &save));
		sigprocmask(SIG_SETMASK, &old, NULL);
	}

	return err;
error:
	return -errno;
}