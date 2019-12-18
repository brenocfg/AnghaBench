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
typedef  int /*<<< orphan*/  uint32_t ;
struct are_txdesc {int /*<<< orphan*/ * tx_dmamap; int /*<<< orphan*/ * tx_m; } ;
struct TYPE_3__ {int /*<<< orphan*/  are_rx_tag; struct are_rxdesc* are_rxdesc; int /*<<< orphan*/ * are_rx_sparemap; int /*<<< orphan*/  are_tx_tag; struct are_txdesc* are_txdesc; int /*<<< orphan*/  are_rx_ring_map; int /*<<< orphan*/  are_rx_ring_tag; int /*<<< orphan*/  are_tx_ring_map; int /*<<< orphan*/  are_tx_ring_tag; int /*<<< orphan*/  are_parent_tag; } ;
struct TYPE_4__ {scalar_t__ are_tx_ring_paddr; scalar_t__ are_rx_ring_paddr; int /*<<< orphan*/  are_rx_ring; int /*<<< orphan*/  are_tx_ring; } ;
struct are_softc {int /*<<< orphan*/  are_dev; TYPE_1__ are_cdata; TYPE_2__ are_rdata; } ;
struct are_rxdesc {int /*<<< orphan*/ * rx_dmamap; int /*<<< orphan*/ * rx_m; } ;
struct are_dmamap_arg {scalar_t__ are_busaddr; } ;

/* Variables and functions */
 int ARE_MAXFRAGS ; 
 int ARE_RING_ALIGN ; 
 int ARE_RX_ALIGN ; 
 int ARE_RX_RING_CNT ; 
 int ARE_RX_RING_SIZE ; 
 int ARE_TX_RING_CNT ; 
 int ARE_TX_RING_SIZE ; 
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int MCLBYTES ; 
 int /*<<< orphan*/  are_dmamap_cb ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct are_dmamap_arg*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
