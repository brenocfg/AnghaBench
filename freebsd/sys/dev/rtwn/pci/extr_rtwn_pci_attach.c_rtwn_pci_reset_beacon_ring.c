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
struct rtwn_tx_ring {int /*<<< orphan*/  data_dmat; int /*<<< orphan*/  desc_map; int /*<<< orphan*/  desc_dmat; scalar_t__ desc; struct rtwn_tx_data* tx_data; } ;
struct rtwn_tx_desc_common {int flags0; } ;
struct rtwn_tx_data {int /*<<< orphan*/  map; } ;
struct rtwn_softc {int txdesc_len; } ;
struct rtwn_pci_softc {struct rtwn_tx_ring* tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int RTWN_FLAGS0_OWN ; 
 size_t RTWN_PCI_BEACON_QUEUE ; 
 struct rtwn_pci_softc* RTWN_PCI_SOFTC (struct rtwn_softc*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rtwn_pci_reset_beacon_ring(struct rtwn_softc *sc, int id)
{
	struct rtwn_pci_softc *pc = RTWN_PCI_SOFTC(sc);
	struct rtwn_tx_ring *ring = &pc->tx_ring[RTWN_PCI_BEACON_QUEUE];
	struct rtwn_tx_data *data = &ring->tx_data[id];
	struct rtwn_tx_desc_common *txd = (struct rtwn_tx_desc_common *)
	    ((uint8_t *)ring->desc + id * sc->txdesc_len);

	bus_dmamap_sync(ring->desc_dmat, ring->desc_map, BUS_DMASYNC_POSTREAD);
	if (txd->flags0 & RTWN_FLAGS0_OWN) {
		/* Clear OWN bit. */
		txd->flags0 &= ~RTWN_FLAGS0_OWN;
		bus_dmamap_sync(ring->desc_dmat, ring->desc_map,
		    BUS_DMASYNC_PREWRITE);

		/* Unload mbuf. */
		bus_dmamap_sync(ring->data_dmat, data->map,
		    BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(ring->data_dmat, data->map);
	}
}