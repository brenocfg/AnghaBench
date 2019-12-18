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
struct TYPE_4__ {int /*<<< orphan*/  ste_rx_tag; struct ste_chain_onefrag* ste_rx_chain; int /*<<< orphan*/ * ste_rx_sparemap; int /*<<< orphan*/  ste_tx_tag; struct ste_chain* ste_tx_chain; int /*<<< orphan*/  ste_rx_list_map; int /*<<< orphan*/  ste_rx_list_tag; int /*<<< orphan*/  ste_tx_list_map; int /*<<< orphan*/  ste_tx_list_tag; int /*<<< orphan*/  ste_parent_tag; } ;
struct TYPE_3__ {scalar_t__ ste_tx_list_paddr; scalar_t__ ste_rx_list_paddr; int /*<<< orphan*/  ste_rx_list; int /*<<< orphan*/  ste_tx_list; } ;
struct ste_softc {int /*<<< orphan*/  ste_dev; TYPE_2__ ste_cdata; TYPE_1__ ste_ldata; } ;
struct ste_dmamap_arg {scalar_t__ ste_busaddr; } ;
struct ste_chain_onefrag {int /*<<< orphan*/ * ste_map; int /*<<< orphan*/ * ste_next; int /*<<< orphan*/ * ste_mbuf; int /*<<< orphan*/ * ste_ptr; } ;
struct ste_chain {int /*<<< orphan*/ * ste_map; scalar_t__ ste_phys; int /*<<< orphan*/ * ste_next; int /*<<< orphan*/ * ste_mbuf; int /*<<< orphan*/ * ste_ptr; } ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int MCLBYTES ; 
 int STE_DESC_ALIGN ; 
 int STE_MAXFRAGS ; 
 int STE_RX_LIST_CNT ; 
 int STE_RX_LIST_SZ ; 
 int STE_TX_LIST_CNT ; 
 int STE_TX_LIST_SZ ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ste_dmamap_arg*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ste_dmamap_cb ; 

