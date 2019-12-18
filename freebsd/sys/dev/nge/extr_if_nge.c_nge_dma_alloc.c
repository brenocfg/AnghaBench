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
struct nge_txdesc {int /*<<< orphan*/ * tx_dmamap; int /*<<< orphan*/ * tx_m; } ;
struct TYPE_3__ {int /*<<< orphan*/  nge_rx_tag; struct nge_rxdesc* nge_rxdesc; int /*<<< orphan*/ * nge_rx_sparemap; int /*<<< orphan*/  nge_tx_tag; struct nge_txdesc* nge_txdesc; int /*<<< orphan*/  nge_rx_ring_map; int /*<<< orphan*/  nge_rx_ring_tag; int /*<<< orphan*/  nge_tx_ring_map; int /*<<< orphan*/  nge_tx_ring_tag; int /*<<< orphan*/  nge_parent_tag; } ;
struct TYPE_4__ {scalar_t__ nge_tx_ring_paddr; scalar_t__ nge_rx_ring_paddr; int /*<<< orphan*/  nge_rx_ring; int /*<<< orphan*/  nge_tx_ring; } ;
struct nge_softc {int /*<<< orphan*/  nge_dev; TYPE_1__ nge_cdata; TYPE_2__ nge_rdata; } ;
struct nge_rxdesc {int /*<<< orphan*/ * rx_dmamap; int /*<<< orphan*/ * rx_m; } ;
struct nge_dmamap_arg {scalar_t__ nge_busaddr; } ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int MCLBYTES ; 
 int NGE_MAXTXSEGS ; 
 int NGE_RING_ALIGN ; 
 int NGE_RX_ALIGN ; 
 int NGE_RX_RING_CNT ; 
 int NGE_RX_RING_SIZE ; 
 int NGE_TX_RING_CNT ; 
 int NGE_TX_RING_SIZE ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct nge_dmamap_arg*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nge_dmamap_cb ; 

