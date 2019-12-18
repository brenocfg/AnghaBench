#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bfe_tx_data {int /*<<< orphan*/ * bfe_map; int /*<<< orphan*/ * bfe_mbuf; } ;
struct bfe_softc {int /*<<< orphan*/  bfe_dev; int /*<<< orphan*/  bfe_rxmbuf_tag; struct bfe_rx_data* bfe_rx_ring; int /*<<< orphan*/ * bfe_rx_sparemap; int /*<<< orphan*/  bfe_txmbuf_tag; struct bfe_tx_data* bfe_tx_ring; void* bfe_rx_dma; int /*<<< orphan*/  bfe_rx_list; int /*<<< orphan*/  bfe_rx_map; int /*<<< orphan*/  bfe_rx_tag; void* bfe_tx_dma; int /*<<< orphan*/  bfe_tx_list; int /*<<< orphan*/  bfe_tx_map; int /*<<< orphan*/  bfe_tx_tag; int /*<<< orphan*/  bfe_parent_tag; } ;
struct bfe_rx_data {int /*<<< orphan*/ * bfe_map; scalar_t__ bfe_ctrl; int /*<<< orphan*/ * bfe_mbuf; } ;
struct bfe_dmamap_arg {scalar_t__ bfe_busaddr; } ;

/* Variables and functions */
 void* BFE_ADDR_LO (scalar_t__) ; 
 int /*<<< orphan*/  BFE_DMA_MAXADDR ; 
 int BFE_MAXTXSEGS ; 
 int BFE_RX_LIST_CNT ; 
 int BFE_RX_LIST_SIZE ; 
 int BFE_RX_RING_ALIGN ; 
 int BFE_TX_LIST_CNT ; 
 int BFE_TX_LIST_SIZE ; 
 int BFE_TX_RING_ALIGN ; 
 int BUS_DMA_COHERENT ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int MCLBYTES ; 
 int /*<<< orphan*/  bfe_dma_map ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct bfe_dmamap_arg*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
