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
struct sge_txdesc {int /*<<< orphan*/ * tx_dmamap; scalar_t__ tx_ndesc; int /*<<< orphan*/ * tx_m; } ;
struct sge_list_data {int /*<<< orphan*/  sge_tx_paddr; int /*<<< orphan*/  sge_tx_ring; int /*<<< orphan*/  sge_rx_paddr; int /*<<< orphan*/  sge_rx_ring; } ;
struct sge_chain_data {int /*<<< orphan*/  sge_rxmbuf_tag; struct sge_rxdesc* sge_rxdesc; int /*<<< orphan*/ * sge_rx_spare_map; int /*<<< orphan*/  sge_txmbuf_tag; struct sge_txdesc* sge_txdesc; int /*<<< orphan*/  sge_tag; int /*<<< orphan*/  sge_tx_dmamap; int /*<<< orphan*/  sge_tx_tag; int /*<<< orphan*/  sge_rx_dmamap; int /*<<< orphan*/  sge_rx_tag; } ;
struct sge_softc {int /*<<< orphan*/  sge_dev; struct sge_list_data sge_ldata; struct sge_chain_data sge_cdata; } ;
struct sge_rxdesc {int /*<<< orphan*/ * rx_dmamap; int /*<<< orphan*/ * rx_m; } ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_NOWAIT ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int SGE_DESC_ALIGN ; 
 int SGE_MAXTXSEGS ; 
 int SGE_RX_BUF_ALIGN ; 
 int SGE_RX_RING_CNT ; 
 int /*<<< orphan*/  SGE_RX_RING_SZ ; 
 int /*<<< orphan*/  SGE_TSO_MAXSEGSIZE ; 
 int /*<<< orphan*/  SGE_TSO_MAXSIZE ; 
 int SGE_TX_RING_CNT ; 
 int /*<<< orphan*/  SGE_TX_RING_SZ ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sge_dma_map_addr ; 

