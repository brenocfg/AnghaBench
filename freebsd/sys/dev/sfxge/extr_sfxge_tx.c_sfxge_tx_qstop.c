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
struct sfxge_txq {size_t evq_index; scalar_t__ init_state; scalar_t__ flush_state; scalar_t__ pending; scalar_t__ added; scalar_t__ completed; scalar_t__ reaped; scalar_t__ hw_cksum_flags; int /*<<< orphan*/  buf_base_id; int /*<<< orphan*/ * common; scalar_t__ blocked; } ;
struct sfxge_softc {int /*<<< orphan*/  txq_entries; int /*<<< orphan*/  enp; int /*<<< orphan*/  dev; struct sfxge_evq** evq; struct sfxge_txq** txq; } ;
struct sfxge_evq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  EFX_TXQ_NBUFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SFXGE_ADAPTER_LOCK_ASSERT_OWNED (struct sfxge_softc*) ; 
 int /*<<< orphan*/  SFXGE_EVQ_LOCK (struct sfxge_evq*) ; 
 int /*<<< orphan*/  SFXGE_EVQ_UNLOCK (struct sfxge_evq*) ; 
 scalar_t__ SFXGE_FLUSH_DONE ; 
 scalar_t__ SFXGE_FLUSH_FAILED ; 
 scalar_t__ SFXGE_FLUSH_PENDING ; 
 scalar_t__ SFXGE_TXQ_INITIALIZED ; 
 int /*<<< orphan*/  SFXGE_TXQ_LOCK (struct sfxge_txq*) ; 
 scalar_t__ SFXGE_TXQ_STARTED ; 
 int /*<<< orphan*/  SFXGE_TXQ_UNLOCK (struct sfxge_txq*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_sram_buf_tbl_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_tx_qdestroy (int /*<<< orphan*/ *) ; 
 scalar_t__ efx_tx_qflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sfxge_tx_qcomplete (struct sfxge_txq*,struct sfxge_evq*) ; 
 int /*<<< orphan*/  sfxge_tx_qreap (struct sfxge_txq*) ; 

__attribute__((used)) static void
sfxge_tx_qstop(struct sfxge_softc *sc, unsigned int index)
{
	struct sfxge_txq *txq;
	struct sfxge_evq *evq;
	unsigned int count;

	SFXGE_ADAPTER_LOCK_ASSERT_OWNED(sc);

	txq = sc->txq[index];
	evq = sc->evq[txq->evq_index];

	SFXGE_EVQ_LOCK(evq);
	SFXGE_TXQ_LOCK(txq);

	KASSERT(txq->init_state == SFXGE_TXQ_STARTED,
	    ("txq->init_state != SFXGE_TXQ_STARTED"));

	txq->init_state = SFXGE_TXQ_INITIALIZED;

	if (txq->flush_state != SFXGE_FLUSH_DONE) {
		txq->flush_state = SFXGE_FLUSH_PENDING;

		SFXGE_EVQ_UNLOCK(evq);
		SFXGE_TXQ_UNLOCK(txq);

		/* Flush the transmit queue. */
		if (efx_tx_qflush(txq->common) != 0) {
			log(LOG_ERR, "%s: Flushing Tx queue %u failed\n",
			    device_get_nameunit(sc->dev), index);
			txq->flush_state = SFXGE_FLUSH_DONE;
		} else {
			count = 0;
			do {
				/* Spin for 100ms. */
				DELAY(100000);
				if (txq->flush_state != SFXGE_FLUSH_PENDING)
					break;
			} while (++count < 20);
		}
		SFXGE_EVQ_LOCK(evq);
		SFXGE_TXQ_LOCK(txq);

		KASSERT(txq->flush_state != SFXGE_FLUSH_FAILED,
		    ("txq->flush_state == SFXGE_FLUSH_FAILED"));

		if (txq->flush_state != SFXGE_FLUSH_DONE) {
			/* Flush timeout */
			log(LOG_ERR, "%s: Cannot flush Tx queue %u\n",
			    device_get_nameunit(sc->dev), index);
			txq->flush_state = SFXGE_FLUSH_DONE;
		}
	}

	txq->blocked = 0;
	txq->pending = txq->added;

	sfxge_tx_qcomplete(txq, evq);
	KASSERT(txq->completed == txq->added,
	    ("txq->completed != txq->added"));

	sfxge_tx_qreap(txq);
	KASSERT(txq->reaped == txq->completed,
	    ("txq->reaped != txq->completed"));

	txq->added = 0;
	txq->pending = 0;
	txq->completed = 0;
	txq->reaped = 0;

	/* Destroy the common code transmit queue. */
	efx_tx_qdestroy(txq->common);
	txq->common = NULL;

	efx_sram_buf_tbl_clear(sc->enp, txq->buf_base_id,
	    EFX_TXQ_NBUFS(sc->txq_entries));

	txq->hw_cksum_flags = 0;

	SFXGE_EVQ_UNLOCK(evq);
	SFXGE_TXQ_UNLOCK(txq);
}