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
struct ath_txq {int /*<<< orphan*/  axq_tidq; } ;
struct ath_tid {size_t ac; int sched; TYPE_1__* an; } ;
struct ath_softc {struct ath_txq** sc_ac2q; } ;
struct TYPE_2__ {scalar_t__ an_leak_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_TX_LOCK_ASSERT (struct ath_softc*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct ath_tid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ath_tid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_tx_tid_can_tx_or_sched (struct ath_softc*,struct ath_tid*) ; 
 int /*<<< orphan*/  axq_qelem ; 

void
ath_tx_tid_sched(struct ath_softc *sc, struct ath_tid *tid)
{
	struct ath_txq *txq = sc->sc_ac2q[tid->ac];

	ATH_TX_LOCK_ASSERT(sc);

	/*
	 * If we are leaking out a frame to this destination
	 * for PS-POLL, ensure that we allow scheduling to
	 * occur.
	 */
	if (! ath_tx_tid_can_tx_or_sched(sc, tid))
		return;		/* paused, can't schedule yet */

	if (tid->sched)
		return;		/* already scheduled */

	tid->sched = 1;

#if 0
	/*
	 * If this is a sleeping node we're leaking to, given
	 * it a higher priority.  This is so bad for QoS it hurts.
	 */
	if (tid->an->an_leak_count) {
		TAILQ_INSERT_HEAD(&txq->axq_tidq, tid, axq_qelem);
	} else {
		TAILQ_INSERT_TAIL(&txq->axq_tidq, tid, axq_qelem);
	}
#endif

	/*
	 * We can't do the above - it'll confuse the TXQ software
	 * scheduler which will keep checking the _head_ TID
	 * in the list to see if it has traffic.  If we queue
	 * a TID to the head of the list and it doesn't transmit,
	 * we'll check it again.
	 *
	 * So, get the rest of this leaking frames support working
	 * and reliable first and _then_ optimise it so they're
	 * pushed out in front of any other pending software
	 * queued nodes.
	 */
	TAILQ_INSERT_TAIL(&txq->axq_tidq, tid, axq_qelem);
}