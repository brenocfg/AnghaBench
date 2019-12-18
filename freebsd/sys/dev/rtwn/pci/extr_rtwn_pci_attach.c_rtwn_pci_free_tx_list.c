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
struct rtwn_tx_ring {scalar_t__ cur; scalar_t__ last; scalar_t__ queued; int /*<<< orphan*/ * data_dmat; struct rtwn_tx_data* tx_data; int /*<<< orphan*/ * desc_dmat; int /*<<< orphan*/  desc_map; int /*<<< orphan*/ * desc; } ;
struct rtwn_tx_data {int /*<<< orphan*/ * m; int /*<<< orphan*/  map; } ;
struct rtwn_softc {int qfullmsk; } ;
struct rtwn_pci_softc {struct rtwn_tx_ring* tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 struct rtwn_pci_softc* RTWN_PCI_SOFTC (struct rtwn_softc*) ; 
 int RTWN_PCI_TX_LIST_COUNT ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rtwn_pci_free_tx_list(struct rtwn_softc *sc, int qid)
{
	struct rtwn_pci_softc *pc = RTWN_PCI_SOFTC(sc);
	struct rtwn_tx_ring *tx_ring = &pc->tx_ring[qid];
	struct rtwn_tx_data *tx_data;
	int i;

	if (tx_ring->desc_dmat != NULL) {
		if (tx_ring->desc != NULL) {
			bus_dmamap_sync(tx_ring->desc_dmat,
			    tx_ring->desc_map, BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(tx_ring->desc_dmat,
			    tx_ring->desc_map);
			bus_dmamem_free(tx_ring->desc_dmat, tx_ring->desc,
			    tx_ring->desc_map);
		}
		bus_dma_tag_destroy(tx_ring->desc_dmat);
	}

	for (i = 0; i < RTWN_PCI_TX_LIST_COUNT; i++) {
		tx_data = &tx_ring->tx_data[i];

		if (tx_data->m != NULL) {
			bus_dmamap_sync(tx_ring->data_dmat, tx_data->map,
			    BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(tx_ring->data_dmat, tx_data->map);
			m_freem(tx_data->m);
			tx_data->m = NULL;
		}
	}
	if (tx_ring->data_dmat != NULL) {
		bus_dma_tag_destroy(tx_ring->data_dmat);
		tx_ring->data_dmat = NULL;
	}

	sc->qfullmsk &= ~(1 << qid);
	tx_ring->queued = 0;
	tx_ring->last = tx_ring->cur = 0;
}