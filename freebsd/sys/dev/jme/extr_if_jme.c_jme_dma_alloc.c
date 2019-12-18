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
struct jme_txdesc {int /*<<< orphan*/ * tx_dmamap; int /*<<< orphan*/ * tx_m; } ;
struct TYPE_4__ {int /*<<< orphan*/  jme_rx_tag; struct jme_rxdesc* jme_rxdesc; int /*<<< orphan*/ * jme_rx_sparemap; int /*<<< orphan*/  jme_tx_tag; struct jme_txdesc* jme_txdesc; int /*<<< orphan*/  jme_ssb_map; int /*<<< orphan*/  jme_ssb_tag; int /*<<< orphan*/  jme_buffer_tag; int /*<<< orphan*/  jme_rx_ring_map; int /*<<< orphan*/  jme_rx_ring_tag; int /*<<< orphan*/  jme_tx_ring_map; int /*<<< orphan*/  jme_tx_ring_tag; int /*<<< orphan*/  jme_ring_tag; } ;
struct TYPE_3__ {scalar_t__ jme_tx_ring_paddr; scalar_t__ jme_rx_ring_paddr; scalar_t__ jme_ssb_block_paddr; int /*<<< orphan*/  jme_ssb_block; int /*<<< orphan*/  jme_rx_ring; int /*<<< orphan*/  jme_tx_ring; } ;
struct jme_softc {int jme_flags; int /*<<< orphan*/  jme_dev; TYPE_2__ jme_cdata; TYPE_1__ jme_rdata; } ;
struct jme_rxdesc {int /*<<< orphan*/ * rx_dmamap; int /*<<< orphan*/ * rx_m; } ;
struct jme_dmamap_arg {scalar_t__ jme_busaddr; } ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 scalar_t__ BUS_SPACE_MAXADDR ; 
 scalar_t__ BUS_SPACE_MAXADDR_32BIT ; 
 scalar_t__ BUS_SPACE_MAXSIZE_32BIT ; 
 scalar_t__ JME_ADDR_HI (scalar_t__) ; 
 int JME_FLAG_DMA32BIT ; 
 int JME_MAXTXSEGS ; 
 int JME_RX_BUF_ALIGN ; 
 int JME_RX_RING_ALIGN ; 
 int JME_RX_RING_CNT ; 
 scalar_t__ JME_RX_RING_SIZE ; 
 int JME_SSB_ALIGN ; 
 scalar_t__ JME_SSB_SIZE ; 
 scalar_t__ JME_TSO_MAXSEGSIZE ; 
 scalar_t__ JME_TSO_MAXSIZE ; 
 int JME_TX_RING_ALIGN ; 
 int JME_TX_RING_CNT ; 
 scalar_t__ JME_TX_RING_SIZE ; 
 scalar_t__ MCLBYTES ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct jme_dmamap_arg*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jme_dma_free (struct jme_softc*) ; 
 int /*<<< orphan*/  jme_dmamap_cb ; 

