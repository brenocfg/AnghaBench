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
struct seq_softc {int unit; int playing; scalar_t__ waiting; int midi_number; int /*<<< orphan*/  seq_lock; int /*<<< orphan*/ * midis; int /*<<< orphan*/  reset_cv; int /*<<< orphan*/  out_cv; int /*<<< orphan*/  state_cv; int /*<<< orphan*/  out_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EINTR ; 
 int ERESTART ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MIDIQ_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIDIQ_EMPTY (int /*<<< orphan*/ ) ; 
 int MIDIQ_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQ_DEBUG (int,int /*<<< orphan*/ ) ; 
 int SEQ_SYNC_TIMEOUT ; 
 scalar_t__ SYNTH_INSYNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int cv_timedwait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int hz ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
seq_sync(struct seq_softc *scp)
{
	int i, rl, sync[16], done;

	mtx_assert(&scp->seq_lock, MA_OWNED);

	SEQ_DEBUG(4, printf("seq_sync: unit %d.\n", scp->unit));

	/*
	 * Wait until output queue is empty.  Check every so often to see if
	 * the queue is moving along.  If it isn't just abort.
	 */
	while (!MIDIQ_EMPTY(scp->out_q)) {

		if (!scp->playing) {
			scp->playing = 1;
			cv_broadcast(&scp->state_cv);
			cv_broadcast(&scp->out_cv);
		}
		rl = MIDIQ_LEN(scp->out_q);

		i = cv_timedwait_sig(&scp->out_cv,
		    &scp->seq_lock, SEQ_SYNC_TIMEOUT * hz);

		if (i == EINTR || i == ERESTART) {
			if (i == EINTR) {
				/*
			         * XXX: I don't know why we stop playing
			         */
				scp->playing = 0;
				cv_broadcast(&scp->out_cv);
			}
			return i;
		}
		if (i == EWOULDBLOCK && rl == MIDIQ_LEN(scp->out_q) &&
		    scp->waiting == 0) {
			/*
			 * A queue seems to be stuck up. Give up and clear
			 * queues.
			 */
			MIDIQ_CLEAR(scp->out_q);
			scp->playing = 0;
			cv_broadcast(&scp->state_cv);
			cv_broadcast(&scp->out_cv);
			cv_broadcast(&scp->reset_cv);

			/*
			 * TODO: Consider if the raw devices need to be flushed
			 */

			SEQ_DEBUG(1, printf("seq_sync queue stuck, aborting\n"));

			return i;
		}
	}

	scp->playing = 0;
	/*
	 * Since syncing a midi device might block, unlock scp->seq_lock.
	 */

	mtx_unlock(&scp->seq_lock);
	for (i = 0; i < scp->midi_number; i++)
		sync[i] = 1;

	do {
		done = 1;
		for (i = 0; i < scp->midi_number; i++)
			if (sync[i]) {
				if (SYNTH_INSYNC(scp->midis[i]) == 0)
					sync[i] = 0;
				else
					done = 0;
			}
		if (!done)
			DELAY(5000);

	} while (!done);

	mtx_lock(&scp->seq_lock);
	return 0;
}