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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PPPDISC ; 
 int /*<<< orphan*/  TIOCSETD ; 
 int /*<<< orphan*/  condition (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tty_open(const char *ttydev)
{
	int		fd;

	if ((fd = open(ttydev, O_RDWR, 0)) == -1)
		err(EXIT_FAILURE, "Couldn't open tty(4) device");

#ifdef USE_PPP_DISCIPLINE
	{
		int	opt = PPPDISC;
		if (ioctl(fd, TIOCSETD, &opt) == -1)
			err(EXIT_FAILURE,
			    "Couldn't set tty(4) discipline to PPP");
	}
#endif

	condition(fd);

	return fd;
}