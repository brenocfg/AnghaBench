#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vte_txdesc {int /*<<< orphan*/ * tx_dmamap; int /*<<< orphan*/ * tx_m; } ;
struct TYPE_2__ {scalar_t__ vte_tx_ring_paddr; scalar_t__ vte_rx_ring_paddr; int /*<<< orphan*/  vte_rx_tag; struct vte_rxdesc* vte_rxdesc; int /*<<< orphan*/ * vte_rx_sparemap; int /*<<< orphan*/  vte_tx_tag; struct vte_txdesc* vte_txdesc; int /*<<< orphan*/  vte_buffer_tag; int /*<<< orphan*/  vte_rx_ring; int /*<<< orphan*/  vte_rx_ring_map; int /*<<< orphan*/  vte_rx_ring_tag; int /*<<< orphan*/  vte_tx_ring; int /*<<< orphan*/  vte_tx_ring_map; int /*<<< orphan*/  vte_tx_ring_tag; int /*<<< orphan*/  vte_parent_tag; } ;
struct vte_softc {int /*<<< orphan*/  vte_dev; TYPE_1__ vte_cdata; } ;
struct vte_rxdesc {int /*<<< orphan*/ * rx_dmamap; int /*<<< orphan*/ * rx_m; } ;
struct vte_dmamap_arg {scalar_t__ vte_busaddr; } ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int VTE_RX_BUF_ALIGN ; 
 int VTE_RX_RING_ALIGN ; 
 int VTE_RX_RING_CNT ; 
 int /*<<< orphan*/  VTE_RX_RING_SZ ; 
 int VTE_TX_RING_ALIGN ; 
 int VTE_TX_RING_CNT ; 
 int /*<<< orphan*/  VTE_TX_RING_SZ ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vte_dmamap_arg*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vte_dmamap_cb ; 