__attribute__((used)) static int
jme_dma_alloc(struct jme_softc *sc)
{
	struct jme_dmamap_arg ctx;
	struct jme_txdesc *txd;
	struct jme_rxdesc *rxd;
	bus_addr_t lowaddr, rx_ring_end, tx_ring_end;
	int error, i;

	lowaddr = BUS_SPACE_MAXADDR;
	if ((sc->jme_flags & JME_FLAG_DMA32BIT) != 0)
		lowaddr = BUS_SPACE_MAXADDR_32BIT;

again:
	/* Create parent ring tag. */
	error = bus_dma_tag_create(bus_get_dma_tag(sc->jme_dev),/* parent */
	    1, 0,			/* algnmnt, boundary */
	    lowaddr,			/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
	    0,				/* nsegments */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->jme_cdata.jme_ring_tag);
	if (error != 0) {
		device_printf(sc->jme_dev,
		    "could not create parent ring DMA tag.\n");
		goto fail;
	}
	/* Create tag for Tx ring. */
	error = bus_dma_tag_create(sc->jme_cdata.jme_ring_tag,/* parent */
	    JME_TX_RING_ALIGN, 0,	/* algnmnt, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    JME_TX_RING_SIZE,		/* maxsize */
	    1,				/* nsegments */
	    JME_TX_RING_SIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->jme_cdata.jme_tx_ring_tag);
	if (error != 0) {
		device_printf(sc->jme_dev,
		    "could not allocate Tx ring DMA tag.\n");
		goto fail;
	}

	/* Create tag for Rx ring. */
	error = bus_dma_tag_create(sc->jme_cdata.jme_ring_tag,/* parent */
	    JME_RX_RING_ALIGN, 0,	/* algnmnt, boundary */
	    lowaddr,			/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    JME_RX_RING_SIZE,		/* maxsize */
	    1,				/* nsegments */
	    JME_RX_RING_SIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->jme_cdata.jme_rx_ring_tag);
	if (error != 0) {
		device_printf(sc->jme_dev,
		    "could not allocate Rx ring DMA tag.\n");
		goto fail;
	}

	/* Allocate DMA'able memory and load the DMA map for Tx ring. */
	error = bus_dmamem_alloc(sc->jme_cdata.jme_tx_ring_tag,
	    (void **)&sc->jme_rdata.jme_tx_ring,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &sc->jme_cdata.jme_tx_ring_map);
	if (error != 0) {
		device_printf(sc->jme_dev,
		    "could not allocate DMA'able memory for Tx ring.\n");
		goto fail;
	}

	ctx.jme_busaddr = 0;
	error = bus_dmamap_load(sc->jme_cdata.jme_tx_ring_tag,
	    sc->jme_cdata.jme_tx_ring_map, sc->jme_rdata.jme_tx_ring,
	    JME_TX_RING_SIZE, jme_dmamap_cb, &ctx, BUS_DMA_NOWAIT);
	if (error != 0 || ctx.jme_busaddr == 0) {
		device_printf(sc->jme_dev,
		    "could not load DMA'able memory for Tx ring.\n");
		goto fail;
	}
	sc->jme_rdata.jme_tx_ring_paddr = ctx.jme_busaddr;

	/* Allocate DMA'able memory and load the DMA map for Rx ring. */
	error = bus_dmamem_alloc(sc->jme_cdata.jme_rx_ring_tag,
	    (void **)&sc->jme_rdata.jme_rx_ring,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &sc->jme_cdata.jme_rx_ring_map);
	if (error != 0) {
		device_printf(sc->jme_dev,
		    "could not allocate DMA'able memory for Rx ring.\n");
		goto fail;
	}

	ctx.jme_busaddr = 0;
	error = bus_dmamap_load(sc->jme_cdata.jme_rx_ring_tag,
	    sc->jme_cdata.jme_rx_ring_map, sc->jme_rdata.jme_rx_ring,
	    JME_RX_RING_SIZE, jme_dmamap_cb, &ctx, BUS_DMA_NOWAIT);
	if (error != 0 || ctx.jme_busaddr == 0) {
		device_printf(sc->jme_dev,
		    "could not load DMA'able memory for Rx ring.\n");
		goto fail;
	}
	sc->jme_rdata.jme_rx_ring_paddr = ctx.jme_busaddr;

	if (lowaddr != BUS_SPACE_MAXADDR_32BIT) {
		/* Tx/Rx descriptor queue should reside within 4GB boundary. */
		tx_ring_end = sc->jme_rdata.jme_tx_ring_paddr +
		    JME_TX_RING_SIZE;
		rx_ring_end = sc->jme_rdata.jme_rx_ring_paddr +
		    JME_RX_RING_SIZE;
		if ((JME_ADDR_HI(tx_ring_end) !=
		    JME_ADDR_HI(sc->jme_rdata.jme_tx_ring_paddr)) ||
		    (JME_ADDR_HI(rx_ring_end) !=
		     JME_ADDR_HI(sc->jme_rdata.jme_rx_ring_paddr))) {
			device_printf(sc->jme_dev, "4GB boundary crossed, "
			    "switching to 32bit DMA address mode.\n");
			jme_dma_free(sc);
			/* Limit DMA address space to 32bit and try again. */
			lowaddr = BUS_SPACE_MAXADDR_32BIT;
			goto again;
		}
	}

	lowaddr = BUS_SPACE_MAXADDR;
	if ((sc->jme_flags & JME_FLAG_DMA32BIT) != 0)
		lowaddr = BUS_SPACE_MAXADDR_32BIT;
	/* Create parent buffer tag. */
	error = bus_dma_tag_create(bus_get_dma_tag(sc->jme_dev),/* parent */
	    1, 0,			/* algnmnt, boundary */
	    lowaddr,			/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
	    0,				/* nsegments */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->jme_cdata.jme_buffer_tag);
	if (error != 0) {
		device_printf(sc->jme_dev,
		    "could not create parent buffer DMA tag.\n");
		goto fail;
	}

	/* Create shadow status block tag. */
	error = bus_dma_tag_create(sc->jme_cdata.jme_buffer_tag,/* parent */
	    JME_SSB_ALIGN, 0,		/* algnmnt, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    JME_SSB_SIZE,		/* maxsize */
	    1,				/* nsegments */
	    JME_SSB_SIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->jme_cdata.jme_ssb_tag);
	if (error != 0) {
		device_printf(sc->jme_dev,
		    "could not create shared status block DMA tag.\n");
		goto fail;
	}

	/* Create tag for Tx buffers. */
	error = bus_dma_tag_create(sc->jme_cdata.jme_buffer_tag,/* parent */
	    1, 0,			/* algnmnt, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    JME_TSO_MAXSIZE,		/* maxsize */
	    JME_MAXTXSEGS,		/* nsegments */
	    JME_TSO_MAXSEGSIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->jme_cdata.jme_tx_tag);
	if (error != 0) {
		device_printf(sc->jme_dev, "could not create Tx DMA tag.\n");
		goto fail;
	}

	/* Create tag for Rx buffers. */
	error = bus_dma_tag_create(sc->jme_cdata.jme_buffer_tag,/* parent */
	    JME_RX_BUF_ALIGN, 0,	/* algnmnt, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES,			/* maxsize */
	    1,				/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->jme_cdata.jme_rx_tag);
	if (error != 0) {
		device_printf(sc->jme_dev, "could not create Rx DMA tag.\n");
		goto fail;
	}

	/*
	 * Allocate DMA'able memory and load the DMA map for shared
	 * status block.
	 */
	error = bus_dmamem_alloc(sc->jme_cdata.jme_ssb_tag,
	    (void **)&sc->jme_rdata.jme_ssb_block,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &sc->jme_cdata.jme_ssb_map);
	if (error != 0) {
		device_printf(sc->jme_dev, "could not allocate DMA'able "
		    "memory for shared status block.\n");
		goto fail;
	}

	ctx.jme_busaddr = 0;
	error = bus_dmamap_load(sc->jme_cdata.jme_ssb_tag,
	    sc->jme_cdata.jme_ssb_map, sc->jme_rdata.jme_ssb_block,
	    JME_SSB_SIZE, jme_dmamap_cb, &ctx, BUS_DMA_NOWAIT);
	if (error != 0 || ctx.jme_busaddr == 0) {
		device_printf(sc->jme_dev, "could not load DMA'able memory "
		    "for shared status block.\n");
		goto fail;
	}
	sc->jme_rdata.jme_ssb_block_paddr = ctx.jme_busaddr;

	/* Create DMA maps for Tx buffers. */
	for (i = 0; i < JME_TX_RING_CNT; i++) {
		txd = &sc->jme_cdata.jme_txdesc[i];
		txd->tx_m = NULL;
		txd->tx_dmamap = NULL;
		error = bus_dmamap_create(sc->jme_cdata.jme_tx_tag, 0,
		    &txd->tx_dmamap);
		if (error != 0) {
			device_printf(sc->jme_dev,
			    "could not create Tx dmamap.\n");
			goto fail;
		}
	}
	/* Create DMA maps for Rx buffers. */
	if ((error = bus_dmamap_create(sc->jme_cdata.jme_rx_tag, 0,
	    &sc->jme_cdata.jme_rx_sparemap)) != 0) {
		device_printf(sc->jme_dev,
		    "could not create spare Rx dmamap.\n");
		goto fail;
	}
	for (i = 0; i < JME_RX_RING_CNT; i++) {
		rxd = &sc->jme_cdata.jme_rxdesc[i];
		rxd->rx_m = NULL;
		rxd->rx_dmamap = NULL;
		error = bus_dmamap_create(sc->jme_cdata.jme_rx_tag, 0,
		    &rxd->rx_dmamap);
		if (error != 0) {
			device_printf(sc->jme_dev,
			    "could not create Rx dmamap.\n");
			goto fail;
		}
	}

fail:
	return (error);
}