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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct sfxge_txq {scalar_t__ init_state; size_t evq_index; } ;
struct sfxge_softc {struct sfxge_evq** evq; struct sfxge_txq** txq; } ;
struct sfxge_evq {size_t index; scalar_t__ init_state; int /*<<< orphan*/  common; struct sfxge_softc* sc; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SFXGE_EVQ_LOCK_ASSERT_OWNED (struct sfxge_evq*) ; 
 scalar_t__ SFXGE_EVQ_STARTED ; 
 int /*<<< orphan*/  SFXGE_SW_EV_TX_QFLUSH_DONE ; 
 scalar_t__ SFXGE_TXQ_INITIALIZED ; 
 int /*<<< orphan*/  efx_ev_qpost (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_sw_ev_txq_magic (int /*<<< orphan*/ ,struct sfxge_txq*) ; 
 int /*<<< orphan*/  sfxge_tx_qflush_done (struct sfxge_txq*) ; 

__attribute__((used)) static boolean_t
sfxge_ev_txq_flush_done(void *arg, uint32_t txq_index)
{
	struct sfxge_evq *evq;
	struct sfxge_softc *sc;
	struct sfxge_txq *txq;
	uint16_t magic;

	evq = (struct sfxge_evq *)arg;
	SFXGE_EVQ_LOCK_ASSERT_OWNED(evq);

	sc = evq->sc;
	txq = sc->txq[txq_index];

	KASSERT(txq != NULL, ("txq == NULL"));
	KASSERT(txq->init_state == SFXGE_TXQ_INITIALIZED,
	    ("txq not initialized"));

	if (txq->evq_index == evq->index) {
		sfxge_tx_qflush_done(txq);
		return (B_FALSE);
	}

	/* Resend a software event on the correct queue */
	evq = sc->evq[txq->evq_index];
	magic = sfxge_sw_ev_txq_magic(SFXGE_SW_EV_TX_QFLUSH_DONE, txq);

	KASSERT(evq->init_state == SFXGE_EVQ_STARTED,
	    ("evq not started"));
	efx_ev_qpost(evq->common, magic);

	return (B_FALSE);
}