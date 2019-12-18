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
struct vr_txdesc {int /*<<< orphan*/ * tx_dmamap; int /*<<< orphan*/ * tx_m; } ;
struct TYPE_4__ {int /*<<< orphan*/  vr_rx_tag; struct vr_rxdesc* vr_rxdesc; int /*<<< orphan*/ * vr_rx_sparemap; int /*<<< orphan*/  vr_tx_tag; struct vr_txdesc* vr_txdesc; int /*<<< orphan*/  vr_rx_ring_map; int /*<<< orphan*/  vr_rx_ring_tag; int /*<<< orphan*/  vr_tx_ring_map; int /*<<< orphan*/  vr_tx_ring_tag; int /*<<< orphan*/  vr_parent_tag; } ;
struct TYPE_3__ {scalar_t__ vr_tx_ring_paddr; scalar_t__ vr_rx_ring_paddr; int /*<<< orphan*/  vr_rx_ring; int /*<<< orphan*/  vr_tx_ring; } ;
struct vr_softc {int vr_quirks; int /*<<< orphan*/  vr_dev; TYPE_2__ vr_cdata; TYPE_1__ vr_rdata; } ;
struct vr_rxdesc {int /*<<< orphan*/ * rx_dmamap; int /*<<< orphan*/ * rx_m; } ;
struct vr_dmamap_arg {scalar_t__ vr_busaddr; } ;
typedef  int bus_size_t ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int MCLBYTES ; 
 int VR_MAXFRAGS ; 
 int VR_Q_NEEDALIGN ; 
 int VR_RING_ALIGN ; 
 int VR_RX_ALIGN ; 
 int VR_RX_RING_CNT ; 
 int VR_RX_RING_SIZE ; 
 int VR_TX_RING_CNT ; 
 int VR_TX_RING_SIZE ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct vr_dmamap_arg*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vr_dmamap_cb ; 

