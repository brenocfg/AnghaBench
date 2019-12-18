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
struct fv_txdesc {int /*<<< orphan*/ * tx_dmamap; int /*<<< orphan*/ * tx_m; } ;
struct TYPE_4__ {int /*<<< orphan*/  fv_rx_tag; struct fv_rxdesc* fv_rxdesc; int /*<<< orphan*/ * fv_rx_sparemap; int /*<<< orphan*/  fv_tx_tag; struct fv_txdesc* fv_txdesc; int /*<<< orphan*/  fv_sf_buff; int /*<<< orphan*/  fv_sf_buff_map; int /*<<< orphan*/  fv_sf_tag; int /*<<< orphan*/  fv_rx_ring_map; int /*<<< orphan*/  fv_rx_ring_tag; int /*<<< orphan*/  fv_tx_ring_map; int /*<<< orphan*/  fv_tx_ring_tag; int /*<<< orphan*/  fv_parent_tag; } ;
struct TYPE_3__ {scalar_t__ fv_tx_ring_paddr; scalar_t__ fv_rx_ring_paddr; scalar_t__ fv_sf_paddr; int /*<<< orphan*/  fv_rx_ring; int /*<<< orphan*/  fv_tx_ring; } ;
struct fv_softc {int /*<<< orphan*/  fv_dev; TYPE_2__ fv_cdata; TYPE_1__ fv_rdata; } ;
struct fv_rxdesc {int /*<<< orphan*/ * rx_dmamap; int /*<<< orphan*/ * rx_m; } ;
struct fv_dmamap_arg {scalar_t__ fv_busaddr; } ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int FV_MAXFRAGS ; 
 int FV_MIN_FRAMELEN ; 
 int FV_RING_ALIGN ; 
 int FV_RX_ALIGN ; 
 int FV_RX_RING_CNT ; 
 int FV_RX_RING_SIZE ; 
 int FV_SFRAME_LEN ; 
 int FV_TX_RING_CNT ; 
 int FV_TX_RING_SIZE ; 
 int MCLBYTES ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct fv_dmamap_arg*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fv_dmamap_cb ; 

