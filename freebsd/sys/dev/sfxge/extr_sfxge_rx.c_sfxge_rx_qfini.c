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
struct sfxge_softc {struct sfxge_rxq** rxq; } ;
struct sfxge_rxq {scalar_t__ init_state; int /*<<< orphan*/  mem; struct sfxge_rxq* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_SFXGE ; 
 scalar_t__ SFXGE_RXQ_INITIALIZED ; 
 int /*<<< orphan*/  free (struct sfxge_rxq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_dma_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfxge_lro_fini (struct sfxge_rxq*) ; 

__attribute__((used)) static void
sfxge_rx_qfini(struct sfxge_softc *sc, unsigned int index)
{
	struct sfxge_rxq *rxq;

	rxq = sc->rxq[index];

	KASSERT(rxq->init_state == SFXGE_RXQ_INITIALIZED,
	    ("rxq->init_state != SFXGE_RXQ_INITIALIZED"));

	/* Free the context array and the flow table. */
	free(rxq->queue, M_SFXGE);
	sfxge_lro_fini(rxq);

	/* Release DMA memory. */
	sfxge_dma_free(&rxq->mem);

	sc->rxq[index] = NULL;

	free(rxq, M_SFXGE);
}