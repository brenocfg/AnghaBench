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
struct sfxge_txq {size_t evq_index; scalar_t__ init_state; unsigned int added; unsigned int completed; scalar_t__ blocked; int /*<<< orphan*/  entries; struct sfxge_softc* sc; } ;
struct sfxge_softc {struct sfxge_evq** evq; } ;
struct sfxge_evq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFXGE_EVQ_LOCK_ASSERT_OWNED (struct sfxge_evq*) ; 
 int /*<<< orphan*/  SFXGE_TXQ_LOCK (struct sfxge_txq*) ; 
 scalar_t__ SFXGE_TXQ_STARTED ; 
 unsigned int SFXGE_TXQ_UNBLOCK_LEVEL (int /*<<< orphan*/ ) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  sfxge_tx_qdpl_service (struct sfxge_txq*) ; 
 int /*<<< orphan*/  sfxge_tx_qreap (struct sfxge_txq*) ; 

__attribute__((used)) static void
sfxge_tx_qunblock(struct sfxge_txq *txq)
{
	struct sfxge_softc *sc;
	struct sfxge_evq *evq;

	sc = txq->sc;
	evq = sc->evq[txq->evq_index];

	SFXGE_EVQ_LOCK_ASSERT_OWNED(evq);

	if (__predict_false(txq->init_state != SFXGE_TXQ_STARTED))
		return;

	SFXGE_TXQ_LOCK(txq);

	if (txq->blocked) {
		unsigned int level;

		level = txq->added - txq->completed;
		if (level <= SFXGE_TXQ_UNBLOCK_LEVEL(txq->entries)) {
			/* reaped must be in sync with blocked */
			sfxge_tx_qreap(txq);
			txq->blocked = 0;
		}
	}

	sfxge_tx_qdpl_service(txq);
	/* note: lock has been dropped */
}