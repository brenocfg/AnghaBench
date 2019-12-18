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
struct msk_txdesc {int /*<<< orphan*/ * tx_dmamap; int /*<<< orphan*/ * tx_m; } ;
struct msk_rxdesc {int /*<<< orphan*/ * rx_dmamap; int /*<<< orphan*/ * rx_m; } ;
struct TYPE_3__ {int /*<<< orphan*/  msk_rx_tag; struct msk_rxdesc* msk_rxdesc; int /*<<< orphan*/ * msk_rx_sparemap; int /*<<< orphan*/  msk_tx_tag; struct msk_txdesc* msk_txdesc; int /*<<< orphan*/  msk_rx_ring_map; int /*<<< orphan*/  msk_rx_ring_tag; int /*<<< orphan*/  msk_tx_ring_map; int /*<<< orphan*/  msk_tx_ring_tag; int /*<<< orphan*/  msk_parent_tag; } ;
struct TYPE_4__ {scalar_t__ msk_rx_ring_paddr; int /*<<< orphan*/  msk_rx_ring; scalar_t__ msk_tx_ring_paddr; int /*<<< orphan*/  msk_tx_ring; } ;
struct msk_if_softc {int msk_flags; int /*<<< orphan*/  msk_if_dev; TYPE_1__ msk_cdata; TYPE_2__ msk_rdata; } ;
struct msk_dmamap_arg {scalar_t__ msk_busaddr; } ;
typedef  int bus_size_t ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int MSK_FLAG_RAMBUF ; 
 int MSK_MAXTXSEGS ; 
 int MSK_RING_ALIGN ; 
 int MSK_RX_BUF_ALIGN ; 
 int MSK_RX_RING_CNT ; 
 int /*<<< orphan*/  MSK_RX_RING_SZ ; 
 int /*<<< orphan*/  MSK_TSO_MAXSGSIZE ; 
 int /*<<< orphan*/  MSK_TSO_MAXSIZE ; 
 int MSK_TX_RING_CNT ; 
 int /*<<< orphan*/  MSK_TX_RING_SZ ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct msk_dmamap_arg*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msk_dmamap_cb ; 