__attribute__((used)) static int
nge_dma_alloc(struct nge_softc *sc)
{
	struct nge_dmamap_arg ctx;
	struct nge_txdesc *txd;
	struct nge_rxdesc *rxd;
	int error, i;

	/* Create parent DMA tag. */
	error = bus_dma_tag_create(
	    bus_get_dma_tag(sc->nge_dev),	/* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
	    0,				/* nsegments */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->nge_cdata.nge_parent_tag);
	if (error != 0) {
		device_printf(sc->nge_dev, "failed to create parent DMA tag\n");
		goto fail;
	}
	/* Create tag for Tx ring. */
	error = bus_dma_tag_create(sc->nge_cdata.nge_parent_tag,/* parent */
	    NGE_RING_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    NGE_TX_RING_SIZE,		/* maxsize */
	    1,				/* nsegments */
	    NGE_TX_RING_SIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->nge_cdata.nge_tx_ring_tag);
	if (error != 0) {
		device_printf(sc->nge_dev, "failed to create Tx ring DMA tag\n");
		goto fail;
	}

	/* Create tag for Rx ring. */
	error = bus_dma_tag_create(sc->nge_cdata.nge_parent_tag,/* parent */
	    NGE_RING_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    NGE_RX_RING_SIZE,		/* maxsize */
	    1,				/* nsegments */
	    NGE_RX_RING_SIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->nge_cdata.nge_rx_ring_tag);
	if (error != 0) {
		device_printf(sc->nge_dev,
		    "failed to create Rx ring DMA tag\n");
		goto fail;
	}

	/* Create tag for Tx buffers. */
	error = bus_dma_tag_create(sc->nge_cdata.nge_parent_tag,/* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES * NGE_MAXTXSEGS,	/* maxsize */
	    NGE_MAXTXSEGS,		/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->nge_cdata.nge_tx_tag);
	if (error != 0) {
		device_printf(sc->nge_dev, "failed to create Tx DMA tag\n");
		goto fail;
	}

	/* Create tag for Rx buffers. */
	error = bus_dma_tag_create(sc->nge_cdata.nge_parent_tag,/* parent */
	    NGE_RX_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES,			/* maxsize */
	    1,				/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->nge_cdata.nge_rx_tag);
	if (error != 0) {
		device_printf(sc->nge_dev, "failed to create Rx DMA tag\n");
		goto fail;
	}

	/* Allocate DMA'able memory and load the DMA map for Tx ring. */
	error = bus_dmamem_alloc(sc->nge_cdata.nge_tx_ring_tag,
	    (void **)&sc->nge_rdata.nge_tx_ring, BUS_DMA_WAITOK |
	    BUS_DMA_COHERENT | BUS_DMA_ZERO, &sc->nge_cdata.nge_tx_ring_map);
	if (error != 0) {
		device_printf(sc->nge_dev,
		    "failed to allocate DMA'able memory for Tx ring\n");
		goto fail;
	}

	ctx.nge_busaddr = 0;
	error = bus_dmamap_load(sc->nge_cdata.nge_tx_ring_tag,
	    sc->nge_cdata.nge_tx_ring_map, sc->nge_rdata.nge_tx_ring,
	    NGE_TX_RING_SIZE, nge_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.nge_busaddr == 0) {
		device_printf(sc->nge_dev,
		    "failed to load DMA'able memory for Tx ring\n");
		goto fail;
	}
	sc->nge_rdata.nge_tx_ring_paddr = ctx.nge_busaddr;

	/* Allocate DMA'able memory and load the DMA map for Rx ring. */
	error = bus_dmamem_alloc(sc->nge_cdata.nge_rx_ring_tag,
	    (void **)&sc->nge_rdata.nge_rx_ring, BUS_DMA_WAITOK |
	    BUS_DMA_COHERENT | BUS_DMA_ZERO, &sc->nge_cdata.nge_rx_ring_map);
	if (error != 0) {
		device_printf(sc->nge_dev,
		    "failed to allocate DMA'able memory for Rx ring\n");
		goto fail;
	}

	ctx.nge_busaddr = 0;
	error = bus_dmamap_load(sc->nge_cdata.nge_rx_ring_tag,
	    sc->nge_cdata.nge_rx_ring_map, sc->nge_rdata.nge_rx_ring,
	    NGE_RX_RING_SIZE, nge_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.nge_busaddr == 0) {
		device_printf(sc->nge_dev,
		    "failed to load DMA'able memory for Rx ring\n");
		goto fail;
	}
	sc->nge_rdata.nge_rx_ring_paddr = ctx.nge_busaddr;

	/* Create DMA maps for Tx buffers. */
	for (i = 0; i < NGE_TX_RING_CNT; i++) {
		txd = &sc->nge_cdata.nge_txdesc[i];
		txd->tx_m = NULL;
		txd->tx_dmamap = NULL;
		error = bus_dmamap_create(sc->nge_cdata.nge_tx_tag, 0,
		    &txd->tx_dmamap);
		if (error != 0) {
			device_printf(sc->nge_dev,
			    "failed to create Tx dmamap\n");
			goto fail;
		}
	}
	/* Create DMA maps for Rx buffers. */
	if ((error = bus_dmamap_create(sc->nge_cdata.nge_rx_tag, 0,
	    &sc->nge_cdata.nge_rx_sparemap)) != 0) {
		device_printf(sc->nge_dev,
		    "failed to create spare Rx dmamap\n");
		goto fail;
	}
	for (i = 0; i < NGE_RX_RING_CNT; i++) {
		rxd = &sc->nge_cdata.nge_rxdesc[i];
		rxd->rx_m = NULL;
		rxd->rx_dmamap = NULL;
		error = bus_dmamap_create(sc->nge_cdata.nge_rx_tag, 0,
		    &rxd->rx_dmamap);
		if (error != 0) {
			device_printf(sc->nge_dev,
			    "failed to create Rx dmamap\n");
			goto fail;
		}
	}

fail:
	return (error);
}