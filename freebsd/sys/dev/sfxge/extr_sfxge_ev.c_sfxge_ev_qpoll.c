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
struct TYPE_2__ {int /*<<< orphan*/  esm_map; int /*<<< orphan*/  esm_tag; } ;
struct sfxge_evq {scalar_t__ init_state; scalar_t__ rx_done; scalar_t__ tx_done; int /*<<< orphan*/  read_ptr; int /*<<< orphan*/  common; int /*<<< orphan*/ * txq; int /*<<< orphan*/ ** txqs; TYPE_1__ mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  B_TRUE ; 
 int EINVAL ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SFXGE_EVQ_LOCK (struct sfxge_evq*) ; 
 scalar_t__ SFXGE_EVQ_STARTED ; 
 scalar_t__ SFXGE_EVQ_STARTING ; 
 int /*<<< orphan*/  SFXGE_EVQ_UNLOCK (struct sfxge_evq*) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_ev_qpoll (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sfxge_evq*) ; 
 int efx_ev_qprime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_ev_callbacks ; 
 int /*<<< orphan*/  sfxge_ev_qcomplete (struct sfxge_evq*,int /*<<< orphan*/ ) ; 

int
sfxge_ev_qpoll(struct sfxge_evq *evq)
{
	int rc;

	SFXGE_EVQ_LOCK(evq);

	if (__predict_false(evq->init_state != SFXGE_EVQ_STARTING &&
			    evq->init_state != SFXGE_EVQ_STARTED)) {
		rc = EINVAL;
		goto fail;
	}

	/* Synchronize the DMA memory for reading */
	bus_dmamap_sync(evq->mem.esm_tag, evq->mem.esm_map,
	    BUS_DMASYNC_POSTREAD);

	KASSERT(evq->rx_done == 0, ("evq->rx_done != 0"));
	KASSERT(evq->tx_done == 0, ("evq->tx_done != 0"));
	KASSERT(evq->txq == NULL, ("evq->txq != NULL"));
	KASSERT(evq->txqs == &evq->txq, ("evq->txqs != &evq->txq"));

	/* Poll the queue */
	efx_ev_qpoll(evq->common, &evq->read_ptr, &sfxge_ev_callbacks, evq);

	evq->rx_done = 0;
	evq->tx_done = 0;

	/* Perform any pending completion processing */
	sfxge_ev_qcomplete(evq, B_TRUE);

	/* Re-prime the event queue for interrupts */
	if ((rc = efx_ev_qprime(evq->common, evq->read_ptr)) != 0)
		goto fail;

	SFXGE_EVQ_UNLOCK(evq);

	return (0);

fail:
	SFXGE_EVQ_UNLOCK(evq);
	return (rc);
}