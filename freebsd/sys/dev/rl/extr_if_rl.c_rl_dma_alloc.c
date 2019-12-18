#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ rl_rx_buf_paddr; scalar_t__ rl_rx_buf; scalar_t__ rl_rx_buf_ptr; int /*<<< orphan*/ ** rl_tx_dmamap; int /*<<< orphan*/  rl_tx_tag; int /*<<< orphan*/ ** rl_tx_chain; int /*<<< orphan*/  rl_rx_dmamap; int /*<<< orphan*/  rl_rx_tag; } ;
struct rl_softc {TYPE_1__ rl_cdata; int /*<<< orphan*/  rl_dev; int /*<<< orphan*/  rl_parent_tag; } ;
struct rl_dmamap_arg {scalar_t__ rl_busaddr; } ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 scalar_t__ BUS_SPACE_MAXSIZE_32BIT ; 
 scalar_t__ MCLBYTES ; 
 scalar_t__ RL_RXBUFLEN ; 
 int RL_RX_8139_BUF_ALIGN ; 
 scalar_t__ RL_RX_8139_BUF_GUARD_SZ ; 
 scalar_t__ RL_RX_8139_BUF_RESERVE ; 
 int RL_TX_8139_BUF_ALIGN ; 
 int RL_TX_LIST_CNT ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct rl_dmamap_arg*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rl_dmamap_cb ; 

__attribute__((used)) static int
rl_dma_alloc(struct rl_softc *sc)
{
	struct rl_dmamap_arg	ctx;
	int			error, i;

	/*
	 * Allocate the parent bus DMA tag appropriate for PCI.
	 */
	error = bus_dma_tag_create(bus_get_dma_tag(sc->rl_dev),	/* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE_32BIT, 0,	/* maxsize, nsegments */
	    BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->rl_parent_tag);
	if (error) {
                device_printf(sc->rl_dev,
		    "failed to create parent DMA tag.\n");
		goto fail;
	}
	/* Create DMA tag for Rx memory block. */
	error = bus_dma_tag_create(sc->rl_parent_tag,	/* parent */
	    RL_RX_8139_BUF_ALIGN, 0,	/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    RL_RXBUFLEN + RL_RX_8139_BUF_GUARD_SZ, 1,	/* maxsize,nsegments */
	    RL_RXBUFLEN + RL_RX_8139_BUF_GUARD_SZ,	/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->rl_cdata.rl_rx_tag);
	if (error) {
                device_printf(sc->rl_dev,
		    "failed to create Rx memory block DMA tag.\n");
		goto fail;
	}
	/* Create DMA tag for Tx buffer. */
	error = bus_dma_tag_create(sc->rl_parent_tag,	/* parent */
	    RL_TX_8139_BUF_ALIGN, 0,	/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES, 1,		/* maxsize, nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->rl_cdata.rl_tx_tag);
	if (error) {
                device_printf(sc->rl_dev, "failed to create Tx DMA tag.\n");
		goto fail;
	}

	/*
	 * Allocate DMA'able memory and load DMA map for Rx memory block.
	 */
	error = bus_dmamem_alloc(sc->rl_cdata.rl_rx_tag,
	    (void **)&sc->rl_cdata.rl_rx_buf, BUS_DMA_WAITOK |
	    BUS_DMA_COHERENT | BUS_DMA_ZERO, &sc->rl_cdata.rl_rx_dmamap);
	if (error != 0) {
		device_printf(sc->rl_dev,
		    "failed to allocate Rx DMA memory block.\n");
		goto fail;
	}
	ctx.rl_busaddr = 0;
	error = bus_dmamap_load(sc->rl_cdata.rl_rx_tag,
	    sc->rl_cdata.rl_rx_dmamap, sc->rl_cdata.rl_rx_buf,
	    RL_RXBUFLEN + RL_RX_8139_BUF_GUARD_SZ, rl_dmamap_cb, &ctx,
	    BUS_DMA_NOWAIT);
	if (error != 0 || ctx.rl_busaddr == 0) {
		device_printf(sc->rl_dev,
		    "could not load Rx DMA memory block.\n");
		goto fail;
	}
	sc->rl_cdata.rl_rx_buf_paddr = ctx.rl_busaddr;

	/* Create DMA maps for Tx buffers. */
	for (i = 0; i < RL_TX_LIST_CNT; i++) {
		sc->rl_cdata.rl_tx_chain[i] = NULL;
		sc->rl_cdata.rl_tx_dmamap[i] = NULL;
		error = bus_dmamap_create(sc->rl_cdata.rl_tx_tag, 0,
		    &sc->rl_cdata.rl_tx_dmamap[i]);
		if (error != 0) {
			device_printf(sc->rl_dev,
			    "could not create Tx dmamap.\n");
			goto fail;
		}
	}

	/* Leave a few bytes before the start of the RX ring buffer. */
	sc->rl_cdata.rl_rx_buf_ptr = sc->rl_cdata.rl_rx_buf;
	sc->rl_cdata.rl_rx_buf += RL_RX_8139_BUF_RESERVE;

fail:
	return (error);
}