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
struct alc_txdesc {int /*<<< orphan*/ * tx_dmamap; int /*<<< orphan*/ * tx_m; } ;
struct TYPE_4__ {int /*<<< orphan*/  alc_rx_tag; struct alc_rxdesc* alc_rxdesc; int /*<<< orphan*/ * alc_rx_sparemap; int /*<<< orphan*/  alc_tx_tag; struct alc_txdesc* alc_txdesc; int /*<<< orphan*/  alc_buffer_tag; int /*<<< orphan*/  alc_smb_map; int /*<<< orphan*/  alc_smb_tag; int /*<<< orphan*/  alc_cmb_map; int /*<<< orphan*/  alc_cmb_tag; int /*<<< orphan*/  alc_rr_ring_map; int /*<<< orphan*/  alc_rr_ring_tag; int /*<<< orphan*/  alc_rx_ring_map; int /*<<< orphan*/  alc_rx_ring_tag; int /*<<< orphan*/  alc_tx_ring_map; int /*<<< orphan*/  alc_tx_ring_tag; int /*<<< orphan*/  alc_parent_tag; } ;
struct TYPE_3__ {scalar_t__ alc_tx_ring_paddr; scalar_t__ alc_rx_ring_paddr; scalar_t__ alc_rr_ring_paddr; scalar_t__ alc_cmb_paddr; scalar_t__ alc_smb_paddr; int /*<<< orphan*/  alc_smb; int /*<<< orphan*/  alc_cmb; int /*<<< orphan*/  alc_rr_ring; int /*<<< orphan*/  alc_rx_ring; int /*<<< orphan*/  alc_tx_ring; } ;
struct alc_softc {int /*<<< orphan*/  alc_dev; TYPE_2__ alc_cdata; TYPE_1__ alc_rdata; } ;
struct alc_rxdesc {int /*<<< orphan*/ * rx_dmamap; int /*<<< orphan*/ * rx_m; } ;
struct alc_dmamap_arg {scalar_t__ alc_busaddr; } ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int ALC_CMB_ALIGN ; 
 int /*<<< orphan*/  ALC_CMB_SZ ; 
 int ALC_MAXTXSEGS ; 
 int ALC_RR_RING_ALIGN ; 
 int /*<<< orphan*/  ALC_RR_RING_SZ ; 
 int ALC_RX_BUF_ALIGN ; 
 int ALC_RX_RING_ALIGN ; 
 int ALC_RX_RING_CNT ; 
 int /*<<< orphan*/  ALC_RX_RING_SZ ; 
 int ALC_SMB_ALIGN ; 
 int /*<<< orphan*/  ALC_SMB_SZ ; 
 int /*<<< orphan*/  ALC_TSO_MAXSEGSIZE ; 
 int /*<<< orphan*/  ALC_TSO_MAXSIZE ; 
 int ALC_TX_RING_ALIGN ; 
 int ALC_TX_RING_CNT ; 
 int /*<<< orphan*/  ALC_TX_RING_SZ ; 
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 scalar_t__ BUS_SPACE_MAXADDR ; 
 scalar_t__ BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int alc_check_boundary (struct alc_softc*) ; 
 int /*<<< orphan*/  alc_dma_free (struct alc_softc*) ; 
 int /*<<< orphan*/  alc_dmamap_cb ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct alc_dmamap_arg*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
