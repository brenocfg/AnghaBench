#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sfxge_softc {int /*<<< orphan*/  enp; int /*<<< orphan*/  ev_moderation; struct sfxge_evq** evq; } ;
struct TYPE_4__ {int /*<<< orphan*/  esm_base; } ;
struct sfxge_evq {scalar_t__ init_state; int /*<<< orphan*/  entries; int /*<<< orphan*/  buf_base_id; int /*<<< orphan*/  common; int /*<<< orphan*/  read_ptr; TYPE_1__ mem; } ;
typedef  TYPE_1__ efsys_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_EVQ_FLAGS_TYPE_AUTO ; 
 int /*<<< orphan*/  EFX_EVQ_NBUFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFX_EVQ_SIZE (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ SFXGE_EVQ_INITIALIZED ; 
 int /*<<< orphan*/  SFXGE_EVQ_LOCK (struct sfxge_evq*) ; 
 scalar_t__ SFXGE_EVQ_STARTED ; 
 scalar_t__ SFXGE_EVQ_STARTING ; 
 int /*<<< orphan*/  SFXGE_EVQ_UNLOCK (struct sfxge_evq*) ; 
 int efx_ev_qcreate (int /*<<< orphan*/ ,unsigned int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_ev_qdestroy (int /*<<< orphan*/ ) ; 
 int efx_ev_qprime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_sram_buf_tbl_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int efx_sram_buf_tbl_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause (char*,int) ; 

__attribute__((used)) static int
sfxge_ev_qstart(struct sfxge_softc *sc, unsigned int index)
{
	struct sfxge_evq *evq;
	efsys_mem_t *esmp;
	int count;
	int rc;

	evq = sc->evq[index];
	esmp = &evq->mem;

	KASSERT(evq->init_state == SFXGE_EVQ_INITIALIZED,
	    ("evq->init_state != SFXGE_EVQ_INITIALIZED"));

	/* Clear all events. */
	(void)memset(esmp->esm_base, 0xff, EFX_EVQ_SIZE(evq->entries));

	/* Program the buffer table. */
	if ((rc = efx_sram_buf_tbl_set(sc->enp, evq->buf_base_id, esmp,
	    EFX_EVQ_NBUFS(evq->entries))) != 0)
		return (rc);

	/* Create the common code event queue. */
	if ((rc = efx_ev_qcreate(sc->enp, index, esmp, evq->entries,
	    evq->buf_base_id, sc->ev_moderation, EFX_EVQ_FLAGS_TYPE_AUTO,
	    &evq->common)) != 0)
		goto fail;

	SFXGE_EVQ_LOCK(evq);

	/* Prime the event queue for interrupts */
	if ((rc = efx_ev_qprime(evq->common, evq->read_ptr)) != 0)
		goto fail2;

	evq->init_state = SFXGE_EVQ_STARTING;

	SFXGE_EVQ_UNLOCK(evq);

	/* Wait for the initialization event */
	count = 0;
	do {
		/* Pause for 100 ms */
		pause("sfxge evq init", hz / 10);

		/* Check to see if the test event has been processed */
		if (evq->init_state == SFXGE_EVQ_STARTED)
			goto done;

	} while (++count < 20);

	rc = ETIMEDOUT;
	goto fail3;

done:
	return (0);

fail3:
	SFXGE_EVQ_LOCK(evq);
	evq->init_state = SFXGE_EVQ_INITIALIZED;
fail2:
	SFXGE_EVQ_UNLOCK(evq);
	efx_ev_qdestroy(evq->common);
fail:
	efx_sram_buf_tbl_clear(sc->enp, evq->buf_base_id,
	    EFX_EVQ_NBUFS(evq->entries));

	return (rc);
}