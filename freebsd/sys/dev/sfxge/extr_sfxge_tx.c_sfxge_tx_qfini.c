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
struct sfxge_txq {scalar_t__ init_state; scalar_t__ type; int /*<<< orphan*/  mem; struct sfxge_txq* stmp; int /*<<< orphan*/  map; int /*<<< orphan*/  packet_dma_tag; struct sfxge_txq* pend_desc; } ;
struct sfxge_softc {unsigned int txq_entries; struct sfxge_txq** txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_SFXGE ; 
 scalar_t__ SFXGE_TXQ_INITIALIZED ; 
 scalar_t__ SFXGE_TXQ_IP_TCP_UDP_CKSUM ; 
 int /*<<< orphan*/  SFXGE_TXQ_LOCK_DESTROY (struct sfxge_txq*) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sfxge_txq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_dma_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tso_fini (struct sfxge_txq*) ; 

__attribute__((used)) static void
sfxge_tx_qfini(struct sfxge_softc *sc, unsigned int index)
{
	struct sfxge_txq *txq;
	unsigned int nmaps;

	txq = sc->txq[index];

	KASSERT(txq->init_state == SFXGE_TXQ_INITIALIZED,
	    ("txq->init_state != SFXGE_TXQ_INITIALIZED"));

	if (txq->type == SFXGE_TXQ_IP_TCP_UDP_CKSUM)
		tso_fini(txq);

	/* Free the context arrays. */
	free(txq->pend_desc, M_SFXGE);
	nmaps = sc->txq_entries;
	while (nmaps-- != 0)
		bus_dmamap_destroy(txq->packet_dma_tag, txq->stmp[nmaps].map);
	free(txq->stmp, M_SFXGE);

	/* Release DMA memory mapping. */
	sfxge_dma_free(&txq->mem);

	sc->txq[index] = NULL;

	SFXGE_TXQ_LOCK_DESTROY(txq);

	free(txq, M_SFXGE);
}