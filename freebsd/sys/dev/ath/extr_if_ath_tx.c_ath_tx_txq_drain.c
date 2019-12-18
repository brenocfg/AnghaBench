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
struct ath_txq {int /*<<< orphan*/  axq_tidq; } ;
struct ath_tid {int /*<<< orphan*/  an; } ;
struct ath_softc {int dummy; } ;
struct ath_buf {int dummy; } ;
typedef  int /*<<< orphan*/  ath_bufhead ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_TX_LOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_TX_UNLOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 void* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ath_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_tx_default_comp (struct ath_softc*,struct ath_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_tx_tid_drain (struct ath_softc*,int /*<<< orphan*/ ,struct ath_tid*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_tx_tid_unsched (struct ath_softc*,struct ath_tid*) ; 
 int /*<<< orphan*/  bf_list ; 

void
ath_tx_txq_drain(struct ath_softc *sc, struct ath_txq *txq)
{
	struct ath_tid *tid;
	ath_bufhead bf_cq;
	struct ath_buf *bf;

	TAILQ_INIT(&bf_cq);
	ATH_TX_LOCK(sc);

	/*
	 * Iterate over all active tids for the given txq,
	 * flushing and unsched'ing them
	 */
	while (! TAILQ_EMPTY(&txq->axq_tidq)) {
		tid = TAILQ_FIRST(&txq->axq_tidq);
		ath_tx_tid_drain(sc, tid->an, tid, &bf_cq);
		ath_tx_tid_unsched(sc, tid);
	}

	ATH_TX_UNLOCK(sc);

	while ((bf = TAILQ_FIRST(&bf_cq)) != NULL) {
		TAILQ_REMOVE(&bf_cq, bf, bf_list);
		ath_tx_default_comp(sc, bf, 0);
	}
}