alc_dma_alloc(struct alc_softc *sc)
{
	struct alc_txdesc *txd;
	struct alc_rxdesc *rxd;
	bus_addr_t lowaddr;
	struct alc_dmamap_arg ctx;
	int error, i;

	lowaddr = BUS_SPACE_MAXADDR;
again:
	/* Create parent DMA tag. */
	error = bus_dma_tag_create(
	    bus_get_dma_tag(sc->alc_dev), /* parent */
	    1, 0,			/* alignment, boundary */
	    lowaddr,			/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
	    0,				/* nsegments */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->alc_cdata.alc_parent_tag);
	if (error != 0) {
		device_printf(sc->alc_dev,
		    "could not create parent DMA tag.\n");
		goto fail;
	}

	/* Create DMA tag for Tx descriptor ring. */
	error = bus_dma_tag_create(
	    sc->alc_cdata.alc_parent_tag, /* parent */
	    ALC_TX_RING_ALIGN, 0,	/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    ALC_TX_RING_SZ,		/* maxsize */
	    1,				/* nsegments */
	    ALC_TX_RING_SZ,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->alc_cdata.alc_tx_ring_tag);
	if (error != 0) {
		device_printf(sc->alc_dev,
		    "could not create Tx ring DMA tag.\n");
		goto fail;
	}

	/* Create DMA tag for Rx free descriptor ring. */
	error = bus_dma_tag_create(
	    sc->alc_cdata.alc_parent_tag, /* parent */
	    ALC_RX_RING_ALIGN, 0,	/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    ALC_RX_RING_SZ,		/* maxsize */
	    1,				/* nsegments */
	    ALC_RX_RING_SZ,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->alc_cdata.alc_rx_ring_tag);
	if (error != 0) {
		device_printf(sc->alc_dev,
		    "could not create Rx ring DMA tag.\n");
		goto fail;
	}
	/* Create DMA tag for Rx return descriptor ring. */
	error = bus_dma_tag_create(
	    sc->alc_cdata.alc_parent_tag, /* parent */
	    ALC_RR_RING_ALIGN, 0,	/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    ALC_RR_RING_SZ,		/* maxsize */
	    1,				/* nsegments */
	    ALC_RR_RING_SZ,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->alc_cdata.alc_rr_ring_tag);
	if (error != 0) {
		device_printf(sc->alc_dev,
		    "could not create Rx return ring DMA tag.\n");
		goto fail;
	}

	/* Create DMA tag for coalescing message block. */
	error = bus_dma_tag_create(
	    sc->alc_cdata.alc_parent_tag, /* parent */
	    ALC_CMB_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    ALC_CMB_SZ,			/* maxsize */
	    1,				/* nsegments */
	    ALC_CMB_SZ,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->alc_cdata.alc_cmb_tag);
	if (error != 0) {
		device_printf(sc->alc_dev,
		    "could not create CMB DMA tag.\n");
		goto fail;
	}
	/* Create DMA tag for status message block. */
	error = bus_dma_tag_create(
	    sc->alc_cdata.alc_parent_tag, /* parent */
	    ALC_SMB_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    ALC_SMB_SZ,			/* maxsize */
	    1,				/* nsegments */
	    ALC_SMB_SZ,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->alc_cdata.alc_smb_tag);
	if (error != 0) {
		device_printf(sc->alc_dev,
		    "could not create SMB DMA tag.\n");
		goto fail;
	}

	/* Allocate DMA'able memory and load the DMA map for Tx ring. */
	error = bus_dmamem_alloc(sc->alc_cdata.alc_tx_ring_tag,
	    (void **)&sc->alc_rdata.alc_tx_ring,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &sc->alc_cdata.alc_tx_ring_map);
	if (error != 0) {
		device_printf(sc->alc_dev,
		    "could not allocate DMA'able memory for Tx ring.\n");
		goto fail;
	}
	ctx.alc_busaddr = 0;
	error = bus_dmamap_load(sc->alc_cdata.alc_tx_ring_tag,
	    sc->alc_cdata.alc_tx_ring_map, sc->alc_rdata.alc_tx_ring,
	    ALC_TX_RING_SZ, alc_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.alc_busaddr == 0) {
		device_printf(sc->alc_dev,
		    "could not load DMA'able memory for Tx ring.\n");
		goto fail;
	}
	sc->alc_rdata.alc_tx_ring_paddr = ctx.alc_busaddr;

	/* Allocate DMA'able memory and load the DMA map for Rx ring. */
	error = bus_dmamem_alloc(sc->alc_cdata.alc_rx_ring_tag,
	    (void **)&sc->alc_rdata.alc_rx_ring,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &sc->alc_cdata.alc_rx_ring_map);
	if (error != 0) {
		device_printf(sc->alc_dev,
		    "could not allocate DMA'able memory for Rx ring.\n");
		goto fail;
	}
	ctx.alc_busaddr = 0;
	error = bus_dmamap_load(sc->alc_cdata.alc_rx_ring_tag,
	    sc->alc_cdata.alc_rx_ring_map, sc->alc_rdata.alc_rx_ring,
	    ALC_RX_RING_SZ, alc_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.alc_busaddr == 0) {
		device_printf(sc->alc_dev,
		    "could not load DMA'able memory for Rx ring.\n");
		goto fail;
	}
	sc->alc_rdata.alc_rx_ring_paddr = ctx.alc_busaddr;

	/* Allocate DMA'able memory and load the DMA map for Rx return ring. */
	error = bus_dmamem_alloc(sc->alc_cdata.alc_rr_ring_tag,
	    (void **)&sc->alc_rdata.alc_rr_ring,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &sc->alc_cdata.alc_rr_ring_map);
	if (error != 0) {
		device_printf(sc->alc_dev,
		    "could not allocate DMA'able memory for Rx return ring.\n");
		goto fail;
	}
	ctx.alc_busaddr = 0;
	error = bus_dmamap_load(sc->alc_cdata.alc_rr_ring_tag,
	    sc->alc_cdata.alc_rr_ring_map, sc->alc_rdata.alc_rr_ring,
	    ALC_RR_RING_SZ, alc_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.alc_busaddr == 0) {
		device_printf(sc->alc_dev,
		    "could not load DMA'able memory for Tx ring.\n");
		goto fail;
	}
	sc->alc_rdata.alc_rr_ring_paddr = ctx.alc_busaddr;

	/* Allocate DMA'able memory and load the DMA map for CMB. */
	error = bus_dmamem_alloc(sc->alc_cdata.alc_cmb_tag,
	    (void **)&sc->alc_rdata.alc_cmb,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &sc->alc_cdata.alc_cmb_map);
	if (error != 0) {
		device_printf(sc->alc_dev,
		    "could not allocate DMA'able memory for CMB.\n");
		goto fail;
	}
	ctx.alc_busaddr = 0;
	error = bus_dmamap_load(sc->alc_cdata.alc_cmb_tag,
	    sc->alc_cdata.alc_cmb_map, sc->alc_rdata.alc_cmb,
	    ALC_CMB_SZ, alc_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.alc_busaddr == 0) {
		device_printf(sc->alc_dev,
		    "could not load DMA'able memory for CMB.\n");
		goto fail;
	}
	sc->alc_rdata.alc_cmb_paddr = ctx.alc_busaddr;

	/* Allocate DMA'able memory and load the DMA map for SMB. */
	error = bus_dmamem_alloc(sc->alc_cdata.alc_smb_tag,
	    (void **)&sc->alc_rdata.alc_smb,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &sc->alc_cdata.alc_smb_map);
	if (error != 0) {
		device_printf(sc->alc_dev,
		    "could not allocate DMA'able memory for SMB.\n");
		goto fail;
	}
	ctx.alc_busaddr = 0;
	error = bus_dmamap_load(sc->alc_cdata.alc_smb_tag,
	    sc->alc_cdata.alc_smb_map, sc->alc_rdata.alc_smb,
	    ALC_SMB_SZ, alc_dmamap_cb, &ctx, 0);
	if (error != 0 || ctx.alc_busaddr == 0) {
		device_printf(sc->alc_dev,
		    "could not load DMA'able memory for CMB.\n");
		goto fail;
	}
	sc->alc_rdata.alc_smb_paddr = ctx.alc_busaddr;

	/* Make sure we've not crossed 4GB boundary. */
	if (lowaddr != BUS_SPACE_MAXADDR_32BIT &&
	    (error = alc_check_boundary(sc)) != 0) {
		device_printf(sc->alc_dev, "4GB boundary crossed, "
		    "switching to 32bit DMA addressing mode.\n");
		alc_dma_free(sc);
		/*
		 * Limit max allowable DMA address space to 32bit
		 * and try again.
		 */
		lowaddr = BUS_SPACE_MAXADDR_32BIT;
		goto again;
	}

	/*
	 * Create Tx buffer parent tag.
	 * AR81[3567]x allows 64bit DMA addressing of Tx/Rx buffers
	 * so it needs separate parent DMA tag as parent DMA address
	 * space could be restricted to be within 32bit address space
	 * by 4GB boundary crossing.
	 */
	error = bus_dma_tag_create(
	    bus_get_dma_tag(sc->alc_dev), /* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
	    0,				/* nsegments */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->alc_cdata.alc_buffer_tag);
	if (error != 0) {
		device_printf(sc->alc_dev,
		    "could not create parent buffer DMA tag.\n");
		goto fail;
	}

	/* Create DMA tag for Tx buffers. */
	error = bus_dma_tag_create(
	    sc->alc_cdata.alc_buffer_tag, /* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    ALC_TSO_MAXSIZE,		/* maxsize */
	    ALC_MAXTXSEGS,		/* nsegments */
	    ALC_TSO_MAXSEGSIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->alc_cdata.alc_tx_tag);
	if (error != 0) {
		device_printf(sc->alc_dev, "could not create Tx DMA tag.\n");
		goto fail;
	}

	/* Create DMA tag for Rx buffers. */
	error = bus_dma_tag_create(
	    sc->alc_cdata.alc_buffer_tag, /* parent */
	    ALC_RX_BUF_ALIGN, 0,	/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES,			/* maxsize */
	    1,				/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->alc_cdata.alc_rx_tag);
	if (error != 0) {
		device_printf(sc->alc_dev, "could not create Rx DMA tag.\n");
		goto fail;
	}
	/* Create DMA maps for Tx buffers. */
	for (i = 0; i < ALC_TX_RING_CNT; i++) {
		txd = &sc->alc_cdata.alc_txdesc[i];
		txd->tx_m = NULL;
		txd->tx_dmamap = NULL;
		error = bus_dmamap_create(sc->alc_cdata.alc_tx_tag, 0,
		    &txd->tx_dmamap);
		if (error != 0) {
			device_printf(sc->alc_dev,
			    "could not create Tx dmamap.\n");
			goto fail;
		}
	}
	/* Create DMA maps for Rx buffers. */
	if ((error = bus_dmamap_create(sc->alc_cdata.alc_rx_tag, 0,
	    &sc->alc_cdata.alc_rx_sparemap)) != 0) {
		device_printf(sc->alc_dev,
		    "could not create spare Rx dmamap.\n");
		goto fail;
	}
	for (i = 0; i < ALC_RX_RING_CNT; i++) {
		rxd = &sc->alc_cdata.alc_rxdesc[i];
		rxd->rx_m = NULL;
		rxd->rx_dmamap = NULL;
		error = bus_dmamap_create(sc->alc_cdata.alc_rx_tag, 0,
		    &rxd->rx_dmamap);
		if (error != 0) {
			device_printf(sc->alc_dev,
			    "could not create Rx dmamap.\n");
			goto fail;
		}
	}

fail:
	return (error);
}