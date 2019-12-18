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
struct et_txstatus_data {int /*<<< orphan*/  txsd_paddr; int /*<<< orphan*/  txsd_dmap; int /*<<< orphan*/  txsd_status; int /*<<< orphan*/  txsd_dtag; } ;
struct et_txdesc_ring {int /*<<< orphan*/  tr_paddr; int /*<<< orphan*/  tr_dmap; int /*<<< orphan*/  tr_desc; int /*<<< orphan*/  tr_dtag; } ;
struct et_txbuf_data {TYPE_2__* tbd_buf; } ;
struct et_rxstatus_data {int dummy; } ;
struct et_rxstat_ring {int /*<<< orphan*/  rsr_paddr; int /*<<< orphan*/  rsr_dmap; int /*<<< orphan*/  rsr_stat; int /*<<< orphan*/  rsr_dtag; } ;
struct et_softc {int /*<<< orphan*/ * sc_dtag; struct et_txstatus_data sc_tx_status; struct et_txdesc_ring sc_tx_ring; struct et_rxstatus_data sc_rx_status; struct et_rxstat_ring sc_rxstat_ring; struct et_rxdesc_ring* sc_rx_ring; int /*<<< orphan*/ * sc_tx_tag; struct et_txbuf_data sc_tx_data; int /*<<< orphan*/ * sc_rx_tag; int /*<<< orphan*/ * sc_rx_sparemap; struct et_rxbuf_data* sc_rx_data; int /*<<< orphan*/ * sc_rx_mini_tag; int /*<<< orphan*/ * sc_rx_mini_sparemap; } ;
struct et_rxdesc_ring {int /*<<< orphan*/  rr_paddr; int /*<<< orphan*/  rr_dmap; int /*<<< orphan*/  rr_desc; int /*<<< orphan*/  rr_dtag; } ;
struct et_rxbuf_data {TYPE_1__* rbd_buf; } ;
struct TYPE_4__ {int /*<<< orphan*/ * tb_dmap; } ;
struct TYPE_3__ {int /*<<< orphan*/ * rb_dmap; } ;

/* Variables and functions */
 int ET_RX_NDESC ; 
 int ET_TX_NDESC ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  et_dma_ring_free (struct et_softc*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
et_dma_free(struct et_softc *sc)
{
	struct et_txdesc_ring *tx_ring;
	struct et_rxdesc_ring *rx_ring;
	struct et_txstatus_data *txsd;
	struct et_rxstat_ring *rxst_ring;
	struct et_rxstatus_data *rxsd;
	struct et_rxbuf_data *rbd;
        struct et_txbuf_data *tbd;
	int i;

	/* Destroy DMA maps for mini RX buffers, ring 0. */
	rbd = &sc->sc_rx_data[0];
	for (i = 0; i < ET_RX_NDESC; i++) {
		if (rbd->rbd_buf[i].rb_dmap) {
			bus_dmamap_destroy(sc->sc_rx_mini_tag,
			    rbd->rbd_buf[i].rb_dmap);
			rbd->rbd_buf[i].rb_dmap = NULL;
		}
	}
	if (sc->sc_rx_mini_sparemap) {
		bus_dmamap_destroy(sc->sc_rx_mini_tag, sc->sc_rx_mini_sparemap);
		sc->sc_rx_mini_sparemap = NULL;
	}
	if (sc->sc_rx_mini_tag) {
		bus_dma_tag_destroy(sc->sc_rx_mini_tag);
		sc->sc_rx_mini_tag = NULL;
	}

	/* Destroy DMA maps for standard RX buffers, ring 1. */
	rbd = &sc->sc_rx_data[1];
	for (i = 0; i < ET_RX_NDESC; i++) {
		if (rbd->rbd_buf[i].rb_dmap) {
			bus_dmamap_destroy(sc->sc_rx_tag,
			    rbd->rbd_buf[i].rb_dmap);
			rbd->rbd_buf[i].rb_dmap = NULL;
		}
	}
	if (sc->sc_rx_sparemap) {
		bus_dmamap_destroy(sc->sc_rx_tag, sc->sc_rx_sparemap);
		sc->sc_rx_sparemap = NULL;
	}
	if (sc->sc_rx_tag) {
		bus_dma_tag_destroy(sc->sc_rx_tag);
		sc->sc_rx_tag = NULL;
	}

	/* Destroy DMA maps for TX buffers. */
	tbd = &sc->sc_tx_data;
	for (i = 0; i < ET_TX_NDESC; i++) {
		if (tbd->tbd_buf[i].tb_dmap) {
			bus_dmamap_destroy(sc->sc_tx_tag,
			    tbd->tbd_buf[i].tb_dmap);
			tbd->tbd_buf[i].tb_dmap = NULL;
		}
	}
	if (sc->sc_tx_tag) {
		bus_dma_tag_destroy(sc->sc_tx_tag);
		sc->sc_tx_tag = NULL;
	}

	/* Destroy mini RX ring, ring 0. */
	rx_ring = &sc->sc_rx_ring[0];
	et_dma_ring_free(sc, &rx_ring->rr_dtag, (void *)&rx_ring->rr_desc,
	    rx_ring->rr_dmap, &rx_ring->rr_paddr);
	/* Destroy standard RX ring, ring 1. */
	rx_ring = &sc->sc_rx_ring[1];
	et_dma_ring_free(sc, &rx_ring->rr_dtag, (void *)&rx_ring->rr_desc,
	    rx_ring->rr_dmap, &rx_ring->rr_paddr);
	/* Destroy RX stat ring. */
	rxst_ring = &sc->sc_rxstat_ring;
	et_dma_ring_free(sc, &rxst_ring->rsr_dtag, (void *)&rxst_ring->rsr_stat,
	    rxst_ring->rsr_dmap, &rxst_ring->rsr_paddr);
	/* Destroy RX status block. */
	rxsd = &sc->sc_rx_status;
	et_dma_ring_free(sc, &rxst_ring->rsr_dtag, (void *)&rxst_ring->rsr_stat,
	    rxst_ring->rsr_dmap, &rxst_ring->rsr_paddr);
	/* Destroy TX ring. */
	tx_ring = &sc->sc_tx_ring;
	et_dma_ring_free(sc, &tx_ring->tr_dtag, (void *)&tx_ring->tr_desc,
	    tx_ring->tr_dmap, &tx_ring->tr_paddr);
	/* Destroy TX status block. */
	txsd = &sc->sc_tx_status;
	et_dma_ring_free(sc, &txsd->txsd_dtag, (void *)&txsd->txsd_status,
	    txsd->txsd_dmap, &txsd->txsd_paddr);

	/* Destroy the parent tag. */
	if (sc->sc_dtag) {
		bus_dma_tag_destroy(sc->sc_dtag);
		sc->sc_dtag = NULL;
	}
}