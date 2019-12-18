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
 int /*<<< orphan*/  TIOCNOTTY ; 
 int /*<<< orphan*/  _PATH_TTY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int open (int /*<<< orphan*/ ,int) ; 

void
disconnect_controlling_tty(void)
{
#ifdef TIOCNOTTY
	int fd;

	if ((fd = open(_PATH_TTY, O_RDWR | O_NOCTTY)) >= 0) {
		(void) ioctl(fd, TIOCNOTTY, NULL);
		close(fd);
	}
#endif /* TIOCNOTTY */
}