__attribute__((used)) static int
sge_dma_alloc(struct sge_softc *sc)
{
	struct sge_chain_data *cd;
	struct sge_list_data *ld;
	struct sge_rxdesc *rxd;
	struct sge_txdesc *txd;
	int error, i;

	cd = &sc->sge_cdata;
	ld = &sc->sge_ldata;
	error = bus_dma_tag_create(bus_get_dma_tag(sc->sge_dev),
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
	    1,				/* nsegments */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
	    0,				/* flags */
	    NULL,			/* lockfunc */
	    NULL,			/* lockarg */
	    &cd->sge_tag);
	if (error != 0) {
		device_printf(sc->sge_dev,
		    "could not create parent DMA tag.\n");
		goto fail;
	}

	/* RX descriptor ring */
	error = bus_dma_tag_create(cd->sge_tag,
	    SGE_DESC_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    SGE_RX_RING_SZ, 1,		/* maxsize,nsegments */
	    SGE_RX_RING_SZ,		/* maxsegsize */
	    0,				/* flags */
	    NULL,			/* lockfunc */
	    NULL,			/* lockarg */
	    &cd->sge_rx_tag);
	if (error != 0) {
		device_printf(sc->sge_dev,
		    "could not create Rx ring DMA tag.\n");
		goto fail;
	}
	/* Allocate DMA'able memory and load DMA map for RX ring. */
	error = bus_dmamem_alloc(cd->sge_rx_tag, (void **)&ld->sge_rx_ring,
	    BUS_DMA_NOWAIT | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &cd->sge_rx_dmamap);
	if (error != 0) {
		device_printf(sc->sge_dev,
		    "could not allocate DMA'able memory for Rx ring.\n");
		goto fail;
	}
	error = bus_dmamap_load(cd->sge_rx_tag, cd->sge_rx_dmamap,
	    ld->sge_rx_ring, SGE_RX_RING_SZ, sge_dma_map_addr,
	    &ld->sge_rx_paddr, BUS_DMA_NOWAIT);
	if (error != 0) {
		device_printf(sc->sge_dev,
		    "could not load DMA'able memory for Rx ring.\n");
	}

	/* TX descriptor ring */
	error = bus_dma_tag_create(cd->sge_tag,
	    SGE_DESC_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    SGE_TX_RING_SZ, 1,		/* maxsize,nsegments */
	    SGE_TX_RING_SZ,		/* maxsegsize */
	    0,				/* flags */
	    NULL,			/* lockfunc */
	    NULL,			/* lockarg */
	    &cd->sge_tx_tag);
	if (error != 0) {
		device_printf(sc->sge_dev,
		    "could not create Rx ring DMA tag.\n");
		goto fail;
	}
	/* Allocate DMA'able memory and load DMA map for TX ring. */
	error = bus_dmamem_alloc(cd->sge_tx_tag, (void **)&ld->sge_tx_ring,
	    BUS_DMA_NOWAIT | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &cd->sge_tx_dmamap);
	if (error != 0) {
		device_printf(sc->sge_dev,
		    "could not allocate DMA'able memory for Tx ring.\n");
		goto fail;
	}
	error = bus_dmamap_load(cd->sge_tx_tag, cd->sge_tx_dmamap,
	    ld->sge_tx_ring, SGE_TX_RING_SZ, sge_dma_map_addr,
	    &ld->sge_tx_paddr, BUS_DMA_NOWAIT);
	if (error != 0) {
		device_printf(sc->sge_dev,
		    "could not load DMA'able memory for Rx ring.\n");
		goto fail;
	}

	/* Create DMA tag for Tx buffers. */
	error = bus_dma_tag_create(cd->sge_tag, 1, 0, BUS_SPACE_MAXADDR,
	    BUS_SPACE_MAXADDR, NULL, NULL, SGE_TSO_MAXSIZE, SGE_MAXTXSEGS,
	    SGE_TSO_MAXSEGSIZE, 0, NULL, NULL, &cd->sge_txmbuf_tag);
	if (error != 0) {
		device_printf(sc->sge_dev,
		    "could not create Tx mbuf DMA tag.\n");
		goto fail;
	}

	/* Create DMA tag for Rx buffers. */
	error = bus_dma_tag_create(cd->sge_tag, SGE_RX_BUF_ALIGN, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL, MCLBYTES, 1,
	    MCLBYTES, 0, NULL, NULL, &cd->sge_rxmbuf_tag);
	if (error != 0) {
		device_printf(sc->sge_dev,
		    "could not create Rx mbuf DMA tag.\n");
		goto fail;
	}

	/* Create DMA maps for Tx buffers. */
	for (i = 0; i < SGE_TX_RING_CNT; i++) {
		txd = &cd->sge_txdesc[i];
		txd->tx_m = NULL;
		txd->tx_dmamap = NULL;
		txd->tx_ndesc = 0;
		error = bus_dmamap_create(cd->sge_txmbuf_tag, 0,
		    &txd->tx_dmamap);
		if (error != 0) {
			device_printf(sc->sge_dev,
			    "could not create Tx DMA map.\n");
			goto fail;
		}
	}
	/* Create spare DMA map for Rx buffer. */
	error = bus_dmamap_create(cd->sge_rxmbuf_tag, 0, &cd->sge_rx_spare_map);
	if (error != 0) {
		device_printf(sc->sge_dev,
		    "could not create spare Rx DMA map.\n");
		goto fail;
	}
	/* Create DMA maps for Rx buffers. */
	for (i = 0; i < SGE_RX_RING_CNT; i++) {
		rxd = &cd->sge_rxdesc[i];
		rxd->rx_m = NULL;
		rxd->rx_dmamap = NULL;
		error = bus_dmamap_create(cd->sge_rxmbuf_tag, 0,
		    &rxd->rx_dmamap);
		if (error) {
			device_printf(sc->sge_dev,
			    "could not create Rx DMA map.\n");
			goto fail;
		}
	}
fail:
	return (error);
}