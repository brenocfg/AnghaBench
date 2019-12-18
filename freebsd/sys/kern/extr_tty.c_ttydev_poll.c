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
struct tty {int t_flags; int /*<<< orphan*/  t_outpoll; int /*<<< orphan*/  t_inpoll; } ;
struct thread {int dummy; } ;
struct cdev {struct tty* si_drv1; } ;

/* Variables and functions */
 int POLLHUP ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLRDNORM ; 
 int POLLWRNORM ; 
 int TF_ZOMBIE ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int ttydev_enter (struct tty*) ; 
 scalar_t__ ttydisc_read_poll (struct tty*) ; 
 scalar_t__ ttydisc_write_poll (struct tty*) ; 

__attribute__((used)) static int
ttydev_poll(struct cdev *dev, int events, struct thread *td)
{
	struct tty *tp = dev->si_drv1;
	int error, revents = 0;

	error = ttydev_enter(tp);
	if (error)
		return ((events & (POLLIN|POLLRDNORM)) | POLLHUP);

	if (events & (POLLIN|POLLRDNORM)) {
		/* See if we can read something. */
		if (ttydisc_read_poll(tp) > 0)
			revents |= events & (POLLIN|POLLRDNORM);
	}

	if (tp->t_flags & TF_ZOMBIE) {
		/* Hangup flag on zombie state. */
		revents |= POLLHUP;
	} else if (events & (POLLOUT|POLLWRNORM)) {
		/* See if we can write something. */
		if (ttydisc_write_poll(tp) > 0)
			revents |= events & (POLLOUT|POLLWRNORM);
	}

	if (revents == 0) {
		if (events & (POLLIN|POLLRDNORM))
			selrecord(td, &tp->t_inpoll);
		if (events & (POLLOUT|POLLWRNORM))
			selrecord(td, &tp->t_outpoll);
	}

	tty_unlock(tp);

	return (revents);
}