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
struct sfxge_softc {struct sfxge_evq** evq; } ;
struct sfxge_evq {scalar_t__ init_state; int /*<<< orphan*/  mem; int /*<<< orphan*/  txq; int /*<<< orphan*/ * txqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_SFXGE ; 
 scalar_t__ SFXGE_EVQ_INITIALIZED ; 
 int /*<<< orphan*/  SFXGE_EVQ_LOCK_DESTROY (struct sfxge_evq*) ; 
 int /*<<< orphan*/  free (struct sfxge_evq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_dma_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sfxge_ev_qfini(struct sfxge_softc *sc, unsigned int index)
{
	struct sfxge_evq *evq;

	evq = sc->evq[index];

	KASSERT(evq->init_state == SFXGE_EVQ_INITIALIZED,
	    ("evq->init_state != SFXGE_EVQ_INITIALIZED"));
	KASSERT(evq->txqs == &evq->txq, ("evq->txqs != &evq->txq"));

	sfxge_dma_free(&evq->mem);

	sc->evq[index] = NULL;

	SFXGE_EVQ_LOCK_DESTROY(evq);

	free(evq, M_SFXGE);
}