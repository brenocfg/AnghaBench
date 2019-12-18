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
struct vge_txdesc {int /*<<< orphan*/ * tx_dmamap; int /*<<< orphan*/ * tx_m; } ;
struct TYPE_4__ {int /*<<< orphan*/  vge_rx_tag; struct vge_rxdesc* vge_rxdesc; int /*<<< orphan*/ * vge_rx_sparemap; int /*<<< orphan*/  vge_tx_tag; struct vge_txdesc* vge_txdesc; int /*<<< orphan*/  vge_buffer_tag; int /*<<< orphan*/  vge_rx_ring_map; int /*<<< orphan*/  vge_rx_ring_tag; int /*<<< orphan*/  vge_tx_ring_map; int /*<<< orphan*/  vge_tx_ring_tag; int /*<<< orphan*/  vge_ring_tag; } ;
struct TYPE_3__ {scalar_t__ vge_tx_ring_paddr; scalar_t__ vge_rx_ring_paddr; int /*<<< orphan*/  vge_rx_ring; int /*<<< orphan*/  vge_tx_ring; } ;
struct vge_softc {int vge_flags; int /*<<< orphan*/  vge_dev; TYPE_2__ vge_cdata; TYPE_1__ vge_rdata; } ;
struct vge_rxdesc {int /*<<< orphan*/ * rx_dmamap; int /*<<< orphan*/ * rx_m; } ;
struct vge_dmamap_arg {scalar_t__ vge_busaddr; } ;
typedef  int bus_addr_t ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int BUS_SPACE_MAXADDR ; 
 int BUS_SPACE_MAXADDR_32BIT ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int MCLBYTES ; 
 scalar_t__ VGE_ADDR_HI (int) ; 
 int VGE_BUF_DMA_MAXADDR ; 
 int VGE_FLAG_PCIE ; 
 int VGE_MAXTXSEGS ; 
 int VGE_RX_BUF_ALIGN ; 
 int VGE_RX_DESC_CNT ; 
 int VGE_RX_LIST_SZ ; 
 int VGE_RX_RING_ALIGN ; 
 int VGE_TX_DESC_CNT ; 
 int VGE_TX_LIST_SZ ; 
 int VGE_TX_RING_ALIGN ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct vge_dmamap_arg*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vge_dma_free (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_dmamap_cb ; 

__attribute__((used)) static int
vge_dma_alloc(struct vge_softc *sc)
{
	struct vge_dmamap_arg ctx;
	struct vge_txdesc *txd;
	struct vge_rxdesc *rxd;
	bus_addr_t lowaddr, tx_ring_end, rx_ring_end;
	int error, i;

	/*
	 * It seems old PCI controllers do not support DAC.  DAC
	 * configuration can be enabled by accessing VGE_CHIPCFG3
	 * register but honor EEPROM configuration instead of
	 * blindly overriding DAC configuration.  PCIe based
	 * controllers are supposed to support 64bit DMA so enable
	 * 64bit DMA on these controllers.
	 */
	if ((sc->vge_flags & VGE_FLAG_PCIE) != 0)
		lowaddr = BUS_SPACE_MAXADDR;
	else
		lowaddr = BUS_SPACE_MAXADDR_32BIT;

again:
	/* Create parent ring tag. */
	error = bus_dma_tag_create(bus_get_dma_tag(sc->vge_dev),/* parent */
	    1, 0,			/* algnmnt, boundary */
	    lowaddr,			/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
	    0,				/* nsegments */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->vge_cdata.vge_ring_tag);
	if (error != 0) {
		device_printf(sc->vge_dev,
		    "could not create parent DMA tag.\n");
		goto fail;
	}

	/* Create tag for Tx ring. */
	error = bus_dma_tag_create(sc->vge_cdata.vge_ring_tag,/* parent */
	    VGE_TX_RING_ALIGN, 0,	/* algnmnt, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    VGE_TX_LIST_SZ,		/* maxsize */
	    1,				/* nsegments */
	    VGE_TX_LIST_SZ,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->vge_cdata.vge_tx_ring_tag);
	if (error != 0) {
		device_printf(sc->vge_dev,
		    "could not allocate Tx ring DMA tag.\n");
		goto fail;
	}

	/* Create tag for Rx ring. */
	error = bus_dma_tag_create(sc->vge_cdata.vge_ring_tag,/* parent */
	    VGE_RX_RING_ALIGN, 0,	/* algnmnt, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    VGE_RX_LIST_SZ,		/* maxsize */
	    1,				/* nsegments */
	    VGE_RX_LIST_SZ,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->vge_cdata.vge_rx_ring_tag);
	if (error != 0) {
		device_printf(sc->vge_dev,
		    "could not allocate Rx ring DMA tag.\n");
		goto fail;
	}

	/* Allocate DMA'able memory and load the DMA map for Tx ring. */
	error = bus_dmamem_alloc(sc->vge_cdata.vge_tx_ring_tag,
	    (void **)&sc->vge_rdata.vge_tx_ring,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &sc->vge_cdata.vge_tx_ring_map);
	if (error != 0) {
		device_printf(sc->vge_dev,
		    "could not allocate DMA'able memory for Tx ring.\n");
		goto fail;
	}

	ctx.vge_busaddr = 0;
	error = bus_dmamap_load(sc->vge_cdata.vge_tx_ring_tag,
	    sc->vge_cdata.vge_tx_ring_map, sc->vge_rdata.vge_tx_ring,
	    VGE_TX_LIST_SZ, vge_dmamap_cb, &ctx, BUS_DMA_NOWAIT);
	if (error != 0 || ctx.vge_busaddr == 0) {
		device_printf(sc->vge_dev,
		    "could not load DMA'able memory for Tx ring.\n");
		goto fail;
	}
	sc->vge_rdata.vge_tx_ring_paddr = ctx.vge_busaddr;

	/* Allocate DMA'able memory and load the DMA map for Rx ring. */
	error = bus_dmamem_alloc(sc->vge_cdata.vge_rx_ring_tag,
	    (void **)&sc->vge_rdata.vge_rx_ring,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &sc->vge_cdata.vge_rx_ring_map);
	if (error != 0) {
		device_printf(sc->vge_dev,
		    "could not allocate DMA'able memory for Rx ring.\n");
		goto fail;
	}

	ctx.vge_busaddr = 0;
	error = bus_dmamap_load(sc->vge_cdata.vge_rx_ring_tag,
	    sc->vge_cdata.vge_rx_ring_map, sc->vge_rdata.vge_rx_ring,
	    VGE_RX_LIST_SZ, vge_dmamap_cb, &ctx, BUS_DMA_NOWAIT);
	if (error != 0 || ctx.vge_busaddr == 0) {
		device_printf(sc->vge_dev,
		    "could not load DMA'able memory for Rx ring.\n");
		goto fail;
	}
	sc->vge_rdata.vge_rx_ring_paddr = ctx.vge_busaddr;

	/* Tx/Rx descriptor queue should reside within 4GB boundary. */
	tx_ring_end = sc->vge_rdata.vge_tx_ring_paddr + VGE_TX_LIST_SZ;
	rx_ring_end = sc->vge_rdata.vge_rx_ring_paddr + VGE_RX_LIST_SZ;
	if ((VGE_ADDR_HI(tx_ring_end) !=
	    VGE_ADDR_HI(sc->vge_rdata.vge_tx_ring_paddr)) ||
	    (VGE_ADDR_HI(rx_ring_end) !=
	    VGE_ADDR_HI(sc->vge_rdata.vge_rx_ring_paddr)) ||
	    VGE_ADDR_HI(tx_ring_end) != VGE_ADDR_HI(rx_ring_end)) {
		device_printf(sc->vge_dev, "4GB boundary crossed, "
		    "switching to 32bit DMA address mode.\n");
		vge_dma_free(sc);
		/* Limit DMA address space to 32bit and try again. */
		lowaddr = BUS_SPACE_MAXADDR_32BIT;
		goto again;
	}

	if ((sc->vge_flags & VGE_FLAG_PCIE) != 0)
		lowaddr = VGE_BUF_DMA_MAXADDR;
	else
		lowaddr = BUS_SPACE_MAXADDR_32BIT;
	/* Create parent buffer tag. */
	error = bus_dma_tag_create(bus_get_dma_tag(sc->vge_dev),/* parent */
	    1, 0,			/* algnmnt, boundary */
	    lowaddr,			/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
	    0,				/* nsegments */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->vge_cdata.vge_buffer_tag);
	if (error != 0) {
		device_printf(sc->vge_dev,
		    "could not create parent buffer DMA tag.\n");
		goto fail;
	}

	/* Create tag for Tx buffers. */
	error = bus_dma_tag_create(sc->vge_cdata.vge_buffer_tag,/* parent */
	    1, 0,			/* algnmnt, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES * VGE_MAXTXSEGS,	/* maxsize */
	    VGE_MAXTXSEGS,		/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->vge_cdata.vge_tx_tag);
	if (error != 0) {
		device_printf(sc->vge_dev, "could not create Tx DMA tag.\n");
		goto fail;
	}

	/* Create tag for Rx buffers. */
	error = bus_dma_tag_create(sc->vge_cdata.vge_buffer_tag,/* parent */
	    VGE_RX_BUF_ALIGN, 0,	/* algnmnt, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES,			/* maxsize */
	    1,				/* nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->vge_cdata.vge_rx_tag);
	if (error != 0) {
		device_printf(sc->vge_dev, "could not create Rx DMA tag.\n");
		goto fail;
	}

	/* Create DMA maps for Tx buffers. */
	for (i = 0; i < VGE_TX_DESC_CNT; i++) {
		txd = &sc->vge_cdata.vge_txdesc[i];
		txd->tx_m = NULL;
		txd->tx_dmamap = NULL;
		error = bus_dmamap_create(sc->vge_cdata.vge_tx_tag, 0,
		    &txd->tx_dmamap);
		if (error != 0) {
			device_printf(sc->vge_dev,
			    "could not create Tx dmamap.\n");
			goto fail;
		}
	}
	/* Create DMA maps for Rx buffers. */
	if ((error = bus_dmamap_create(sc->vge_cdata.vge_rx_tag, 0,
	    &sc->vge_cdata.vge_rx_sparemap)) != 0) {
		device_printf(sc->vge_dev,
		    "could not create spare Rx dmamap.\n");
		goto fail;
	}
	for (i = 0; i < VGE_RX_DESC_CNT; i++) {
		rxd = &sc->vge_cdata.vge_rxdesc[i];
		rxd->rx_m = NULL;
		rxd->rx_dmamap = NULL;
		error = bus_dmamap_create(sc->vge_cdata.vge_rx_tag, 0,
		    &rxd->rx_dmamap);
		if (error != 0) {
			device_printf(sc->vge_dev,
			    "could not create Rx dmamap.\n");
			goto fail;
		}
	}

fail:
	return (error);
}