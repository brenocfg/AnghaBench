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
struct termios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B921600 ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  TIOCGQSIZE ; 
 int /*<<< orphan*/  TIOCSQSIZE ; 
 int /*<<< orphan*/  cfmakeraw (struct termios*) ; 
 int /*<<< orphan*/  cfsetspeed (struct termios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int qsize ; 
 int tcgetattr (int,struct termios*) ; 
 int tcsetattr (int,int /*<<< orphan*/ ,struct termios*) ; 

__attribute__((used)) static void
condition(int fd)
{
	struct termios	tios;

	if (qsize) {
		int opt = qsize;
		if (ioctl(fd, TIOCSQSIZE, &opt) == -1)
			err(EXIT_FAILURE, "Couldn't set tty(4) buffer size");
		if (ioctl(fd, TIOCGQSIZE, &opt) == -1)
			err(EXIT_FAILURE, "Couldn't get tty(4) buffer size");
		if (opt != qsize)
			errx(EXIT_FAILURE, "Wrong qsize %d != %d\n",
			    qsize, opt);
	}
	if (tcgetattr(fd, &tios) == -1)
		err(EXIT_FAILURE, "tcgetattr()");
	cfmakeraw(&tios);
	cfsetspeed(&tios, B921600);
	if (tcsetattr(fd, TCSANOW, &tios) == -1)
		err(EXIT_FAILURE, "tcsetattr()");
}