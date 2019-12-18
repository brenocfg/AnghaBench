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
struct thread {int dummy; } ;
struct snd_midi {scalar_t__ hiwat; int /*<<< orphan*/  qlock; int /*<<< orphan*/  lock; int /*<<< orphan*/  wsel; int /*<<< orphan*/  rsel; int /*<<< orphan*/  outq; int /*<<< orphan*/  inq; } ;
struct cdev {struct snd_midi* si_drv1; } ;

/* Variables and functions */
 scalar_t__ MIDIQ_AVAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIDIQ_EMPTY (int /*<<< orphan*/ ) ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLRDNORM ; 
 int POLLWRNORM ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

int
midi_poll(struct cdev *i_dev, int events, struct thread *td)
{
	struct snd_midi *m = i_dev->si_drv1;
	int revents;

	if (m == NULL)
		return 0;

	revents = 0;

	mtx_lock(&m->lock);
	mtx_lock(&m->qlock);

	if (events & (POLLIN | POLLRDNORM))
		if (!MIDIQ_EMPTY(m->inq))
			events |= events & (POLLIN | POLLRDNORM);

	if (events & (POLLOUT | POLLWRNORM))
		if (MIDIQ_AVAIL(m->outq) < m->hiwat)
			events |= events & (POLLOUT | POLLWRNORM);

	if (revents == 0) {
		if (events & (POLLIN | POLLRDNORM))
			selrecord(td, &m->rsel);

		if (events & (POLLOUT | POLLWRNORM))
			selrecord(td, &m->wsel);
	}
	mtx_unlock(&m->lock);
	mtx_unlock(&m->qlock);

	return (revents);
}