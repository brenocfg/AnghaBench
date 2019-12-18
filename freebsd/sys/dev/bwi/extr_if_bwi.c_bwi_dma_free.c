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
struct bwi_ring_data {int /*<<< orphan*/  rdata_dmap; int /*<<< orphan*/ * rdata_desc; } ;
struct bwi_softc {int /*<<< orphan*/ * sc_parent_dtag; int /*<<< orphan*/ * sc_rxring_dtag; struct bwi_ring_data sc_rx_rdata; int /*<<< orphan*/ * sc_txring_dtag; struct bwi_ring_data* sc_tx_rdata; } ;

/* Variables and functions */
 int BWI_TX_NRING ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_dma_mbuf_destroy (struct bwi_softc*,int,int) ; 
 int /*<<< orphan*/  bwi_dma_txstats_free (struct bwi_softc*) ; 

__attribute__((used)) static void
bwi_dma_free(struct bwi_softc *sc)
{
	if (sc->sc_txring_dtag != NULL) {
		int i;

		for (i = 0; i < BWI_TX_NRING; ++i) {
			struct bwi_ring_data *rd = &sc->sc_tx_rdata[i];

			if (rd->rdata_desc != NULL) {
				bus_dmamap_unload(sc->sc_txring_dtag,
						  rd->rdata_dmap);
				bus_dmamem_free(sc->sc_txring_dtag,
						rd->rdata_desc,
						rd->rdata_dmap);
			}
		}
		bus_dma_tag_destroy(sc->sc_txring_dtag);
	}

	if (sc->sc_rxring_dtag != NULL) {
		struct bwi_ring_data *rd = &sc->sc_rx_rdata;

		if (rd->rdata_desc != NULL) {
			bus_dmamap_unload(sc->sc_rxring_dtag, rd->rdata_dmap);
			bus_dmamem_free(sc->sc_rxring_dtag, rd->rdata_desc,
					rd->rdata_dmap);
		}
		bus_dma_tag_destroy(sc->sc_rxring_dtag);
	}

	bwi_dma_txstats_free(sc);
	bwi_dma_mbuf_destroy(sc, BWI_TX_NRING, 1);

	if (sc->sc_parent_dtag != NULL)
		bus_dma_tag_destroy(sc->sc_parent_dtag);
}