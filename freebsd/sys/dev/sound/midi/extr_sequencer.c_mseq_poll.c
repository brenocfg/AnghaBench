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
struct seq_softc {int unit; int playing; int out_water; int /*<<< orphan*/  seq_lock; int /*<<< orphan*/  in_sel; int /*<<< orphan*/  in_q; int /*<<< orphan*/  out_sel; int /*<<< orphan*/  out_q; int /*<<< orphan*/  out_cv; int /*<<< orphan*/  state_cv; } ;
struct cdev {struct seq_softc* si_drv1; } ;

/* Variables and functions */
 int MIDIQ_AVAIL (int /*<<< orphan*/ ) ; 
 int MIDIQ_LEN (int /*<<< orphan*/ ) ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLRDNORM ; 
 int POLLWRNORM ; 
 int /*<<< orphan*/  SEQ_DEBUG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

int
mseq_poll(struct cdev *i_dev, int events, struct thread *td)
{
	int ret, lim;
	struct seq_softc *scp = i_dev->si_drv1;

	SEQ_DEBUG(3, printf("seq_poll: unit %d.\n", scp->unit));
	SEQ_DEBUG(1, printf("seq_poll: unit %d.\n", scp->unit));

	mtx_lock(&scp->seq_lock);

	ret = 0;

	/* Look up the apropriate queue and select it. */
	if ((events & (POLLOUT | POLLWRNORM)) != 0) {
		/* Start playing. */
		scp->playing = 1;
		cv_broadcast(&scp->state_cv);
		cv_broadcast(&scp->out_cv);

		lim = scp->out_water;

		if (MIDIQ_AVAIL(scp->out_q) < lim)
			/* No enough space, record select. */
			selrecord(td, &scp->out_sel);
		else
			/* We can write now. */
			ret |= events & (POLLOUT | POLLWRNORM);
	}
	if ((events & (POLLIN | POLLRDNORM)) != 0) {
		/* TODO: Start recording. */

		/* Find out the boundary. */
		lim = 1;
		if (MIDIQ_LEN(scp->in_q) < lim)
			/* No data ready, record select. */
			selrecord(td, &scp->in_sel);
		else
			/* We can read now. */
			ret |= events & (POLLIN | POLLRDNORM);
	}
	mtx_unlock(&scp->seq_lock);

	return (ret);
}