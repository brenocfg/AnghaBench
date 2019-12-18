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
struct ale_txdesc {int /*<<< orphan*/ * tx_dmamap; int /*<<< orphan*/ * tx_m; } ;
struct TYPE_4__ {scalar_t__ ale_tx_ring_paddr; scalar_t__ ale_tx_cmb_paddr; int /*<<< orphan*/  ale_tx_tag; struct ale_txdesc* ale_txdesc; int /*<<< orphan*/  ale_buffer_tag; TYPE_1__* ale_rx_page; int /*<<< orphan*/  ale_tx_cmb; int /*<<< orphan*/  ale_tx_cmb_map; int /*<<< orphan*/  ale_tx_cmb_tag; int /*<<< orphan*/  ale_tx_ring; int /*<<< orphan*/  ale_tx_ring_map; int /*<<< orphan*/  ale_tx_ring_tag; int /*<<< orphan*/  ale_parent_tag; } ;
struct ale_softc {int ale_flags; int /*<<< orphan*/  ale_dev; TYPE_2__ ale_cdata; int /*<<< orphan*/  ale_pagesize; } ;
struct ale_dmamap_arg {scalar_t__ ale_busaddr; } ;
typedef  scalar_t__ bus_addr_t ;
struct TYPE_3__ {scalar_t__ page_paddr; scalar_t__ cmb_paddr; int /*<<< orphan*/  cmb_addr; int /*<<< orphan*/  cmb_map; int /*<<< orphan*/  cmb_tag; int /*<<< orphan*/  page_addr; int /*<<< orphan*/  page_map; int /*<<< orphan*/  page_tag; } ;

/* Variables and functions */
 int ALE_CMB_ALIGN ; 
 int ALE_FLAG_JUMBO ; 
 int ALE_JUMBO_FRAMELEN ; 
 int ALE_MAXTXSEGS ; 
 int ALE_MAX_FRAMELEN ; 
 int /*<<< orphan*/  ALE_RX_CMB_SZ ; 
 int ALE_RX_PAGES ; 
 int ALE_RX_PAGE_ALIGN ; 
 scalar_t__ ALE_RX_PAGE_SZ ; 
 int /*<<< orphan*/  ALE_TSO_MAXSEGSIZE ; 
 int /*<<< orphan*/  ALE_TSO_MAXSIZE ; 
 int /*<<< orphan*/  ALE_TX_CMB_SZ ; 
 int ALE_TX_RING_ALIGN ; 
 int ALE_TX_RING_CNT ; 
 int /*<<< orphan*/  ALE_TX_RING_SZ ; 
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 scalar_t__ BUS_SPACE_MAXADDR ; 
 scalar_t__ BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int ale_check_boundary (struct ale_softc*) ; 
 int /*<<< orphan*/  ale_dma_free (struct ale_softc*) ; 
 int /*<<< orphan*/  ale_dmamap_cb ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ale_dmamap_arg*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  roundup (scalar_t__,int) ; 

