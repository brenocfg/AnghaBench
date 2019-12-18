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
struct sfxge_softc {int /*<<< orphan*/  enp; struct sfxge_evq** evq; } ;
struct sfxge_evq {scalar_t__ init_state; int /*<<< orphan*/  entries; int /*<<< orphan*/  buf_base_id; int /*<<< orphan*/  common; int /*<<< orphan*/  stats; int /*<<< orphan*/  exception; scalar_t__ read_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  EFX_EVQ_NBUFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ SFXGE_EVQ_INITIALIZED ; 
 int /*<<< orphan*/  SFXGE_EVQ_LOCK (struct sfxge_evq*) ; 
 scalar_t__ SFXGE_EVQ_STARTED ; 
 int /*<<< orphan*/  SFXGE_EVQ_UNLOCK (struct sfxge_evq*) ; 
 int /*<<< orphan*/  efx_ev_qdestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_ev_qstats_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_sram_buf_tbl_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sfxge_ev_qstop(struct sfxge_softc *sc, unsigned int index)
{
	struct sfxge_evq *evq;

	evq = sc->evq[index];

	KASSERT(evq->init_state == SFXGE_EVQ_STARTED,
	    ("evq->init_state != SFXGE_EVQ_STARTED"));

	SFXGE_EVQ_LOCK(evq);
	evq->init_state = SFXGE_EVQ_INITIALIZED;
	evq->read_ptr = 0;
	evq->exception = B_FALSE;

#if EFSYS_OPT_QSTATS
	/* Add event counts before discarding the common evq state */
	efx_ev_qstats_update(evq->common, evq->stats);
#endif

	efx_ev_qdestroy(evq->common);
	efx_sram_buf_tbl_clear(sc->enp, evq->buf_base_id,
	    EFX_EVQ_NBUFS(evq->entries));
	SFXGE_EVQ_UNLOCK(evq);
}