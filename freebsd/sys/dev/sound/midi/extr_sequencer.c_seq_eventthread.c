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
typedef  int /*<<< orphan*/  u_char ;
struct seq_softc {scalar_t__ done; scalar_t__ playing; scalar_t__ out_water; int /*<<< orphan*/  seq_lock; int /*<<< orphan*/  th_cv; int /*<<< orphan*/  out_sel; int /*<<< orphan*/  out_cv; int /*<<< orphan*/  out_q; int /*<<< orphan*/  empty_cv; int /*<<< orphan*/  state_cv; } ;

/* Variables and functions */
 int EV_SZ ; 
 scalar_t__ MIDIQ_AVAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIDIQ_DEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ MIDIQ_EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQ_DEBUG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  selwakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_processevent (struct seq_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
seq_eventthread(void *arg)
{
	struct seq_softc *scp = arg;
	u_char event[EV_SZ];

	mtx_lock(&scp->seq_lock);
	SEQ_DEBUG(2, printf("seq_eventthread started\n"));
	while (scp->done == 0) {
restart:
		while (scp->playing == 0) {
			cv_wait(&scp->state_cv, &scp->seq_lock);
			if (scp->done)
				goto done;
		}

		while (MIDIQ_EMPTY(scp->out_q)) {
			cv_broadcast(&scp->empty_cv);
			cv_wait(&scp->out_cv, &scp->seq_lock);
			if (scp->playing == 0)
				goto restart;
			if (scp->done)
				goto done;
		}

		MIDIQ_DEQ(scp->out_q, event, EV_SZ);

		if (MIDIQ_AVAIL(scp->out_q) < scp->out_water) {
			cv_broadcast(&scp->out_cv);
			selwakeup(&scp->out_sel);
		}
		seq_processevent(scp, event);
	}

done:
	cv_broadcast(&scp->th_cv);
	mtx_unlock(&scp->seq_lock);
	SEQ_DEBUG(2, printf("seq_eventthread finished\n"));
	kproc_exit(0);
}