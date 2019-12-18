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
struct sfxge_softc {int /*<<< orphan*/  rxq_entries; int /*<<< orphan*/  enp; struct sfxge_evq** evq; struct sfxge_rxq** rxq; } ;
struct sfxge_rxq {scalar_t__ init_state; int /*<<< orphan*/  buf_base_id; int /*<<< orphan*/  flush_state; int /*<<< orphan*/  common; int /*<<< orphan*/  mem; } ;
struct sfxge_evq {scalar_t__ init_state; int /*<<< orphan*/  common; } ;
typedef  int /*<<< orphan*/  efsys_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  EFX_RXQ_FLAG_NONE ; 
 int /*<<< orphan*/  EFX_RXQ_LIMIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFX_RXQ_NBUFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFX_RXQ_TYPE_DEFAULT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SFXGE_ADAPTER_LOCK_ASSERT_OWNED (struct sfxge_softc*) ; 
 int /*<<< orphan*/  SFXGE_EVQ_LOCK (struct sfxge_evq*) ; 
 scalar_t__ SFXGE_EVQ_STARTED ; 
 int /*<<< orphan*/  SFXGE_EVQ_UNLOCK (struct sfxge_evq*) ; 
 int /*<<< orphan*/  SFXGE_FLUSH_REQUIRED ; 
 scalar_t__ SFXGE_RXQ_INITIALIZED ; 
 scalar_t__ SFXGE_RXQ_STARTED ; 
 int efx_rx_qcreate (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_rx_qenable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_sram_buf_tbl_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int efx_sram_buf_tbl_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_rx_qfill (struct sfxge_rxq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sfxge_rx_qstart(struct sfxge_softc *sc, unsigned int index)
{
	struct sfxge_rxq *rxq;
	efsys_mem_t *esmp;
	struct sfxge_evq *evq;
	int rc;

	SFXGE_ADAPTER_LOCK_ASSERT_OWNED(sc);

	rxq = sc->rxq[index];
	esmp = &rxq->mem;
	evq = sc->evq[index];

	KASSERT(rxq->init_state == SFXGE_RXQ_INITIALIZED,
	    ("rxq->init_state != SFXGE_RXQ_INITIALIZED"));
	KASSERT(evq->init_state == SFXGE_EVQ_STARTED,
	    ("evq->init_state != SFXGE_EVQ_STARTED"));

	/* Program the buffer table. */
	if ((rc = efx_sram_buf_tbl_set(sc->enp, rxq->buf_base_id, esmp,
	    EFX_RXQ_NBUFS(sc->rxq_entries))) != 0)
		return (rc);

	/* Create the common code receive queue. */
	if ((rc = efx_rx_qcreate(sc->enp, index, 0, EFX_RXQ_TYPE_DEFAULT,
	    esmp, sc->rxq_entries, rxq->buf_base_id, EFX_RXQ_FLAG_NONE,
	    evq->common, &rxq->common)) != 0)
		goto fail;

	SFXGE_EVQ_LOCK(evq);

	/* Enable the receive queue. */
	efx_rx_qenable(rxq->common);

	rxq->init_state = SFXGE_RXQ_STARTED;
	rxq->flush_state = SFXGE_FLUSH_REQUIRED;

	/* Try to fill the queue from the pool. */
	sfxge_rx_qfill(rxq, EFX_RXQ_LIMIT(sc->rxq_entries), B_FALSE);

	SFXGE_EVQ_UNLOCK(evq);

	return (0);

fail:
	efx_sram_buf_tbl_clear(sc->enp, rxq->buf_base_id,
	    EFX_RXQ_NBUFS(sc->rxq_entries));
	return (rc);
}