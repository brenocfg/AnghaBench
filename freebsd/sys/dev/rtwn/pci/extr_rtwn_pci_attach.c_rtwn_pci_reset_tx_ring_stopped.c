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
typedef  int /*<<< orphan*/  uint8_t ;
struct rtwn_tx_ring {scalar_t__ cur; scalar_t__ last; scalar_t__ queued; int /*<<< orphan*/  desc_map; int /*<<< orphan*/  desc_dmat; int /*<<< orphan*/  data_dmat; scalar_t__ desc; struct rtwn_tx_data* tx_data; } ;
struct rtwn_tx_data {int /*<<< orphan*/ * ni; int /*<<< orphan*/ * m; int /*<<< orphan*/  map; } ;
struct rtwn_softc {int txdesc_len; int qfullmsk; } ;
struct rtwn_pci_softc {struct rtwn_tx_ring* tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 struct rtwn_pci_softc* RTWN_PCI_SOFTC (struct rtwn_softc*) ; 
 int RTWN_PCI_TX_LIST_COUNT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtwn_pci_copy_tx_desc (struct rtwn_pci_softc*,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rtwn_pci_reset_tx_ring_stopped(struct rtwn_softc *sc, int qid)
{
	struct rtwn_pci_softc *pc = RTWN_PCI_SOFTC(sc);
	struct rtwn_tx_ring *ring = &pc->tx_ring[qid];
	int i;

	for (i = 0; i < RTWN_PCI_TX_LIST_COUNT; i++) {
		struct rtwn_tx_data *data = &ring->tx_data[i];
		void *desc = (uint8_t *)ring->desc + sc->txdesc_len * i;

		rtwn_pci_copy_tx_desc(pc, desc, NULL);

		if (data->m != NULL) {
			bus_dmamap_sync(ring->data_dmat, data->map,
			    BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(ring->data_dmat, data->map);
			m_freem(data->m);
			data->m = NULL;
		}
		if (data->ni != NULL) {
			ieee80211_free_node(data->ni);
			data->ni = NULL;
		}
	}

	bus_dmamap_sync(ring->desc_dmat, ring->desc_map,
	    BUS_DMASYNC_POSTWRITE);

	sc->qfullmsk &= ~(1 << qid);
	ring->queued = 0;
	ring->last = ring->cur = 0;
}