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
struct stge_txdesc {scalar_t__ tx_dmamap; int /*<<< orphan*/ * tx_m; } ;
struct TYPE_3__ {int /*<<< orphan*/  stge_rx_tag; struct stge_rxdesc* stge_rxdesc; scalar_t__ stge_rx_sparemap; int /*<<< orphan*/  stge_tx_tag; struct stge_txdesc* stge_txdesc; int /*<<< orphan*/  stge_rx_ring_map; int /*<<< orphan*/  stge_rx_ring_tag; int /*<<< orphan*/  stge_tx_ring_map; int /*<<< orphan*/  stge_tx_ring_tag; int /*<<< orphan*/  stge_parent_tag; } ;
struct TYPE_4__ {scalar_t__ stge_tx_ring_paddr; scalar_t__ stge_rx_ring_paddr; int /*<<< orphan*/  stge_rx_ring; int /*<<< orphan*/  stge_tx_ring; } ;
struct stge_softc {int /*<<< orphan*/  sc_dev; TYPE_1__ sc_cdata; TYPE_2__ sc_rdata; } ;
struct stge_rxdesc {scalar_t__ rx_dmamap; int /*<<< orphan*/ * rx_m; } ;
struct stge_dmamap_arg {scalar_t__ stge_busaddr; } ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_NOWAIT ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int MCLBYTES ; 
 int /*<<< orphan*/  STGE_DMA_MAXADDR ; 
 int STGE_MAXTXSEGS ; 
 int STGE_RING_ALIGN ; 
 int STGE_RX_RING_CNT ; 
 int STGE_RX_RING_SZ ; 
 int STGE_TX_RING_CNT ; 
 int STGE_TX_RING_SZ ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct stge_dmamap_arg*,int) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stge_dmamap_cb ; 

