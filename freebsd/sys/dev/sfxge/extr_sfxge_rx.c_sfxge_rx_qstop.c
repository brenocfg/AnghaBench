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
struct sfxge_softc {int /*<<< orphan*/  rxq_entries; int /*<<< orphan*/  enp; int /*<<< orphan*/  dev; struct sfxge_evq** evq; struct sfxge_rxq** rxq; } ;
struct sfxge_rxq {scalar_t__ init_state; scalar_t__ flush_state; scalar_t__ pending; scalar_t__ added; scalar_t__ completed; int /*<<< orphan*/  buf_base_id; int /*<<< orphan*/  common; scalar_t__ loopback; scalar_t__ pushed; int /*<<< orphan*/  refill_callout; } ;
struct sfxge_evq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  EFX_RXQ_NBUFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SFXGE_ADAPTER_LOCK_ASSERT_OWNED (struct sfxge_softc*) ; 
 int /*<<< orphan*/  SFXGE_EVQ_LOCK (struct sfxge_evq*) ; 
 int /*<<< orphan*/  SFXGE_EVQ_UNLOCK (struct sfxge_evq*) ; 
 scalar_t__ SFXGE_FLUSH_DONE ; 
 scalar_t__ SFXGE_FLUSH_FAILED ; 
 scalar_t__ SFXGE_FLUSH_PENDING ; 
 scalar_t__ SFXGE_RXQ_INITIALIZED ; 
 scalar_t__ SFXGE_RXQ_STARTED ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_rx_qdestroy (int /*<<< orphan*/ ) ; 
 scalar_t__ efx_rx_qflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_sram_buf_tbl_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sfxge_rx_qcomplete (struct sfxge_rxq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sfxge_rx_qstop(struct sfxge_softc *sc, unsigned int index)
{
	struct sfxge_rxq *rxq;
	struct sfxge_evq *evq;
	unsigned int count;
	unsigned int retry = 3;

	SFXGE_ADAPTER_LOCK_ASSERT_OWNED(sc);

	rxq = sc->rxq[index];
	evq = sc->evq[index];

	SFXGE_EVQ_LOCK(evq);

	KASSERT(rxq->init_state == SFXGE_RXQ_STARTED,
	    ("rxq not started"));

	rxq->init_state = SFXGE_RXQ_INITIALIZED;

	callout_stop(&rxq->refill_callout);

	while (rxq->flush_state != SFXGE_FLUSH_DONE && retry != 0) {
		rxq->flush_state = SFXGE_FLUSH_PENDING;

		SFXGE_EVQ_UNLOCK(evq);

		/* Flush the receive queue */
		if (efx_rx_qflush(rxq->common) != 0) {
			SFXGE_EVQ_LOCK(evq);
			rxq->flush_state = SFXGE_FLUSH_FAILED;
			break;
		}

		count = 0;
		do {
			/* Spin for 100 ms */
			DELAY(100000);

			if (rxq->flush_state != SFXGE_FLUSH_PENDING)
				break;

		} while (++count < 20);

		SFXGE_EVQ_LOCK(evq);

		if (rxq->flush_state == SFXGE_FLUSH_PENDING) {
			/* Flush timeout - neither done nor failed */
			log(LOG_ERR, "%s: Cannot flush Rx queue %u\n",
			    device_get_nameunit(sc->dev), index);
			rxq->flush_state = SFXGE_FLUSH_DONE;
		}
		retry--;
	}
	if (rxq->flush_state == SFXGE_FLUSH_FAILED) {
		log(LOG_ERR, "%s: Flushing Rx queue %u failed\n",
		    device_get_nameunit(sc->dev), index);
		rxq->flush_state = SFXGE_FLUSH_DONE;
	}

	rxq->pending = rxq->added;
	sfxge_rx_qcomplete(rxq, B_TRUE);

	KASSERT(rxq->completed == rxq->pending,
	    ("rxq->completed != rxq->pending"));

	rxq->added = 0;
	rxq->pushed = 0;
	rxq->pending = 0;
	rxq->completed = 0;
	rxq->loopback = 0;

	/* Destroy the common code receive queue. */
	efx_rx_qdestroy(rxq->common);

	efx_sram_buf_tbl_clear(sc->enp, rxq->buf_base_id,
	    EFX_RXQ_NBUFS(sc->rxq_entries));

	SFXGE_EVQ_UNLOCK(evq);
}