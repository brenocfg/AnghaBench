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
struct vr_txdesc {int /*<<< orphan*/ * tx_dmamap; } ;
struct TYPE_4__ {int /*<<< orphan*/ * vr_parent_tag; int /*<<< orphan*/ * vr_rx_tag; int /*<<< orphan*/ * vr_rx_sparemap; struct vr_rxdesc* vr_rxdesc; int /*<<< orphan*/ * vr_tx_tag; struct vr_txdesc* vr_txdesc; int /*<<< orphan*/ * vr_rx_ring_tag; int /*<<< orphan*/  vr_rx_ring_map; int /*<<< orphan*/ * vr_tx_ring_tag; int /*<<< orphan*/  vr_tx_ring_map; } ;
struct TYPE_3__ {scalar_t__ vr_rx_ring_paddr; int /*<<< orphan*/ * vr_rx_ring; scalar_t__ vr_tx_ring_paddr; int /*<<< orphan*/ * vr_tx_ring; } ;
struct vr_softc {TYPE_2__ vr_cdata; TYPE_1__ vr_rdata; } ;
struct vr_rxdesc {int /*<<< orphan*/ * rx_dmamap; } ;

/* Variables and functions */
 int VR_RX_RING_CNT ; 
 int VR_TX_RING_CNT ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vr_dma_free(struct vr_softc *sc)
{
	struct vr_txdesc	*txd;
	struct vr_rxdesc	*rxd;
	int			i;

	/* Tx ring. */
	if (sc->vr_cdata.vr_tx_ring_tag) {
		if (sc->vr_rdata.vr_tx_ring_paddr)
			bus_dmamap_unload(sc->vr_cdata.vr_tx_ring_tag,
			    sc->vr_cdata.vr_tx_ring_map);
		if (sc->vr_rdata.vr_tx_ring)
			bus_dmamem_free(sc->vr_cdata.vr_tx_ring_tag,
			    sc->vr_rdata.vr_tx_ring,
			    sc->vr_cdata.vr_tx_ring_map);
		sc->vr_rdata.vr_tx_ring = NULL;
		sc->vr_rdata.vr_tx_ring_paddr = 0;
		bus_dma_tag_destroy(sc->vr_cdata.vr_tx_ring_tag);
		sc->vr_cdata.vr_tx_ring_tag = NULL;
	}
	/* Rx ring. */
	if (sc->vr_cdata.vr_rx_ring_tag) {
		if (sc->vr_rdata.vr_rx_ring_paddr)
			bus_dmamap_unload(sc->vr_cdata.vr_rx_ring_tag,
			    sc->vr_cdata.vr_rx_ring_map);
		if (sc->vr_rdata.vr_rx_ring)
			bus_dmamem_free(sc->vr_cdata.vr_rx_ring_tag,
			    sc->vr_rdata.vr_rx_ring,
			    sc->vr_cdata.vr_rx_ring_map);
		sc->vr_rdata.vr_rx_ring = NULL;
		sc->vr_rdata.vr_rx_ring_paddr = 0;
		bus_dma_tag_destroy(sc->vr_cdata.vr_rx_ring_tag);
		sc->vr_cdata.vr_rx_ring_tag = NULL;
	}
	/* Tx buffers. */
	if (sc->vr_cdata.vr_tx_tag) {
		for (i = 0; i < VR_TX_RING_CNT; i++) {
			txd = &sc->vr_cdata.vr_txdesc[i];
			if (txd->tx_dmamap) {
				bus_dmamap_destroy(sc->vr_cdata.vr_tx_tag,
				    txd->tx_dmamap);
				txd->tx_dmamap = NULL;
			}
		}
		bus_dma_tag_destroy(sc->vr_cdata.vr_tx_tag);
		sc->vr_cdata.vr_tx_tag = NULL;
	}
	/* Rx buffers. */
	if (sc->vr_cdata.vr_rx_tag) {
		for (i = 0; i < VR_RX_RING_CNT; i++) {
			rxd = &sc->vr_cdata.vr_rxdesc[i];
			if (rxd->rx_dmamap) {
				bus_dmamap_destroy(sc->vr_cdata.vr_rx_tag,
				    rxd->rx_dmamap);
				rxd->rx_dmamap = NULL;
			}
		}
		if (sc->vr_cdata.vr_rx_sparemap) {
			bus_dmamap_destroy(sc->vr_cdata.vr_rx_tag,
			    sc->vr_cdata.vr_rx_sparemap);
			sc->vr_cdata.vr_rx_sparemap = 0;
		}
		bus_dma_tag_destroy(sc->vr_cdata.vr_rx_tag);
		sc->vr_cdata.vr_rx_tag = NULL;
	}

	if (sc->vr_cdata.vr_parent_tag) {
		bus_dma_tag_destroy(sc->vr_cdata.vr_parent_tag);
		sc->vr_cdata.vr_parent_tag = NULL;
	}
}