__attribute__((used)) static int
stge_dma_alloc(struct stge_softc *sc)
{
	struct stge_dmamap_arg ctx;
	struct stge_txdesc *txd;
	struct stge_rxdesc *rxd;
	int error, i;

	/* create parent tag. */
	error = bus_dma_tag_create(bus_get_dma_tag(sc->sc_dev),/* parent */
		    1, 0,			/* algnmnt, boundary */
		    STGE_DMA_MAXADDR,		/* lowaddr */
		    BUS_SPACE_MAXADDR,		/* highaddr */
		    NULL, NULL,			/* filter, filterarg */
		    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
		    0,				/* nsegments */
		    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
		    0,				/* flags */
		    NULL, NULL,			/* lockfunc, lockarg */
		    &sc->sc_cdata.stge_parent_tag);
	if (error != 0) {
		device_printf(sc->sc_dev, "failed to create parent DMA tag\n");
		goto fail;
	}
	/* create tag for Tx ring. */
	error = bus_dma_tag_create(sc->sc_cdata.stge_parent_tag,/* parent */
		    STGE_RING_ALIGN, 0,		/* algnmnt, boundary */
		    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
		    BUS_SPACE_MAXADDR,		/* highaddr */
		    NULL, NULL,			/* filter, filterarg */
		    STGE_TX_RING_SZ,		/* maxsize */
		    1,				/* nsegments */
		    STGE_TX_RING_SZ,		/* maxsegsize */
		    0,				/* flags */
		    NULL, NULL,			/* lockfunc, lockarg */
		    &sc->sc_cdata.stge_tx_ring_tag);
	if (error != 0) {
		device_printf(sc->sc_dev,
		    "failed to allocate Tx ring DMA tag\n");
		goto fail;
	}

	/* create tag for Rx ring. */
	error = bus_dma_tag_create(sc->sc_cdata.stge_parent_tag,/* parent */
		    STGE_RING_ALIGN, 0,		/* algnmnt, boundary */
		    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
		    BUS_SPACE_MAXADDR,		/* highaddr */
		    NULL, NULL,			/* filter, filterarg */
		    STGE_RX_RING_SZ,		/* maxsize */
		    1,				/* nsegments */
		    STGE_RX_RING_SZ,		/* maxsegsize */
		    0,				/* flags */
		    NULL, NULL,			/* lockfunc, lockarg */
		    &sc->sc_cdata.stge_rx_ring_tag);
	if (error != 0) {
		device_printf(sc->sc_dev,
		    "failed to allocate Rx ring DMA tag\n");
		goto fail;
	}

	/* create tag for Tx buffers. */
	error = bus_dma_tag_create(sc->sc_cdata.stge_parent_tag,/* parent */
		    1, 0,			/* algnmnt, boundary */
		    BUS_SPACE_MAXADDR,		/* lowaddr */
		    BUS_SPACE_MAXADDR,		/* highaddr */
		    NULL, NULL,			/* filter, filterarg */
		    MCLBYTES * STGE_MAXTXSEGS,	/* maxsize */
		    STGE_MAXTXSEGS,		/* nsegments */
		    MCLBYTES,			/* maxsegsize */
		    0,				/* flags */
		    NULL, NULL,			/* lockfunc, lockarg */
		    &sc->sc_cdata.stge_tx_tag);
	if (error != 0) {
		device_printf(sc->sc_dev, "failed to allocate Tx DMA tag\n");
		goto fail;
	}

	/* create tag for Rx buffers. */
	error = bus_dma_tag_create(sc->sc_cdata.stge_parent_tag,/* parent */
		    1, 0,			/* algnmnt, boundary */
		    BUS_SPACE_MAXADDR,		/* lowaddr */
		    BUS_SPACE_MAXADDR,		/* highaddr */
		    NULL, NULL,			/* filter, filterarg */
		    MCLBYTES,			/* maxsize */
		    1,				/* nsegments */
		    MCLBYTES,			/* maxsegsize */
		    0,				/* flags */
		    NULL, NULL,			/* lockfunc, lockarg */
		    &sc->sc_cdata.stge_rx_tag);
	if (error != 0) {
		device_printf(sc->sc_dev, "failed to allocate Rx DMA tag\n");
		goto fail;
	}

	/* allocate DMA'able memory and load the DMA map for Tx ring. */
	error = bus_dmamem_alloc(sc->sc_cdata.stge_tx_ring_tag,
	    (void **)&sc->sc_rdata.stge_tx_ring, BUS_DMA_NOWAIT |
	    BUS_DMA_COHERENT | BUS_DMA_ZERO, &sc->sc_cdata.stge_tx_ring_map);
	if (error != 0) {
		device_printf(sc->sc_dev,
		    "failed to allocate DMA'able memory for Tx ring\n");
		goto fail;
	}

	ctx.stge_busaddr = 0;
	error = bus_dmamap_load(sc->sc_cdata.stge_tx_ring_tag,
	    sc->sc_cdata.stge_tx_ring_map, sc->sc_rdata.stge_tx_ring,
	    STGE_TX_RING_SZ, stge_dmamap_cb, &ctx, BUS_DMA_NOWAIT);
	if (error != 0 || ctx.stge_busaddr == 0) {
		device_printf(sc->sc_dev,
		    "failed to load DMA'able memory for Tx ring\n");
		goto fail;
	}
	sc->sc_rdata.stge_tx_ring_paddr = ctx.stge_busaddr;

	/* allocate DMA'able memory and load the DMA map for Rx ring. */
	error = bus_dmamem_alloc(sc->sc_cdata.stge_rx_ring_tag,
	    (void **)&sc->sc_rdata.stge_rx_ring, BUS_DMA_NOWAIT |
	    BUS_DMA_COHERENT | BUS_DMA_ZERO, &sc->sc_cdata.stge_rx_ring_map);
	if (error != 0) {
		device_printf(sc->sc_dev,
		    "failed to allocate DMA'able memory for Rx ring\n");
		goto fail;
	}

	ctx.stge_busaddr = 0;
	error = bus_dmamap_load(sc->sc_cdata.stge_rx_ring_tag,
	    sc->sc_cdata.stge_rx_ring_map, sc->sc_rdata.stge_rx_ring,
	    STGE_RX_RING_SZ, stge_dmamap_cb, &ctx, BUS_DMA_NOWAIT);
	if (error != 0 || ctx.stge_busaddr == 0) {
		device_printf(sc->sc_dev,
		    "failed to load DMA'able memory for Rx ring\n");
		goto fail;
	}
	sc->sc_rdata.stge_rx_ring_paddr = ctx.stge_busaddr;

	/* create DMA maps for Tx buffers. */
	for (i = 0; i < STGE_TX_RING_CNT; i++) {
		txd = &sc->sc_cdata.stge_txdesc[i];
		txd->tx_m = NULL;
		txd->tx_dmamap = 0;
		error = bus_dmamap_create(sc->sc_cdata.stge_tx_tag, 0,
		    &txd->tx_dmamap);
		if (error != 0) {
			device_printf(sc->sc_dev,
			    "failed to create Tx dmamap\n");
			goto fail;
		}
	}
	/* create DMA maps for Rx buffers. */
	if ((error = bus_dmamap_create(sc->sc_cdata.stge_rx_tag, 0,
	    &sc->sc_cdata.stge_rx_sparemap)) != 0) {
		device_printf(sc->sc_dev, "failed to create spare Rx dmamap\n");
		goto fail;
	}
	for (i = 0; i < STGE_RX_RING_CNT; i++) {
		rxd = &sc->sc_cdata.stge_rxdesc[i];
		rxd->rx_m = NULL;
		rxd->rx_dmamap = 0;
		error = bus_dmamap_create(sc->sc_cdata.stge_rx_tag, 0,
		    &rxd->rx_dmamap);
		if (error != 0) {
			device_printf(sc->sc_dev,
			    "failed to create Rx dmamap\n");
			goto fail;
		}
	}

fail:
	return (error);
}