#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uio {int dummy; } ;
struct TYPE_2__ {int c_lflag; } ;
struct tty {int t_flags; int /*<<< orphan*/  t_outserwait; TYPE_1__ t_termios; } ;
struct cdev {struct tty* si_drv1; } ;

/* Variables and functions */
 int IO_NDELAY ; 
 int /*<<< orphan*/  SIGTTOU ; 
 int TF_BUSY_OUT ; 
 int TOSTOP ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int tty_wait (struct tty*,int /*<<< orphan*/ *) ; 
 int tty_wait_background (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ttydev_enter (struct tty*) ; 
 int ttydisc_write (struct tty*,struct uio*,int) ; 

__attribute__((used)) static int
ttydev_write(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct tty *tp = dev->si_drv1;
	int error;

	error = ttydev_enter(tp);
	if (error)
		return (error);

	if (tp->t_termios.c_lflag & TOSTOP) {
		error = tty_wait_background(tp, curthread, SIGTTOU);
		if (error)
			goto done;
	}

	if (ioflag & IO_NDELAY && tp->t_flags & TF_BUSY_OUT) {
		/* Allow non-blocking writes to bypass serialization. */
		error = ttydisc_write(tp, uio, ioflag);
	} else {
		/* Serialize write() calls. */
		while (tp->t_flags & TF_BUSY_OUT) {
			error = tty_wait(tp, &tp->t_outserwait);
			if (error)
				goto done;
		}

		tp->t_flags |= TF_BUSY_OUT;
		error = ttydisc_write(tp, uio, ioflag);
		tp->t_flags &= ~TF_BUSY_OUT;
		cv_signal(&tp->t_outserwait);
	}

done:	tty_unlock(tp);
	return (error);
}