bfe_dma_alloc(struct bfe_softc *sc)
{
	struct bfe_dmamap_arg ctx;
	struct bfe_rx_data *rd;
	struct bfe_tx_data *td;
	int error, i;

	/*
	 * parent tag.  Apparently the chip cannot handle any DMA address
	 * greater than 1GB.
	 */
	error = bus_dma_tag_create(bus_get_dma_tag(sc->bfe_dev), /* parent */
	    1, 0,			/* alignment, boundary */
	    BFE_DMA_MAXADDR, 		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
	    0,				/* nsegments */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->bfe_parent_tag);
	if (error != 0) {
		device_printf(sc->bfe_dev, "cannot create parent DMA tag.\n");
		goto fail;
	}

	/* Create tag for Tx ring. */
	error = bus_dma_tag_create(sc->bfe_parent_tag, /* parent */
	    BFE_TX_RING_ALIGN, 0,	/* alignment, boundary */
	    BUS_SPACE_MAXADDR, 		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BFE_TX_LIST_SIZE,		/* maxsize */
	    1,				/* nsegments */
	    BFE_TX_LIST_SIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->bfe_tx_tag);
	if (error != 0) {
		device_printf(sc->bfe_dev, "cannot create Tx ring DMA tag.\n");
		goto fail;
	}

	/* Create tag for Rx ring. */
	error = bus_dma_tag_create(sc->bfe_parent_tag, /* parent */
	    BFE_RX_RING_ALIGN, 0,	/* alignment, boundary */
	    BUS_SPACE_MAXADDR, 		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BFE_RX_LIST_SIZE,		/* maxsize */
	    1,				/* nsegments */
	    BFE_RX_LIST_SIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->bfe_rx_tag);
	if (error != 0) {
		device_printf(sc->bfe_dev, "cannot create Rx ring DMA tag.\n");
		goto fail;
	}

	/* Create tag for Tx buffers. */
	error = bus_dma_tag_create(sc->bfe_parent_tag, /* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR, 		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES * BFE_MAXTXSEGS,	/* maxsize */
	    BFE_MAXTXSEGS,		/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->bfe_txmbuf_tag);
	if (error != 0) {
		device_printf(sc->bfe_dev,
		    "cannot create Tx buffer DMA tag.\n");
		goto fail;
	}

	/* Create tag for Rx buffers. */
	error = bus_dma_tag_create(sc->bfe_parent_tag, /* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR, 		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES,			/* maxsize */
	    1,				/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->bfe_rxmbuf_tag);
	if (error != 0) {
		device_printf(sc->bfe_dev,
		    "cannot create Rx buffer DMA tag.\n");
		goto fail;
	}

	/* Allocate DMA'able memory and load DMA map. */
	error = bus_dmamem_alloc(sc->bfe_tx_tag, (void *)&sc->bfe_tx_list,
	  BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT, &sc->bfe_tx_map);
	if (error != 0) {
		device_printf(sc->bfe_dev,
		    "cannot allocate DMA'able memory for Tx ring.\n");
		goto fail;
	}
	ctx.bfe_busaddr = 0;
	error = bus_dmamap_load(sc->bfe_tx_tag, sc->bfe_tx_map,
	    sc->bfe_tx_list, BFE_TX_LIST_SIZE, bfe_dma_map, &ctx,
	    BUS_DMA_NOWAIT);
	if (error != 0 || ctx.bfe_busaddr == 0) {
		device_printf(sc->bfe_dev,
		    "cannot load DMA'able memory for Tx ring.\n");
		goto fail;
	}
	sc->bfe_tx_dma = BFE_ADDR_LO(ctx.bfe_busaddr);

	error = bus_dmamem_alloc(sc->bfe_rx_tag, (void *)&sc->bfe_rx_list,
	  BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT, &sc->bfe_rx_map);
	if (error != 0) {
		device_printf(sc->bfe_dev,
		    "cannot allocate DMA'able memory for Rx ring.\n");
		goto fail;
	}
	ctx.bfe_busaddr = 0;
	error = bus_dmamap_load(sc->bfe_rx_tag, sc->bfe_rx_map,
	    sc->bfe_rx_list, BFE_RX_LIST_SIZE, bfe_dma_map, &ctx,
	    BUS_DMA_NOWAIT);
	if (error != 0 || ctx.bfe_busaddr == 0) {
		device_printf(sc->bfe_dev,
		    "cannot load DMA'able memory for Rx ring.\n");
		goto fail;
	}
	sc->bfe_rx_dma = BFE_ADDR_LO(ctx.bfe_busaddr);

	/* Create DMA maps for Tx buffers. */
	for (i = 0; i < BFE_TX_LIST_CNT; i++) {
		td = &sc->bfe_tx_ring[i];
		td->bfe_mbuf = NULL;
		td->bfe_map = NULL;
		error = bus_dmamap_create(sc->bfe_txmbuf_tag, 0, &td->bfe_map);
		if (error != 0) {
			device_printf(sc->bfe_dev,
			    "cannot create DMA map for Tx.\n");
			goto fail;
		}
	}

	/* Create spare DMA map for Rx buffers. */
	error = bus_dmamap_create(sc->bfe_rxmbuf_tag, 0, &sc->bfe_rx_sparemap);
	if (error != 0) {
		device_printf(sc->bfe_dev, "cannot create spare DMA map for Rx.\n");
		goto fail;
	}
	/* Create DMA maps for Rx buffers. */
	for (i = 0; i < BFE_RX_LIST_CNT; i++) {
		rd = &sc->bfe_rx_ring[i];
		rd->bfe_mbuf = NULL;
		rd->bfe_map = NULL;
		rd->bfe_ctrl = 0;
		error = bus_dmamap_create(sc->bfe_rxmbuf_tag, 0, &rd->bfe_map);
		if (error != 0) {
			device_printf(sc->bfe_dev,
			    "cannot create DMA map for Rx.\n");
			goto fail;
		}
	}

fail:
	return (error);
}