are_dma_alloc(struct are_softc *sc)
{
	struct are_dmamap_arg	ctx;
	struct are_txdesc	*txd;
	struct are_rxdesc	*rxd;
	int			error, i;

	/* Create parent DMA tag. */
	error = bus_dma_tag_create(
	    bus_get_dma_tag(sc->are_dev),	/* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
	    0,				/* nsegments */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->are_cdata.are_parent_tag);
	if (error != 0) {
		device_printf(sc->are_dev, "failed to create parent DMA tag\n");
		goto fail;
	}
	/* Create tag for Tx ring. */
	error = bus_dma_tag_create(
	    sc->are_cdata.are_parent_tag,	/* parent */
	    ARE_RING_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    ARE_TX_RING_SIZE,		/* maxsize */
	    1,				/* nsegments */
	    ARE_TX_RING_SIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->are_cdata.are_tx_ring_tag);
	if (error != 0) {
		device_printf(sc->are_dev, "failed to create Tx ring DMA tag\n");
		goto fail;
	}

	/* Create tag for Rx ring. */
	error = bus_dma_tag_create(
	    sc->are_cdata.are_parent_tag,	/* parent */
	    ARE_RING_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    ARE_RX_RING_SIZE,		/* maxsize */
	    1,				/* nsegments */
	    ARE_RX_RING_SIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->are_cdata.are_rx_ring_tag);
	if (error != 0) {
		device_printf(sc->are_dev, "failed to create Rx ring DMA tag\n");
		goto fail;
	}

	/* Create tag for Tx buffers. */
	error = bus_dma_tag_create(
	    sc->are_cdata.are_parent_tag,	/* parent */
	    sizeof(uint32_t), 0,	/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES * ARE_MAXFRAGS,	/* maxsize */
	    ARE_MAXFRAGS,		/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->are_cdata.are_tx_tag);
	if (error != 0) {
		device_printf(sc->are_dev, "failed to create Tx DMA tag\n");
		goto fail;
	}

	/* Create tag for Rx buffers. */
	error = bus_dma_tag_create(
	    sc->are_cdata.are_parent_tag,	/* parent */
	    ARE_RX_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES,			/* maxsize */
	    1,				/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->are_cdata.are_rx_tag);
	if (error != 0) {
		device_printf(sc->are_dev, "failed to create Rx DMA tag\n");
		goto fail;
	}

	/* Allocate DMA'able memory and load the DMA map for Tx ring. */
	error = bus_dmamem_alloc(sc->are_cdata.are_tx_ring_tag,
	    (void **)&sc->are_rdata.are_tx_ring, BUS_DMA_WAITOK |
	    BUS_DMA_COHERENT | BUS_DMA_ZERO, &sc->are_cdata.are_tx_ring_map);
	if (error != 0) {
		device_printf(sc->are_dev,
		    "failed to allocate DMA'able memory for Tx ring\n");
		goto fail;
	}

	ctx.are_busaddr = 0;
	error = bus_dmamap_load(sc->are_cdata.are_tx_ring_tag,
	    sc->are_cdata.are_tx_ring_map, sc->are_rdata.are_tx_ring,
	    ARE_TX_RING_SIZE, are_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.are_busaddr == 0) {
		device_printf(sc->are_dev,
		    "failed to load DMA'able memory for Tx ring\n");
		goto fail;
	}
	sc->are_rdata.are_tx_ring_paddr = ctx.are_busaddr;

	/* Allocate DMA'able memory and load the DMA map for Rx ring. */
	error = bus_dmamem_alloc(sc->are_cdata.are_rx_ring_tag,
	    (void **)&sc->are_rdata.are_rx_ring, BUS_DMA_WAITOK |
	    BUS_DMA_COHERENT | BUS_DMA_ZERO, &sc->are_cdata.are_rx_ring_map);
	if (error != 0) {
		device_printf(sc->are_dev,
		    "failed to allocate DMA'able memory for Rx ring\n");
		goto fail;
	}

	ctx.are_busaddr = 0;
	error = bus_dmamap_load(sc->are_cdata.are_rx_ring_tag,
	    sc->are_cdata.are_rx_ring_map, sc->are_rdata.are_rx_ring,
	    ARE_RX_RING_SIZE, are_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.are_busaddr == 0) {
		device_printf(sc->are_dev,
		    "failed to load DMA'able memory for Rx ring\n");
		goto fail;
	}
	sc->are_rdata.are_rx_ring_paddr = ctx.are_busaddr;

	/* Create DMA maps for Tx buffers. */
	for (i = 0; i < ARE_TX_RING_CNT; i++) {
		txd = &sc->are_cdata.are_txdesc[i];
		txd->tx_m = NULL;
		txd->tx_dmamap = NULL;
		error = bus_dmamap_create(sc->are_cdata.are_tx_tag, 0,
		    &txd->tx_dmamap);
		if (error != 0) {
			device_printf(sc->are_dev,
			    "failed to create Tx dmamap\n");
			goto fail;
		}
	}
	/* Create DMA maps for Rx buffers. */
	if ((error = bus_dmamap_create(sc->are_cdata.are_rx_tag, 0,
	    &sc->are_cdata.are_rx_sparemap)) != 0) {
		device_printf(sc->are_dev,
		    "failed to create spare Rx dmamap\n");
		goto fail;
	}
	for (i = 0; i < ARE_RX_RING_CNT; i++) {
		rxd = &sc->are_cdata.are_rxdesc[i];
		rxd->rx_m = NULL;
		rxd->rx_dmamap = NULL;
		error = bus_dmamap_create(sc->are_cdata.are_rx_tag, 0,
		    &rxd->rx_dmamap);
		if (error != 0) {
			device_printf(sc->are_dev,
			    "failed to create Rx dmamap\n");
			goto fail;
		}
	}

fail:
	return (error);
}