__attribute__((used)) static int
ste_dma_alloc(struct ste_softc *sc)
{
	struct ste_chain *txc;
	struct ste_chain_onefrag *rxc;
	struct ste_dmamap_arg ctx;
	int error, i;

	/* Create parent DMA tag. */
	error = bus_dma_tag_create(
	    bus_get_dma_tag(sc->ste_dev), /* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
	    0,				/* nsegments */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->ste_cdata.ste_parent_tag);
	if (error != 0) {
		device_printf(sc->ste_dev,
		    "could not create parent DMA tag.\n");
		goto fail;
	}

	/* Create DMA tag for Tx descriptor list. */
	error = bus_dma_tag_create(
	    sc->ste_cdata.ste_parent_tag, /* parent */
	    STE_DESC_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    STE_TX_LIST_SZ,		/* maxsize */
	    1,				/* nsegments */
	    STE_TX_LIST_SZ,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->ste_cdata.ste_tx_list_tag);
	if (error != 0) {
		device_printf(sc->ste_dev,
		    "could not create Tx list DMA tag.\n");
		goto fail;
	}

	/* Create DMA tag for Rx descriptor list. */
	error = bus_dma_tag_create(
	    sc->ste_cdata.ste_parent_tag, /* parent */
	    STE_DESC_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    STE_RX_LIST_SZ,		/* maxsize */
	    1,				/* nsegments */
	    STE_RX_LIST_SZ,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->ste_cdata.ste_rx_list_tag);
	if (error != 0) {
		device_printf(sc->ste_dev,
		    "could not create Rx list DMA tag.\n");
		goto fail;
	}

	/* Create DMA tag for Tx buffers. */
	error = bus_dma_tag_create(
	    sc->ste_cdata.ste_parent_tag, /* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES * STE_MAXFRAGS,	/* maxsize */
	    STE_MAXFRAGS,		/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->ste_cdata.ste_tx_tag);
	if (error != 0) {
		device_printf(sc->ste_dev, "could not create Tx DMA tag.\n");
		goto fail;
	}

	/* Create DMA tag for Rx buffers. */
	error = bus_dma_tag_create(
	    sc->ste_cdata.ste_parent_tag, /* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES,			/* maxsize */
	    1,				/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->ste_cdata.ste_rx_tag);
	if (error != 0) {
		device_printf(sc->ste_dev, "could not create Rx DMA tag.\n");
		goto fail;
	}

	/* Allocate DMA'able memory and load the DMA map for Tx list. */
	error = bus_dmamem_alloc(sc->ste_cdata.ste_tx_list_tag,
	    (void **)&sc->ste_ldata.ste_tx_list,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &sc->ste_cdata.ste_tx_list_map);
	if (error != 0) {
		device_printf(sc->ste_dev,
		    "could not allocate DMA'able memory for Tx list.\n");
		goto fail;
	}
	ctx.ste_busaddr = 0;
	error = bus_dmamap_load(sc->ste_cdata.ste_tx_list_tag,
	    sc->ste_cdata.ste_tx_list_map, sc->ste_ldata.ste_tx_list,
	    STE_TX_LIST_SZ, ste_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.ste_busaddr == 0) {
		device_printf(sc->ste_dev,
		    "could not load DMA'able memory for Tx list.\n");
		goto fail;
	}
	sc->ste_ldata.ste_tx_list_paddr = ctx.ste_busaddr;

	/* Allocate DMA'able memory and load the DMA map for Rx list. */
	error = bus_dmamem_alloc(sc->ste_cdata.ste_rx_list_tag,
	    (void **)&sc->ste_ldata.ste_rx_list,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &sc->ste_cdata.ste_rx_list_map);
	if (error != 0) {
		device_printf(sc->ste_dev,
		    "could not allocate DMA'able memory for Rx list.\n");
		goto fail;
	}
	ctx.ste_busaddr = 0;
	error = bus_dmamap_load(sc->ste_cdata.ste_rx_list_tag,
	    sc->ste_cdata.ste_rx_list_map, sc->ste_ldata.ste_rx_list,
	    STE_RX_LIST_SZ, ste_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.ste_busaddr == 0) {
		device_printf(sc->ste_dev,
		    "could not load DMA'able memory for Rx list.\n");
		goto fail;
	}
	sc->ste_ldata.ste_rx_list_paddr = ctx.ste_busaddr;

	/* Create DMA maps for Tx buffers. */
	for (i = 0; i < STE_TX_LIST_CNT; i++) {
		txc = &sc->ste_cdata.ste_tx_chain[i];
		txc->ste_ptr = NULL;
		txc->ste_mbuf = NULL;
		txc->ste_next = NULL;
		txc->ste_phys = 0;
		txc->ste_map = NULL;
		error = bus_dmamap_create(sc->ste_cdata.ste_tx_tag, 0,
		    &txc->ste_map);
		if (error != 0) {
			device_printf(sc->ste_dev,
			    "could not create Tx dmamap.\n");
			goto fail;
		}
	}
	/* Create DMA maps for Rx buffers. */
	if ((error = bus_dmamap_create(sc->ste_cdata.ste_rx_tag, 0,
	    &sc->ste_cdata.ste_rx_sparemap)) != 0) {
		device_printf(sc->ste_dev,
		    "could not create spare Rx dmamap.\n");
		goto fail;
	}
	for (i = 0; i < STE_RX_LIST_CNT; i++) {
		rxc = &sc->ste_cdata.ste_rx_chain[i];
		rxc->ste_ptr = NULL;
		rxc->ste_mbuf = NULL;
		rxc->ste_next = NULL;
		rxc->ste_map = NULL;
		error = bus_dmamap_create(sc->ste_cdata.ste_rx_tag, 0,
		    &rxc->ste_map);
		if (error != 0) {
			device_printf(sc->ste_dev,
			    "could not create Rx dmamap.\n");
			goto fail;
		}
	}

fail:
	return (error);
}