__attribute__((used)) static int
msk_txrx_dma_alloc(struct msk_if_softc *sc_if)
{
	struct msk_dmamap_arg ctx;
	struct msk_txdesc *txd;
	struct msk_rxdesc *rxd;
	bus_size_t rxalign;
	int error, i;

	/* Create parent DMA tag. */
	error = bus_dma_tag_create(
		    bus_get_dma_tag(sc_if->msk_if_dev),	/* parent */
		    1, 0,			/* alignment, boundary */
		    BUS_SPACE_MAXADDR,		/* lowaddr */
		    BUS_SPACE_MAXADDR,		/* highaddr */
		    NULL, NULL,			/* filter, filterarg */
		    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
		    0,				/* nsegments */
		    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
		    0,				/* flags */
		    NULL, NULL,			/* lockfunc, lockarg */
		    &sc_if->msk_cdata.msk_parent_tag);
	if (error != 0) {
		device_printf(sc_if->msk_if_dev,
		    "failed to create parent DMA tag\n");
		goto fail;
	}
	/* Create tag for Tx ring. */
	error = bus_dma_tag_create(sc_if->msk_cdata.msk_parent_tag,/* parent */
		    MSK_RING_ALIGN, 0,		/* alignment, boundary */
		    BUS_SPACE_MAXADDR,		/* lowaddr */
		    BUS_SPACE_MAXADDR,		/* highaddr */
		    NULL, NULL,			/* filter, filterarg */
		    MSK_TX_RING_SZ,		/* maxsize */
		    1,				/* nsegments */
		    MSK_TX_RING_SZ,		/* maxsegsize */
		    0,				/* flags */
		    NULL, NULL,			/* lockfunc, lockarg */
		    &sc_if->msk_cdata.msk_tx_ring_tag);
	if (error != 0) {
		device_printf(sc_if->msk_if_dev,
		    "failed to create Tx ring DMA tag\n");
		goto fail;
	}

	/* Create tag for Rx ring. */
	error = bus_dma_tag_create(sc_if->msk_cdata.msk_parent_tag,/* parent */
		    MSK_RING_ALIGN, 0,		/* alignment, boundary */
		    BUS_SPACE_MAXADDR,		/* lowaddr */
		    BUS_SPACE_MAXADDR,		/* highaddr */
		    NULL, NULL,			/* filter, filterarg */
		    MSK_RX_RING_SZ,		/* maxsize */
		    1,				/* nsegments */
		    MSK_RX_RING_SZ,		/* maxsegsize */
		    0,				/* flags */
		    NULL, NULL,			/* lockfunc, lockarg */
		    &sc_if->msk_cdata.msk_rx_ring_tag);
	if (error != 0) {
		device_printf(sc_if->msk_if_dev,
		    "failed to create Rx ring DMA tag\n");
		goto fail;
	}

	/* Create tag for Tx buffers. */
	error = bus_dma_tag_create(sc_if->msk_cdata.msk_parent_tag,/* parent */
		    1, 0,			/* alignment, boundary */
		    BUS_SPACE_MAXADDR,		/* lowaddr */
		    BUS_SPACE_MAXADDR,		/* highaddr */
		    NULL, NULL,			/* filter, filterarg */
		    MSK_TSO_MAXSIZE,		/* maxsize */
		    MSK_MAXTXSEGS,		/* nsegments */
		    MSK_TSO_MAXSGSIZE,		/* maxsegsize */
		    0,				/* flags */
		    NULL, NULL,			/* lockfunc, lockarg */
		    &sc_if->msk_cdata.msk_tx_tag);
	if (error != 0) {
		device_printf(sc_if->msk_if_dev,
		    "failed to create Tx DMA tag\n");
		goto fail;
	}

	rxalign = 1;
	/*
	 * Workaround hardware hang which seems to happen when Rx buffer
	 * is not aligned on multiple of FIFO word(8 bytes).
	 */
	if ((sc_if->msk_flags & MSK_FLAG_RAMBUF) != 0)
		rxalign = MSK_RX_BUF_ALIGN;
	/* Create tag for Rx buffers. */
	error = bus_dma_tag_create(sc_if->msk_cdata.msk_parent_tag,/* parent */
		    rxalign, 0,			/* alignment, boundary */
		    BUS_SPACE_MAXADDR,		/* lowaddr */
		    BUS_SPACE_MAXADDR,		/* highaddr */
		    NULL, NULL,			/* filter, filterarg */
		    MCLBYTES,			/* maxsize */
		    1,				/* nsegments */
		    MCLBYTES,			/* maxsegsize */
		    0,				/* flags */
		    NULL, NULL,			/* lockfunc, lockarg */
		    &sc_if->msk_cdata.msk_rx_tag);
	if (error != 0) {
		device_printf(sc_if->msk_if_dev,
		    "failed to create Rx DMA tag\n");
		goto fail;
	}

	/* Allocate DMA'able memory and load the DMA map for Tx ring. */
	error = bus_dmamem_alloc(sc_if->msk_cdata.msk_tx_ring_tag,
	    (void **)&sc_if->msk_rdata.msk_tx_ring, BUS_DMA_WAITOK |
	    BUS_DMA_COHERENT | BUS_DMA_ZERO, &sc_if->msk_cdata.msk_tx_ring_map);
	if (error != 0) {
		device_printf(sc_if->msk_if_dev,
		    "failed to allocate DMA'able memory for Tx ring\n");
		goto fail;
	}

	ctx.msk_busaddr = 0;
	error = bus_dmamap_load(sc_if->msk_cdata.msk_tx_ring_tag,
	    sc_if->msk_cdata.msk_tx_ring_map, sc_if->msk_rdata.msk_tx_ring,
	    MSK_TX_RING_SZ, msk_dmamap_cb, &ctx, BUS_DMA_NOWAIT);
	if (error != 0) {
		device_printf(sc_if->msk_if_dev,
		    "failed to load DMA'able memory for Tx ring\n");
		goto fail;
	}
	sc_if->msk_rdata.msk_tx_ring_paddr = ctx.msk_busaddr;

	/* Allocate DMA'able memory and load the DMA map for Rx ring. */
	error = bus_dmamem_alloc(sc_if->msk_cdata.msk_rx_ring_tag,
	    (void **)&sc_if->msk_rdata.msk_rx_ring, BUS_DMA_WAITOK |
	    BUS_DMA_COHERENT | BUS_DMA_ZERO, &sc_if->msk_cdata.msk_rx_ring_map);
	if (error != 0) {
		device_printf(sc_if->msk_if_dev,
		    "failed to allocate DMA'able memory for Rx ring\n");
		goto fail;
	}

	ctx.msk_busaddr = 0;
	error = bus_dmamap_load(sc_if->msk_cdata.msk_rx_ring_tag,
	    sc_if->msk_cdata.msk_rx_ring_map, sc_if->msk_rdata.msk_rx_ring,
	    MSK_RX_RING_SZ, msk_dmamap_cb, &ctx, BUS_DMA_NOWAIT);
	if (error != 0) {
		device_printf(sc_if->msk_if_dev,
		    "failed to load DMA'able memory for Rx ring\n");
		goto fail;
	}
	sc_if->msk_rdata.msk_rx_ring_paddr = ctx.msk_busaddr;

	/* Create DMA maps for Tx buffers. */
	for (i = 0; i < MSK_TX_RING_CNT; i++) {
		txd = &sc_if->msk_cdata.msk_txdesc[i];
		txd->tx_m = NULL;
		txd->tx_dmamap = NULL;
		error = bus_dmamap_create(sc_if->msk_cdata.msk_tx_tag, 0,
		    &txd->tx_dmamap);
		if (error != 0) {
			device_printf(sc_if->msk_if_dev,
			    "failed to create Tx dmamap\n");
			goto fail;
		}
	}
	/* Create DMA maps for Rx buffers. */
	if ((error = bus_dmamap_create(sc_if->msk_cdata.msk_rx_tag, 0,
	    &sc_if->msk_cdata.msk_rx_sparemap)) != 0) {
		device_printf(sc_if->msk_if_dev,
		    "failed to create spare Rx dmamap\n");
		goto fail;
	}
	for (i = 0; i < MSK_RX_RING_CNT; i++) {
		rxd = &sc_if->msk_cdata.msk_rxdesc[i];
		rxd->rx_m = NULL;
		rxd->rx_dmamap = NULL;
		error = bus_dmamap_create(sc_if->msk_cdata.msk_rx_tag, 0,
		    &rxd->rx_dmamap);
		if (error != 0) {
			device_printf(sc_if->msk_if_dev,
			    "failed to create Rx dmamap\n");
			goto fail;
		}
	}

fail:
	return (error);
}