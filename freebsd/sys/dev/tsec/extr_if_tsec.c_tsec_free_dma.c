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
struct tsec_softc {int /*<<< orphan*/  tsec_rx_vaddr; int /*<<< orphan*/  tsec_rx_dmap; int /*<<< orphan*/  tsec_rx_dtag; int /*<<< orphan*/  tsec_tx_vaddr; int /*<<< orphan*/  tsec_tx_dmap; int /*<<< orphan*/  tsec_tx_dtag; int /*<<< orphan*/  tsec_rx_mtag; TYPE_2__* rx_data; int /*<<< orphan*/  tsec_tx_mtag; TYPE_1__* tx_bufmap; } ;
struct TYPE_4__ {int /*<<< orphan*/ * map; scalar_t__ mbuf; } ;
struct TYPE_3__ {int /*<<< orphan*/ * map; scalar_t__ map_initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int TSEC_RX_NUM_DESC ; 
 int TSEC_TX_NUM_DESC ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (scalar_t__) ; 
 int /*<<< orphan*/  tsec_free_dma_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tsec_free_dma(struct tsec_softc *sc)
{
	int i;

	/* Free TX maps */
	for (i = 0; i < TSEC_TX_NUM_DESC; i++)
		if (sc->tx_bufmap[i].map_initialized)
			bus_dmamap_destroy(sc->tsec_tx_mtag,
			    sc->tx_bufmap[i].map);
	/* Destroy tag for TX mbufs */
	bus_dma_tag_destroy(sc->tsec_tx_mtag);

	/* Free RX mbufs and maps */
	for (i = 0; i < TSEC_RX_NUM_DESC; i++) {
		if (sc->rx_data[i].mbuf) {
			/* Unload buffer from DMA */
			bus_dmamap_sync(sc->tsec_rx_mtag, sc->rx_data[i].map,
			    BUS_DMASYNC_POSTREAD);
			bus_dmamap_unload(sc->tsec_rx_mtag,
			    sc->rx_data[i].map);

			/* Free buffer */
			m_freem(sc->rx_data[i].mbuf);
		}
		/* Destroy map for this buffer */
		if (sc->rx_data[i].map != NULL)
			bus_dmamap_destroy(sc->tsec_rx_mtag,
			    sc->rx_data[i].map);
	}
	/* Destroy tag for RX mbufs */
	bus_dma_tag_destroy(sc->tsec_rx_mtag);

	/* Unload TX/RX descriptors */
	tsec_free_dma_desc(sc->tsec_tx_dtag, sc->tsec_tx_dmap,
	    sc->tsec_tx_vaddr);
	tsec_free_dma_desc(sc->tsec_rx_dtag, sc->tsec_rx_dmap,
	    sc->tsec_rx_vaddr);
}