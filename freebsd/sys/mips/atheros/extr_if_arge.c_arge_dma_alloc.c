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
struct arge_txdesc {int /*<<< orphan*/ * tx_dmamap; int /*<<< orphan*/ * tx_m; } ;
struct TYPE_4__ {int /*<<< orphan*/  arge_rx_tag; struct arge_rxdesc* arge_rxdesc; int /*<<< orphan*/ * arge_rx_sparemap; int /*<<< orphan*/  arge_tx_tag; struct arge_txdesc* arge_txdesc; int /*<<< orphan*/  arge_rx_ring_map; int /*<<< orphan*/  arge_rx_ring_tag; int /*<<< orphan*/  arge_tx_ring_map; int /*<<< orphan*/  arge_tx_ring_tag; int /*<<< orphan*/  arge_parent_tag; } ;
struct TYPE_3__ {scalar_t__ arge_tx_ring_paddr; scalar_t__ arge_rx_ring_paddr; int /*<<< orphan*/  arge_rx_ring; int /*<<< orphan*/  arge_tx_ring; } ;
struct arge_softc {int arge_hw_flags; int /*<<< orphan*/  arge_dev; TYPE_2__ arge_cdata; TYPE_1__ arge_rdata; } ;
struct arge_rxdesc {int /*<<< orphan*/ * rx_dmamap; int /*<<< orphan*/ * rx_m; } ;
struct arge_dmamap_arg {scalar_t__ arge_busaddr; } ;

/* Variables and functions */
 int ARGE_HW_FLG_RX_DESC_ALIGN_1BYTE ; 
 int ARGE_HW_FLG_TX_DESC_ALIGN_1BYTE ; 
 int ARGE_MAXFRAGS ; 
 int ARGE_RING_ALIGN ; 
 int ARGE_RX_DMA_SIZE ; 
 int ARGE_RX_RING_COUNT ; 
 int ARGE_TX_DMA_SIZE ; 
 int ARGE_TX_RING_COUNT ; 
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int MCLBYTES ; 
 int /*<<< orphan*/  arge_dmamap_cb ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct arge_dmamap_arg*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
