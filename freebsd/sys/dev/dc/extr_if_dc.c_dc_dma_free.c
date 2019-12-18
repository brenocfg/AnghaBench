#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * dc_sbuf; int /*<<< orphan*/ ** dc_tx_map; int /*<<< orphan*/ ** dc_rx_map; } ;
struct TYPE_3__ {scalar_t__ dc_rx_list_paddr; scalar_t__ dc_tx_list_paddr; int /*<<< orphan*/ * dc_tx_list; int /*<<< orphan*/ * dc_rx_list; } ;
struct dc_softc {scalar_t__ dc_saddr; int /*<<< orphan*/ * dc_stag; int /*<<< orphan*/  dc_smap; TYPE_2__ dc_cdata; int /*<<< orphan*/ * dc_tx_ltag; int /*<<< orphan*/  dc_tx_lmap; TYPE_1__ dc_ldata; int /*<<< orphan*/ * dc_rx_ltag; int /*<<< orphan*/  dc_rx_lmap; int /*<<< orphan*/ * dc_tx_mtag; int /*<<< orphan*/ * dc_rx_mtag; int /*<<< orphan*/ * dc_sparemap; } ;

/* Variables and functions */
 int DC_RX_LIST_CNT ; 
 int DC_TX_LIST_CNT ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dc_dma_free(struct dc_softc *sc)
{
	int i;

	/* RX buffers. */
	if (sc->dc_rx_mtag != NULL) {
		for (i = 0; i < DC_RX_LIST_CNT; i++) {
			if (sc->dc_cdata.dc_rx_map[i] != NULL)
				bus_dmamap_destroy(sc->dc_rx_mtag,
				    sc->dc_cdata.dc_rx_map[i]);
		}
		if (sc->dc_sparemap != NULL)
			bus_dmamap_destroy(sc->dc_rx_mtag, sc->dc_sparemap);
		bus_dma_tag_destroy(sc->dc_rx_mtag);
	}

	/* TX buffers. */
	if (sc->dc_rx_mtag != NULL) {
		for (i = 0; i < DC_TX_LIST_CNT; i++) {
			if (sc->dc_cdata.dc_tx_map[i] != NULL)
				bus_dmamap_destroy(sc->dc_tx_mtag,
				    sc->dc_cdata.dc_tx_map[i]);
		}
		bus_dma_tag_destroy(sc->dc_tx_mtag);
	}

	/* RX descriptor list. */
	if (sc->dc_rx_ltag) {
		if (sc->dc_ldata.dc_rx_list_paddr != 0)
			bus_dmamap_unload(sc->dc_rx_ltag, sc->dc_rx_lmap);
		if (sc->dc_ldata.dc_rx_list != NULL)
			bus_dmamem_free(sc->dc_rx_ltag, sc->dc_ldata.dc_rx_list,
			    sc->dc_rx_lmap);
		bus_dma_tag_destroy(sc->dc_rx_ltag);
	}

	/* TX descriptor list. */
	if (sc->dc_tx_ltag) {
		if (sc->dc_ldata.dc_tx_list_paddr != 0)
			bus_dmamap_unload(sc->dc_tx_ltag, sc->dc_tx_lmap);
		if (sc->dc_ldata.dc_tx_list != NULL)
			bus_dmamem_free(sc->dc_tx_ltag, sc->dc_ldata.dc_tx_list,
			    sc->dc_tx_lmap);
		bus_dma_tag_destroy(sc->dc_tx_ltag);
	}

	/* multicast setup frame. */
	if (sc->dc_stag) {
		if (sc->dc_saddr != 0)
			bus_dmamap_unload(sc->dc_stag, sc->dc_smap);
		if (sc->dc_cdata.dc_sbuf != NULL)
			bus_dmamem_free(sc->dc_stag, sc->dc_cdata.dc_sbuf,
			    sc->dc_smap);
		bus_dma_tag_destroy(sc->dc_stag);
	}
}