__attribute__((used)) static int
vr_dma_alloc(struct vr_softc *sc)
{
	struct vr_dmamap_arg	ctx;
	struct vr_txdesc	*txd;
	struct vr_rxdesc	*rxd;
	bus_size_t		tx_alignment;
	int			error, i;

	/* Create parent DMA tag. */
	error = bus_dma_tag_create(
	    bus_get_dma_tag(sc->vr_dev),	/* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
	    0,				/* nsegments */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->vr_cdata.vr_parent_tag);
	if (error != 0) {
		device_printf(sc->vr_dev, "failed to create parent DMA tag\n");
		goto fail;
	}
	/* Create tag for Tx ring. */
	error = bus_dma_tag_create(
	    sc->vr_cdata.vr_parent_tag,	/* parent */
	    VR_RING_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    VR_TX_RING_SIZE,		/* maxsize */
	    1,				/* nsegments */
	    VR_TX_RING_SIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->vr_cdata.vr_tx_ring_tag);
	if (error != 0) {
		device_printf(sc->vr_dev, "failed to create Tx ring DMA tag\n");
		goto fail;
	}

	/* Create tag for Rx ring. */
	error = bus_dma_tag_create(
	    sc->vr_cdata.vr_parent_tag,	/* parent */
	    VR_RING_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    VR_RX_RING_SIZE,		/* maxsize */
	    1,				/* nsegments */
	    VR_RX_RING_SIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->vr_cdata.vr_rx_ring_tag);
	if (error != 0) {
		device_printf(sc->vr_dev, "failed to create Rx ring DMA tag\n");
		goto fail;
	}

	if ((sc->vr_quirks & VR_Q_NEEDALIGN) != 0)
		tx_alignment = sizeof(uint32_t);
	else
		tx_alignment = 1;
	/* Create tag for Tx buffers. */
	error = bus_dma_tag_create(
	    sc->vr_cdata.vr_parent_tag,	/* parent */
	    tx_alignment, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES * VR_MAXFRAGS,	/* maxsize */
	    VR_MAXFRAGS,		/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->vr_cdata.vr_tx_tag);
	if (error != 0) {
		device_printf(sc->vr_dev, "failed to create Tx DMA tag\n");
		goto fail;
	}

	/* Create tag for Rx buffers. */
	error = bus_dma_tag_create(
	    sc->vr_cdata.vr_parent_tag,	/* parent */
	    VR_RX_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES,			/* maxsize */
	    1,				/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->vr_cdata.vr_rx_tag);
	if (error != 0) {
		device_printf(sc->vr_dev, "failed to create Rx DMA tag\n");
		goto fail;
	}

	/* Allocate DMA'able memory and load the DMA map for Tx ring. */
	error = bus_dmamem_alloc(sc->vr_cdata.vr_tx_ring_tag,
	    (void **)&sc->vr_rdata.vr_tx_ring, BUS_DMA_WAITOK |
	    BUS_DMA_COHERENT | BUS_DMA_ZERO, &sc->vr_cdata.vr_tx_ring_map);
	if (error != 0) {
		device_printf(sc->vr_dev,
		    "failed to allocate DMA'able memory for Tx ring\n");
		goto fail;
	}

	ctx.vr_busaddr = 0;
	error = bus_dmamap_load(sc->vr_cdata.vr_tx_ring_tag,
	    sc->vr_cdata.vr_tx_ring_map, sc->vr_rdata.vr_tx_ring,
	    VR_TX_RING_SIZE, vr_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.vr_busaddr == 0) {
		device_printf(sc->vr_dev,
		    "failed to load DMA'able memory for Tx ring\n");
		goto fail;
	}
	sc->vr_rdata.vr_tx_ring_paddr = ctx.vr_busaddr;

	/* Allocate DMA'able memory and load the DMA map for Rx ring. */
	error = bus_dmamem_alloc(sc->vr_cdata.vr_rx_ring_tag,
	    (void **)&sc->vr_rdata.vr_rx_ring, BUS_DMA_WAITOK |
	    BUS_DMA_COHERENT | BUS_DMA_ZERO, &sc->vr_cdata.vr_rx_ring_map);
	if (error != 0) {
		device_printf(sc->vr_dev,
		    "failed to allocate DMA'able memory for Rx ring\n");
		goto fail;
	}

	ctx.vr_busaddr = 0;
	error = bus_dmamap_load(sc->vr_cdata.vr_rx_ring_tag,
	    sc->vr_cdata.vr_rx_ring_map, sc->vr_rdata.vr_rx_ring,
	    VR_RX_RING_SIZE, vr_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.vr_busaddr == 0) {
		device_printf(sc->vr_dev,
		    "failed to load DMA'able memory for Rx ring\n");
		goto fail;
	}
	sc->vr_rdata.vr_rx_ring_paddr = ctx.vr_busaddr;

	/* Create DMA maps for Tx buffers. */
	for (i = 0; i < VR_TX_RING_CNT; i++) {
		txd = &sc->vr_cdata.vr_txdesc[i];
		txd->tx_m = NULL;
		txd->tx_dmamap = NULL;
		error = bus_dmamap_create(sc->vr_cdata.vr_tx_tag, 0,
		    &txd->tx_dmamap);
		if (error != 0) {
			device_printf(sc->vr_dev,
			    "failed to create Tx dmamap\n");
			goto fail;
		}
	}
	/* Create DMA maps for Rx buffers. */
	if ((error = bus_dmamap_create(sc->vr_cdata.vr_rx_tag, 0,
	    &sc->vr_cdata.vr_rx_sparemap)) != 0) {
		device_printf(sc->vr_dev,
		    "failed to create spare Rx dmamap\n");
		goto fail;
	}
	for (i = 0; i < VR_RX_RING_CNT; i++) {
		rxd = &sc->vr_cdata.vr_rxdesc[i];
		rxd->rx_m = NULL;
		rxd->rx_dmamap = NULL;
		error = bus_dmamap_create(sc->vr_cdata.vr_rx_tag, 0,
		    &rxd->rx_dmamap);
		if (error != 0) {
			device_printf(sc->vr_dev,
			    "failed to create Rx dmamap\n");
			goto fail;
		}
	}

fail:
	return (error);
}