__attribute__((used)) static int
vte_dma_alloc(struct vte_softc *sc)
{
	struct vte_txdesc *txd;
	struct vte_rxdesc *rxd;
	struct vte_dmamap_arg ctx;
	int error, i;

	/* Create parent DMA tag. */
	error = bus_dma_tag_create(
	    bus_get_dma_tag(sc->vte_dev), /* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
	    0,				/* nsegments */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->vte_cdata.vte_parent_tag);
	if (error != 0) {
		device_printf(sc->vte_dev,
		    "could not create parent DMA tag.\n");
		goto fail;
	}

	/* Create DMA tag for TX descriptor ring. */
	error = bus_dma_tag_create(
	    sc->vte_cdata.vte_parent_tag, /* parent */
	    VTE_TX_RING_ALIGN, 0,	/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    VTE_TX_RING_SZ,		/* maxsize */
	    1,				/* nsegments */
	    VTE_TX_RING_SZ,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->vte_cdata.vte_tx_ring_tag);
	if (error != 0) {
		device_printf(sc->vte_dev,
		    "could not create TX ring DMA tag.\n");
		goto fail;
	}

	/* Create DMA tag for RX free descriptor ring. */
	error = bus_dma_tag_create(
	    sc->vte_cdata.vte_parent_tag, /* parent */
	    VTE_RX_RING_ALIGN, 0,	/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    VTE_RX_RING_SZ,		/* maxsize */
	    1,				/* nsegments */
	    VTE_RX_RING_SZ,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->vte_cdata.vte_rx_ring_tag);
	if (error != 0) {
		device_printf(sc->vte_dev,
		    "could not create RX ring DMA tag.\n");
		goto fail;
	}

	/* Allocate DMA'able memory and load the DMA map for TX ring. */
	error = bus_dmamem_alloc(sc->vte_cdata.vte_tx_ring_tag,
	    (void **)&sc->vte_cdata.vte_tx_ring,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &sc->vte_cdata.vte_tx_ring_map);
	if (error != 0) {
		device_printf(sc->vte_dev,
		    "could not allocate DMA'able memory for TX ring.\n");
		goto fail;
	}
	ctx.vte_busaddr = 0;
	error = bus_dmamap_load(sc->vte_cdata.vte_tx_ring_tag,
	    sc->vte_cdata.vte_tx_ring_map, sc->vte_cdata.vte_tx_ring,
	    VTE_TX_RING_SZ, vte_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.vte_busaddr == 0) {
		device_printf(sc->vte_dev,
		    "could not load DMA'able memory for TX ring.\n");
		goto fail;
	}
	sc->vte_cdata.vte_tx_ring_paddr = ctx.vte_busaddr;

	/* Allocate DMA'able memory and load the DMA map for RX ring. */
	error = bus_dmamem_alloc(sc->vte_cdata.vte_rx_ring_tag,
	    (void **)&sc->vte_cdata.vte_rx_ring,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &sc->vte_cdata.vte_rx_ring_map);
	if (error != 0) {
		device_printf(sc->vte_dev,
		    "could not allocate DMA'able memory for RX ring.\n");
		goto fail;
	}
	ctx.vte_busaddr = 0;
	error = bus_dmamap_load(sc->vte_cdata.vte_rx_ring_tag,
	    sc->vte_cdata.vte_rx_ring_map, sc->vte_cdata.vte_rx_ring,
	    VTE_RX_RING_SZ, vte_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.vte_busaddr == 0) {
		device_printf(sc->vte_dev,
		    "could not load DMA'able memory for RX ring.\n");
		goto fail;
	}
	sc->vte_cdata.vte_rx_ring_paddr = ctx.vte_busaddr;

	/* Create TX buffer parent tag. */
	error = bus_dma_tag_create(
	    bus_get_dma_tag(sc->vte_dev), /* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
	    0,				/* nsegments */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->vte_cdata.vte_buffer_tag);
	if (error != 0) {
		device_printf(sc->vte_dev,
		    "could not create parent buffer DMA tag.\n");
		goto fail;
	}

	/* Create DMA tag for TX buffers. */
	error = bus_dma_tag_create(
	    sc->vte_cdata.vte_buffer_tag, /* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES,			/* maxsize */
	    1,				/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->vte_cdata.vte_tx_tag);
	if (error != 0) {
		device_printf(sc->vte_dev, "could not create TX DMA tag.\n");
		goto fail;
	}

	/* Create DMA tag for RX buffers. */
	error = bus_dma_tag_create(
	    sc->vte_cdata.vte_buffer_tag, /* parent */
	    VTE_RX_BUF_ALIGN, 0,	/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES,			/* maxsize */
	    1,				/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->vte_cdata.vte_rx_tag);
	if (error != 0) {
		device_printf(sc->vte_dev, "could not create RX DMA tag.\n");
		goto fail;
	}
	/* Create DMA maps for TX buffers. */
	for (i = 0; i < VTE_TX_RING_CNT; i++) {
		txd = &sc->vte_cdata.vte_txdesc[i];
		txd->tx_m = NULL;
		txd->tx_dmamap = NULL;
		error = bus_dmamap_create(sc->vte_cdata.vte_tx_tag, 0,
		    &txd->tx_dmamap);
		if (error != 0) {
			device_printf(sc->vte_dev,
			    "could not create TX dmamap.\n");
			goto fail;
		}
	}
	/* Create DMA maps for RX buffers. */
	if ((error = bus_dmamap_create(sc->vte_cdata.vte_rx_tag, 0,
	    &sc->vte_cdata.vte_rx_sparemap)) != 0) {
		device_printf(sc->vte_dev,
		    "could not create spare RX dmamap.\n");
		goto fail;
	}
	for (i = 0; i < VTE_RX_RING_CNT; i++) {
		rxd = &sc->vte_cdata.vte_rxdesc[i];
		rxd->rx_m = NULL;
		rxd->rx_dmamap = NULL;
		error = bus_dmamap_create(sc->vte_cdata.vte_rx_tag, 0,
		    &rxd->rx_dmamap);
		if (error != 0) {
			device_printf(sc->vte_dev,
			    "could not create RX dmamap.\n");
			goto fail;
		}
	}

fail:
	return (error);
}