__attribute__((used)) static int
ale_dma_alloc(struct ale_softc *sc)
{
	struct ale_txdesc *txd;
	bus_addr_t lowaddr;
	struct ale_dmamap_arg ctx;
	int error, guard_size, i;

	if ((sc->ale_flags & ALE_FLAG_JUMBO) != 0)
		guard_size = ALE_JUMBO_FRAMELEN;
	else
		guard_size = ALE_MAX_FRAMELEN;
	sc->ale_pagesize = roundup(guard_size + ALE_RX_PAGE_SZ,
	    ALE_RX_PAGE_ALIGN);
	lowaddr = BUS_SPACE_MAXADDR;
again:
	/* Create parent DMA tag. */
	error = bus_dma_tag_create(
	    bus_get_dma_tag(sc->ale_dev), /* parent */
	    1, 0,			/* alignment, boundary */
	    lowaddr,			/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
	    0,				/* nsegments */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->ale_cdata.ale_parent_tag);
	if (error != 0) {
		device_printf(sc->ale_dev,
		    "could not create parent DMA tag.\n");
		goto fail;
	}

	/* Create DMA tag for Tx descriptor ring. */
	error = bus_dma_tag_create(
	    sc->ale_cdata.ale_parent_tag, /* parent */
	    ALE_TX_RING_ALIGN, 0,	/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    ALE_TX_RING_SZ,		/* maxsize */
	    1,				/* nsegments */
	    ALE_TX_RING_SZ,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->ale_cdata.ale_tx_ring_tag);
	if (error != 0) {
		device_printf(sc->ale_dev,
		    "could not create Tx ring DMA tag.\n");
		goto fail;
	}

	/* Create DMA tag for Rx pages. */
	for (i = 0; i < ALE_RX_PAGES; i++) {
		error = bus_dma_tag_create(
		    sc->ale_cdata.ale_parent_tag, /* parent */
		    ALE_RX_PAGE_ALIGN, 0,	/* alignment, boundary */
		    BUS_SPACE_MAXADDR,		/* lowaddr */
		    BUS_SPACE_MAXADDR,		/* highaddr */
		    NULL, NULL,			/* filter, filterarg */
		    sc->ale_pagesize,		/* maxsize */
		    1,				/* nsegments */
		    sc->ale_pagesize,		/* maxsegsize */
		    0,				/* flags */
		    NULL, NULL,			/* lockfunc, lockarg */
		    &sc->ale_cdata.ale_rx_page[i].page_tag);
		if (error != 0) {
			device_printf(sc->ale_dev,
			    "could not create Rx page %d DMA tag.\n", i);
			goto fail;
		}
	}

	/* Create DMA tag for Tx coalescing message block. */
	error = bus_dma_tag_create(
	    sc->ale_cdata.ale_parent_tag, /* parent */
	    ALE_CMB_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    ALE_TX_CMB_SZ,		/* maxsize */
	    1,				/* nsegments */
	    ALE_TX_CMB_SZ,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->ale_cdata.ale_tx_cmb_tag);
	if (error != 0) {
		device_printf(sc->ale_dev,
		    "could not create Tx CMB DMA tag.\n");
		goto fail;
	}

	/* Create DMA tag for Rx coalescing message block. */
	for (i = 0; i < ALE_RX_PAGES; i++) {
		error = bus_dma_tag_create(
		    sc->ale_cdata.ale_parent_tag, /* parent */
		    ALE_CMB_ALIGN, 0,		/* alignment, boundary */
		    BUS_SPACE_MAXADDR,		/* lowaddr */
		    BUS_SPACE_MAXADDR,		/* highaddr */
		    NULL, NULL,			/* filter, filterarg */
		    ALE_RX_CMB_SZ,		/* maxsize */
		    1,				/* nsegments */
		    ALE_RX_CMB_SZ,		/* maxsegsize */
		    0,				/* flags */
		    NULL, NULL,			/* lockfunc, lockarg */
		    &sc->ale_cdata.ale_rx_page[i].cmb_tag);
		if (error != 0) {
			device_printf(sc->ale_dev,
			    "could not create Rx page %d CMB DMA tag.\n", i);
			goto fail;
		}
	}

	/* Allocate DMA'able memory and load the DMA map for Tx ring. */
	error = bus_dmamem_alloc(sc->ale_cdata.ale_tx_ring_tag,
	    (void **)&sc->ale_cdata.ale_tx_ring,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &sc->ale_cdata.ale_tx_ring_map);
	if (error != 0) {
		device_printf(sc->ale_dev,
		    "could not allocate DMA'able memory for Tx ring.\n");
		goto fail;
	}
	ctx.ale_busaddr = 0;
	error = bus_dmamap_load(sc->ale_cdata.ale_tx_ring_tag,
	    sc->ale_cdata.ale_tx_ring_map, sc->ale_cdata.ale_tx_ring,
	    ALE_TX_RING_SZ, ale_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.ale_busaddr == 0) {
		device_printf(sc->ale_dev,
		    "could not load DMA'able memory for Tx ring.\n");
		goto fail;
	}
	sc->ale_cdata.ale_tx_ring_paddr = ctx.ale_busaddr;

	/* Rx pages. */
	for (i = 0; i < ALE_RX_PAGES; i++) {
		error = bus_dmamem_alloc(sc->ale_cdata.ale_rx_page[i].page_tag,
		    (void **)&sc->ale_cdata.ale_rx_page[i].page_addr,
		    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
		    &sc->ale_cdata.ale_rx_page[i].page_map);
		if (error != 0) {
			device_printf(sc->ale_dev,
			    "could not allocate DMA'able memory for "
			    "Rx page %d.\n", i);
			goto fail;
		}
		ctx.ale_busaddr = 0;
		error = bus_dmamap_load(sc->ale_cdata.ale_rx_page[i].page_tag,
		    sc->ale_cdata.ale_rx_page[i].page_map,
		    sc->ale_cdata.ale_rx_page[i].page_addr,
		    sc->ale_pagesize, ale_dmamap_cb, &ctx, 0);
		if (error != 0 || ctx.ale_busaddr == 0) {
			device_printf(sc->ale_dev,
			    "could not load DMA'able memory for "
			    "Rx page %d.\n", i);
			goto fail;
		}
		sc->ale_cdata.ale_rx_page[i].page_paddr = ctx.ale_busaddr;
	}

	/* Tx CMB. */
	error = bus_dmamem_alloc(sc->ale_cdata.ale_tx_cmb_tag,
	    (void **)&sc->ale_cdata.ale_tx_cmb,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &sc->ale_cdata.ale_tx_cmb_map);
	if (error != 0) {
		device_printf(sc->ale_dev,
		    "could not allocate DMA'able memory for Tx CMB.\n");
		goto fail;
	}
	ctx.ale_busaddr = 0;
	error = bus_dmamap_load(sc->ale_cdata.ale_tx_cmb_tag,
	    sc->ale_cdata.ale_tx_cmb_map, sc->ale_cdata.ale_tx_cmb,
	    ALE_TX_CMB_SZ, ale_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.ale_busaddr == 0) {
		device_printf(sc->ale_dev,
		    "could not load DMA'able memory for Tx CMB.\n");
		goto fail;
	}
	sc->ale_cdata.ale_tx_cmb_paddr = ctx.ale_busaddr;

	/* Rx CMB. */
	for (i = 0; i < ALE_RX_PAGES; i++) {
		error = bus_dmamem_alloc(sc->ale_cdata.ale_rx_page[i].cmb_tag,
		    (void **)&sc->ale_cdata.ale_rx_page[i].cmb_addr,
		    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
		    &sc->ale_cdata.ale_rx_page[i].cmb_map);
		if (error != 0) {
			device_printf(sc->ale_dev, "could not allocate "
			    "DMA'able memory for Rx page %d CMB.\n", i);
			goto fail;
		}
		ctx.ale_busaddr = 0;
		error = bus_dmamap_load(sc->ale_cdata.ale_rx_page[i].cmb_tag,
		    sc->ale_cdata.ale_rx_page[i].cmb_map,
		    sc->ale_cdata.ale_rx_page[i].cmb_addr,
		    ALE_RX_CMB_SZ, ale_dmamap_cb, &ctx, 0);
		if (error != 0 || ctx.ale_busaddr == 0) {
			device_printf(sc->ale_dev, "could not load DMA'able "
			    "memory for Rx page %d CMB.\n", i);
			goto fail;
		}
		sc->ale_cdata.ale_rx_page[i].cmb_paddr = ctx.ale_busaddr;
	}

	/*
	 * Tx descriptors/RXF0/CMB DMA blocks share the same
	 * high address region of 64bit DMA address space.
	 */
	if (lowaddr != BUS_SPACE_MAXADDR_32BIT &&
	    (error = ale_check_boundary(sc)) != 0) {
		device_printf(sc->ale_dev, "4GB boundary crossed, "
		    "switching to 32bit DMA addressing mode.\n");
		ale_dma_free(sc);
		/*
		 * Limit max allowable DMA address space to 32bit
		 * and try again.
		 */
		lowaddr = BUS_SPACE_MAXADDR_32BIT;
		goto again;
	}

	/*
	 * Create Tx buffer parent tag.
	 * AR81xx allows 64bit DMA addressing of Tx buffers so it
	 * needs separate parent DMA tag as parent DMA address space
	 * could be restricted to be within 32bit address space by
	 * 4GB boundary crossing.
	 */
	error = bus_dma_tag_create(
	    bus_get_dma_tag(sc->ale_dev), /* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
	    0,				/* nsegments */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->ale_cdata.ale_buffer_tag);
	if (error != 0) {
		device_printf(sc->ale_dev,
		    "could not create parent buffer DMA tag.\n");
		goto fail;
	}

	/* Create DMA tag for Tx buffers. */
	error = bus_dma_tag_create(
	    sc->ale_cdata.ale_buffer_tag, /* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    ALE_TSO_MAXSIZE,		/* maxsize */
	    ALE_MAXTXSEGS,		/* nsegments */
	    ALE_TSO_MAXSEGSIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->ale_cdata.ale_tx_tag);
	if (error != 0) {
		device_printf(sc->ale_dev, "could not create Tx DMA tag.\n");
		goto fail;
	}

	/* Create DMA maps for Tx buffers. */
	for (i = 0; i < ALE_TX_RING_CNT; i++) {
		txd = &sc->ale_cdata.ale_txdesc[i];
		txd->tx_m = NULL;
		txd->tx_dmamap = NULL;
		error = bus_dmamap_create(sc->ale_cdata.ale_tx_tag, 0,
		    &txd->tx_dmamap);
		if (error != 0) {
			device_printf(sc->ale_dev,
			    "could not create Tx dmamap.\n");
			goto fail;
		}
	}

fail:
	return (error);
}