__attribute__((used)) static int
fv_dma_alloc(struct fv_softc *sc)
{
	struct fv_dmamap_arg	ctx;
	struct fv_txdesc	*txd;
	struct fv_rxdesc	*rxd;
	int			error, i;

	/* Create parent DMA tag. */
	error = bus_dma_tag_create(
	    bus_get_dma_tag(sc->fv_dev),	/* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
	    0,				/* nsegments */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->fv_cdata.fv_parent_tag);
	if (error != 0) {
		device_printf(sc->fv_dev, "failed to create parent DMA tag\n");
		goto fail;
	}
	/* Create tag for Tx ring. */
	error = bus_dma_tag_create(
	    sc->fv_cdata.fv_parent_tag,	/* parent */
	    FV_RING_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    FV_TX_RING_SIZE,		/* maxsize */
	    1,				/* nsegments */
	    FV_TX_RING_SIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->fv_cdata.fv_tx_ring_tag);
	if (error != 0) {
		device_printf(sc->fv_dev, "failed to create Tx ring DMA tag\n");
		goto fail;
	}

	/* Create tag for Rx ring. */
	error = bus_dma_tag_create(
	    sc->fv_cdata.fv_parent_tag,	/* parent */
	    FV_RING_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    FV_RX_RING_SIZE,		/* maxsize */
	    1,				/* nsegments */
	    FV_RX_RING_SIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->fv_cdata.fv_rx_ring_tag);
	if (error != 0) {
		device_printf(sc->fv_dev, "failed to create Rx ring DMA tag\n");
		goto fail;
	}

	/* Create tag for Tx buffers. */
	error = bus_dma_tag_create(
	    sc->fv_cdata.fv_parent_tag,	/* parent */
	    1, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES * FV_MAXFRAGS,	/* maxsize */
	    FV_MAXFRAGS,		/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->fv_cdata.fv_tx_tag);
	if (error != 0) {
		device_printf(sc->fv_dev, "failed to create Tx DMA tag\n");
		goto fail;
	}

	/* Create tag for Rx buffers. */
	error = bus_dma_tag_create(
	    sc->fv_cdata.fv_parent_tag,	/* parent */
	    FV_RX_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES,			/* maxsize */
	    1,				/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->fv_cdata.fv_rx_tag);
	if (error != 0) {
		device_printf(sc->fv_dev, "failed to create Rx DMA tag\n");
		goto fail;
	}

	/* Create tag for setup frame buffers. */
	error = bus_dma_tag_create(
	    sc->fv_cdata.fv_parent_tag,	/* parent */
	    sizeof(uint32_t), 0,	/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    FV_SFRAME_LEN + FV_MIN_FRAMELEN,			/* maxsize */
	    1,				/* nsegments */
	    FV_SFRAME_LEN + FV_MIN_FRAMELEN,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->fv_cdata.fv_sf_tag);
	if (error != 0) {
		device_printf(sc->fv_dev, "failed to create setup frame DMA tag\n");
		goto fail;
	}

	/* Allocate DMA'able memory and load the DMA map for Tx ring. */
	error = bus_dmamem_alloc(sc->fv_cdata.fv_tx_ring_tag,
	    (void **)&sc->fv_rdata.fv_tx_ring, BUS_DMA_WAITOK |
	    BUS_DMA_COHERENT | BUS_DMA_ZERO, &sc->fv_cdata.fv_tx_ring_map);
	if (error != 0) {
		device_printf(sc->fv_dev,
		    "failed to allocate DMA'able memory for Tx ring\n");
		goto fail;
	}

	ctx.fv_busaddr = 0;
	error = bus_dmamap_load(sc->fv_cdata.fv_tx_ring_tag,
	    sc->fv_cdata.fv_tx_ring_map, sc->fv_rdata.fv_tx_ring,
	    FV_TX_RING_SIZE, fv_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.fv_busaddr == 0) {
		device_printf(sc->fv_dev,
		    "failed to load DMA'able memory for Tx ring\n");
		goto fail;
	}
	sc->fv_rdata.fv_tx_ring_paddr = ctx.fv_busaddr;

	/* Allocate DMA'able memory and load the DMA map for Rx ring. */
	error = bus_dmamem_alloc(sc->fv_cdata.fv_rx_ring_tag,
	    (void **)&sc->fv_rdata.fv_rx_ring, BUS_DMA_WAITOK |
	    BUS_DMA_COHERENT | BUS_DMA_ZERO, &sc->fv_cdata.fv_rx_ring_map);
	if (error != 0) {
		device_printf(sc->fv_dev,
		    "failed to allocate DMA'able memory for Rx ring\n");
		goto fail;
	}

	ctx.fv_busaddr = 0;
	error = bus_dmamap_load(sc->fv_cdata.fv_rx_ring_tag,
	    sc->fv_cdata.fv_rx_ring_map, sc->fv_rdata.fv_rx_ring,
	    FV_RX_RING_SIZE, fv_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.fv_busaddr == 0) {
		device_printf(sc->fv_dev,
		    "failed to load DMA'able memory for Rx ring\n");
		goto fail;
	}
	sc->fv_rdata.fv_rx_ring_paddr = ctx.fv_busaddr;

	/* Allocate DMA'able memory and load the DMA map for setup frame. */
	error = bus_dmamem_alloc(sc->fv_cdata.fv_sf_tag,
	    (void **)&sc->fv_cdata.fv_sf_buff, BUS_DMA_WAITOK |
	    BUS_DMA_COHERENT | BUS_DMA_ZERO, &sc->fv_cdata.fv_sf_buff_map);
	if (error != 0) {
		device_printf(sc->fv_dev,
		    "failed to allocate DMA'able memory for setup frame\n");
		goto fail;
	}

	ctx.fv_busaddr = 0;
	error = bus_dmamap_load(sc->fv_cdata.fv_sf_tag,
	    sc->fv_cdata.fv_sf_buff_map, sc->fv_cdata.fv_sf_buff,
	    FV_SFRAME_LEN, fv_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.fv_busaddr == 0) {
		device_printf(sc->fv_dev,
		    "failed to load DMA'able memory for setup frame\n");
		goto fail;
	}
	sc->fv_rdata.fv_sf_paddr = ctx.fv_busaddr;

	/* Create DMA maps for Tx buffers. */
	for (i = 0; i < FV_TX_RING_CNT; i++) {
		txd = &sc->fv_cdata.fv_txdesc[i];
		txd->tx_m = NULL;
		txd->tx_dmamap = NULL;
		error = bus_dmamap_create(sc->fv_cdata.fv_tx_tag, 0,
		    &txd->tx_dmamap);
		if (error != 0) {
			device_printf(sc->fv_dev,
			    "failed to create Tx dmamap\n");
			goto fail;
		}
	}
	/* Create DMA maps for Rx buffers. */
	if ((error = bus_dmamap_create(sc->fv_cdata.fv_rx_tag, 0,
	    &sc->fv_cdata.fv_rx_sparemap)) != 0) {
		device_printf(sc->fv_dev,
		    "failed to create spare Rx dmamap\n");
		goto fail;
	}
	for (i = 0; i < FV_RX_RING_CNT; i++) {
		rxd = &sc->fv_cdata.fv_rxdesc[i];
		rxd->rx_m = NULL;
		rxd->rx_dmamap = NULL;
		error = bus_dmamap_create(sc->fv_cdata.fv_rx_tag, 0,
		    &rxd->rx_dmamap);
		if (error != 0) {
			device_printf(sc->fv_dev,
			    "failed to create Rx dmamap\n");
			goto fail;
		}
	}

fail:
	return (error);
}