arge_dma_alloc(struct arge_softc *sc)
{
	struct arge_dmamap_arg	ctx;
	struct arge_txdesc	*txd;
	struct arge_rxdesc	*rxd;
	int			error, i;
	int			arge_tx_align, arge_rx_align;

	/* Assume 4 byte alignment by default */
	arge_tx_align = 4;
	arge_rx_align = 4;

	if (sc->arge_hw_flags & ARGE_HW_FLG_TX_DESC_ALIGN_1BYTE)
		arge_tx_align = 1;
	if (sc->arge_hw_flags & ARGE_HW_FLG_RX_DESC_ALIGN_1BYTE)
		arge_rx_align = 1;

	/* Create parent DMA tag. */
	error = bus_dma_tag_create(
	    bus_get_dma_tag(sc->arge_dev),	/* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
	    0,				/* nsegments */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->arge_cdata.arge_parent_tag);
	if (error != 0) {
		device_printf(sc->arge_dev,
		    "failed to create parent DMA tag\n");
		goto fail;
	}
	/* Create tag for Tx ring. */
	error = bus_dma_tag_create(
	    sc->arge_cdata.arge_parent_tag,	/* parent */
	    ARGE_RING_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    ARGE_TX_DMA_SIZE,		/* maxsize */
	    1,				/* nsegments */
	    ARGE_TX_DMA_SIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->arge_cdata.arge_tx_ring_tag);
	if (error != 0) {
		device_printf(sc->arge_dev,
		    "failed to create Tx ring DMA tag\n");
		goto fail;
	}

	/* Create tag for Rx ring. */
	error = bus_dma_tag_create(
	    sc->arge_cdata.arge_parent_tag,	/* parent */
	    ARGE_RING_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    ARGE_RX_DMA_SIZE,		/* maxsize */
	    1,				/* nsegments */
	    ARGE_RX_DMA_SIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->arge_cdata.arge_rx_ring_tag);
	if (error != 0) {
		device_printf(sc->arge_dev,
		    "failed to create Rx ring DMA tag\n");
		goto fail;
	}

	/* Create tag for Tx buffers. */
	error = bus_dma_tag_create(
	    sc->arge_cdata.arge_parent_tag,	/* parent */
	    arge_tx_align, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES * ARGE_MAXFRAGS,	/* maxsize */
	    ARGE_MAXFRAGS,		/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->arge_cdata.arge_tx_tag);
	if (error != 0) {
		device_printf(sc->arge_dev, "failed to create Tx DMA tag\n");
		goto fail;
	}

	/* Create tag for Rx buffers. */
	error = bus_dma_tag_create(
	    sc->arge_cdata.arge_parent_tag,	/* parent */
	    arge_rx_align, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES,			/* maxsize */
	    ARGE_MAXFRAGS,		/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->arge_cdata.arge_rx_tag);
	if (error != 0) {
		device_printf(sc->arge_dev, "failed to create Rx DMA tag\n");
		goto fail;
	}

	/* Allocate DMA'able memory and load the DMA map for Tx ring. */
	error = bus_dmamem_alloc(sc->arge_cdata.arge_tx_ring_tag,
	    (void **)&sc->arge_rdata.arge_tx_ring, BUS_DMA_WAITOK |
	    BUS_DMA_COHERENT | BUS_DMA_ZERO,
	    &sc->arge_cdata.arge_tx_ring_map);
	if (error != 0) {
		device_printf(sc->arge_dev,
		    "failed to allocate DMA'able memory for Tx ring\n");
		goto fail;
	}

	ctx.arge_busaddr = 0;
	error = bus_dmamap_load(sc->arge_cdata.arge_tx_ring_tag,
	    sc->arge_cdata.arge_tx_ring_map, sc->arge_rdata.arge_tx_ring,
	    ARGE_TX_DMA_SIZE, arge_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.arge_busaddr == 0) {
		device_printf(sc->arge_dev,
		    "failed to load DMA'able memory for Tx ring\n");
		goto fail;
	}
	sc->arge_rdata.arge_tx_ring_paddr = ctx.arge_busaddr;

	/* Allocate DMA'able memory and load the DMA map for Rx ring. */
	error = bus_dmamem_alloc(sc->arge_cdata.arge_rx_ring_tag,
	    (void **)&sc->arge_rdata.arge_rx_ring, BUS_DMA_WAITOK |
	    BUS_DMA_COHERENT | BUS_DMA_ZERO,
	    &sc->arge_cdata.arge_rx_ring_map);
	if (error != 0) {
		device_printf(sc->arge_dev,
		    "failed to allocate DMA'able memory for Rx ring\n");
		goto fail;
	}

	ctx.arge_busaddr = 0;
	error = bus_dmamap_load(sc->arge_cdata.arge_rx_ring_tag,
	    sc->arge_cdata.arge_rx_ring_map, sc->arge_rdata.arge_rx_ring,
	    ARGE_RX_DMA_SIZE, arge_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.arge_busaddr == 0) {
		device_printf(sc->arge_dev,
		    "failed to load DMA'able memory for Rx ring\n");
		goto fail;
	}
	sc->arge_rdata.arge_rx_ring_paddr = ctx.arge_busaddr;

	/* Create DMA maps for Tx buffers. */
	for (i = 0; i < ARGE_TX_RING_COUNT; i++) {
		txd = &sc->arge_cdata.arge_txdesc[i];
		txd->tx_m = NULL;
		txd->tx_dmamap = NULL;
		error = bus_dmamap_create(sc->arge_cdata.arge_tx_tag, 0,
		    &txd->tx_dmamap);
		if (error != 0) {
			device_printf(sc->arge_dev,
			    "failed to create Tx dmamap\n");
			goto fail;
		}
	}
	/* Create DMA maps for Rx buffers. */
	if ((error = bus_dmamap_create(sc->arge_cdata.arge_rx_tag, 0,
	    &sc->arge_cdata.arge_rx_sparemap)) != 0) {
		device_printf(sc->arge_dev,
		    "failed to create spare Rx dmamap\n");
		goto fail;
	}
	for (i = 0; i < ARGE_RX_RING_COUNT; i++) {
		rxd = &sc->arge_cdata.arge_rxdesc[i];
		rxd->rx_m = NULL;
		rxd->rx_dmamap = NULL;
		error = bus_dmamap_create(sc->arge_cdata.arge_rx_tag, 0,
		    &rxd->rx_dmamap);
		if (error != 0) {
			device_printf(sc->arge_dev,
			    "failed to create Rx dmamap\n");
			goto fail;
		}
	}

fail:
	return (error);
}