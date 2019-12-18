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
typedef  int const u_long ;
struct termios {int c_iflag; int c_oflag; int c_cflag; int c_lflag; scalar_t__ c_ospeed; scalar_t__ c_ispeed; scalar_t__* c_cc; } ;
struct tty {struct termios t_termios_lock_in; struct termios t_termios_lock_out; struct termios t_termios; } ;
struct thread {int dummy; } ;
struct cdev {struct tty* si_drv1; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int NCCS ; 
#define  OTIOCSETD 154 
 int /*<<< orphan*/  SIGTTOU ; 
#define  TIOCCBRK 153 
#define  TIOCCONS 152 
#define  TIOCDRAIN 151 
#define  TIOCEXCL 150 
#define  TIOCFLUSH 149 
#define  TIOCLBIC 148 
#define  TIOCLBIS 147 
#define  TIOCLSET 146 
#define  TIOCNXCL 145 
#define  TIOCSBRK 144 
#define  TIOCSCTTY 143 
#define  TIOCSDRAINWAIT 142 
#define  TIOCSETA 141 
#define  TIOCSETAF 140 
#define  TIOCSETAW 139 
#define  TIOCSETC 138 
#define  TIOCSETD 137 
#define  TIOCSETN 136 
#define  TIOCSETP 135 
#define  TIOCSLTC 134 
#define  TIOCSPGRP 133 
#define  TIOCSTART 132 
#define  TIOCSTAT 131 
#define  TIOCSTI 130 
#define  TIOCSTOP 129 
#define  TIOCSWINSZ 128 
 scalar_t__ TTY_CALLOUT (struct tty*,struct cdev*) ; 
 int /*<<< orphan*/  curthread ; 
 int tty_ioctl (struct tty*,int const,scalar_t__,int,struct thread*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int tty_wait_background (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ttydev_enter (struct tty*) ; 

__attribute__((used)) static int
ttydev_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int fflag,
    struct thread *td)
{
	struct tty *tp = dev->si_drv1;
	int error;

	error = ttydev_enter(tp);
	if (error)
		return (error);

	switch (cmd) {
	case TIOCCBRK:
	case TIOCCONS:
	case TIOCDRAIN:
	case TIOCEXCL:
	case TIOCFLUSH:
	case TIOCNXCL:
	case TIOCSBRK:
	case TIOCSCTTY:
	case TIOCSETA:
	case TIOCSETAF:
	case TIOCSETAW:
	case TIOCSPGRP:
	case TIOCSTART:
	case TIOCSTAT:
	case TIOCSTI:
	case TIOCSTOP:
	case TIOCSWINSZ:
#if 0
	case TIOCSDRAINWAIT:
	case TIOCSETD:
#endif
#ifdef COMPAT_43TTY
	case  TIOCLBIC:
	case  TIOCLBIS:
	case  TIOCLSET:
	case  TIOCSETC:
	case OTIOCSETD:
	case  TIOCSETN:
	case  TIOCSETP:
	case  TIOCSLTC:
#endif /* COMPAT_43TTY */
		/*
		 * If the ioctl() causes the TTY to be modified, let it
		 * wait in the background.
		 */
		error = tty_wait_background(tp, curthread, SIGTTOU);
		if (error)
			goto done;
	}

	if (cmd == TIOCSETA || cmd == TIOCSETAW || cmd == TIOCSETAF) {
		struct termios *old = &tp->t_termios;
		struct termios *new = (struct termios *)data;
		struct termios *lock = TTY_CALLOUT(tp, dev) ?
		    &tp->t_termios_lock_out : &tp->t_termios_lock_in;
		int cc;

		/*
		 * Lock state devices.  Just overwrite the values of the
		 * commands that are currently in use.
		 */
		new->c_iflag = (old->c_iflag & lock->c_iflag) |
		    (new->c_iflag & ~lock->c_iflag);
		new->c_oflag = (old->c_oflag & lock->c_oflag) |
		    (new->c_oflag & ~lock->c_oflag);
		new->c_cflag = (old->c_cflag & lock->c_cflag) |
		    (new->c_cflag & ~lock->c_cflag);
		new->c_lflag = (old->c_lflag & lock->c_lflag) |
		    (new->c_lflag & ~lock->c_lflag);
		for (cc = 0; cc < NCCS; ++cc)
			if (lock->c_cc[cc])
				new->c_cc[cc] = old->c_cc[cc];
		if (lock->c_ispeed)
			new->c_ispeed = old->c_ispeed;
		if (lock->c_ospeed)
			new->c_ospeed = old->c_ospeed;
	}

	error = tty_ioctl(tp, cmd, data, fflag, td);
done:	tty_unlock(tp);

	return (error);
}