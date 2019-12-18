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
typedef  int u_long ;
struct winsize {int dummy; } ;
struct tty {int dummy; } ;
struct thread {int dummy; } ;
struct termios {int dummy; } ;
struct cdev {scalar_t__ si_drv2; struct tty* si_drv1; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENODEV ; 
 int ENOIOCTL ; 
 int ENOTTY ; 
 int /*<<< orphan*/  PRIV_TTY_SETA ; 
#define  TIOCGETA 131 
#define  TIOCGETD 130 
#define  TIOCGWINSZ 129 
#define  TIOCSETA 128 
 int TTYDISC ; 
 int /*<<< orphan*/  bzero (scalar_t__,int) ; 
 int /*<<< orphan*/  dev2unit (struct cdev*) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 scalar_t__ tty_gone (struct tty*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int ttydevsw_cioctl (struct tty*,int /*<<< orphan*/ ,int,scalar_t__,struct thread*) ; 

__attribute__((used)) static int
ttyil_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int fflag,
    struct thread *td)
{
	struct tty *tp = dev->si_drv1;
	int error;

	tty_lock(tp);
	if (tty_gone(tp)) {
		error = ENODEV;
		goto done;
	}

	error = ttydevsw_cioctl(tp, dev2unit(dev), cmd, data, td);
	if (error != ENOIOCTL)
		goto done;
	error = 0;

	switch (cmd) {
	case TIOCGETA:
		/* Obtain terminal flags through tcgetattr(). */
		*(struct termios*)data = *(struct termios*)dev->si_drv2;
		break;
	case TIOCSETA:
		/* Set terminal flags through tcsetattr(). */
		error = priv_check(td, PRIV_TTY_SETA);
		if (error)
			break;
		*(struct termios*)dev->si_drv2 = *(struct termios*)data;
		break;
	case TIOCGETD:
		*(int *)data = TTYDISC;
		break;
	case TIOCGWINSZ:
		bzero(data, sizeof(struct winsize));
		break;
	default:
		error = ENOTTY;
	}

done:	tty_unlock(tp);
	return (error);
}