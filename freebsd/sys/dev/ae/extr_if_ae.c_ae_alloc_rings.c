#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bus_addr_t ;
struct TYPE_3__ {scalar_t__ rxd_base_dma; int /*<<< orphan*/ * rxd_base; scalar_t__ dma_rxd_busaddr; int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_rxd_map; int /*<<< orphan*/  dma_rxd_tag; scalar_t__ dma_txs_busaddr; scalar_t__ txs_base; int /*<<< orphan*/  dma_txs_map; int /*<<< orphan*/  dma_txs_tag; scalar_t__ dma_txd_busaddr; scalar_t__ txd_base; int /*<<< orphan*/  dma_txd_map; int /*<<< orphan*/  dma_txd_tag; int /*<<< orphan*/  dma_parent_tag; } ;
typedef  TYPE_1__ ae_softc_t ;
typedef  int /*<<< orphan*/  ae_rxd_t ;

/* Variables and functions */
 int AE_RXD_COUNT_DEFAULT ; 
 int AE_RXD_PADDING ; 
 int AE_TXD_BUFSIZE_DEFAULT ; 
 int AE_TXS_COUNT_DEFAULT ; 
 int BUS_DMA_COHERENT ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  ae_dmamap_cb ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ae_alloc_rings(ae_softc_t *sc)
{
	bus_addr_t busaddr;
	int error;

	/*
	 * Create parent DMA tag.
	 */
	error = bus_dma_tag_create(bus_get_dma_tag(sc->dev),
	    1, 0, BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR,
	    NULL, NULL, BUS_SPACE_MAXSIZE_32BIT, 0,
	    BUS_SPACE_MAXSIZE_32BIT, 0, NULL, NULL,
	    &sc->dma_parent_tag);
	if (error != 0) {
		device_printf(sc->dev, "could not creare parent DMA tag.\n");
		return (error);
	}

	/*
	 * Create DMA tag for TxD.
	 */
	error = bus_dma_tag_create(sc->dma_parent_tag,
	    8, 0, BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR,
	    NULL, NULL, AE_TXD_BUFSIZE_DEFAULT, 1,
	    AE_TXD_BUFSIZE_DEFAULT, 0, NULL, NULL,
	    &sc->dma_txd_tag);
	if (error != 0) {
		device_printf(sc->dev, "could not creare TxD DMA tag.\n");
		return (error);
	}

	/*
	 * Create DMA tag for TxS.
	 */
	error = bus_dma_tag_create(sc->dma_parent_tag,
	    8, 0, BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR,
	    NULL, NULL, AE_TXS_COUNT_DEFAULT * 4, 1,
	    AE_TXS_COUNT_DEFAULT * 4, 0, NULL, NULL,
	    &sc->dma_txs_tag);
	if (error != 0) {
		device_printf(sc->dev, "could not creare TxS DMA tag.\n");
		return (error);
	}

	/*
	 * Create DMA tag for RxD.
	 */
	error = bus_dma_tag_create(sc->dma_parent_tag,
	    128, 0, BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR,
	    NULL, NULL, AE_RXD_COUNT_DEFAULT * 1536 + AE_RXD_PADDING, 1,
	    AE_RXD_COUNT_DEFAULT * 1536 + AE_RXD_PADDING, 0, NULL, NULL,
	    &sc->dma_rxd_tag);
	if (error != 0) {
		device_printf(sc->dev, "could not creare TxS DMA tag.\n");
		return (error);
	}

	/*
	 * Allocate TxD DMA memory.
	 */
	error = bus_dmamem_alloc(sc->dma_txd_tag, (void **)&sc->txd_base,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &sc->dma_txd_map);
	if (error != 0) {
		device_printf(sc->dev,
		    "could not allocate DMA memory for TxD ring.\n");
		return (error);
	}
	error = bus_dmamap_load(sc->dma_txd_tag, sc->dma_txd_map, sc->txd_base,
	    AE_TXD_BUFSIZE_DEFAULT, ae_dmamap_cb, &busaddr, BUS_DMA_NOWAIT);
	if (error != 0 || busaddr == 0) {
		device_printf(sc->dev,
		    "could not load DMA map for TxD ring.\n");
		return (error);
	}
	sc->dma_txd_busaddr = busaddr;

	/*
	 * Allocate TxS DMA memory.
	 */
	error = bus_dmamem_alloc(sc->dma_txs_tag, (void **)&sc->txs_base,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &sc->dma_txs_map);
	if (error != 0) {
		device_printf(sc->dev,
		    "could not allocate DMA memory for TxS ring.\n");
		return (error);
	}
	error = bus_dmamap_load(sc->dma_txs_tag, sc->dma_txs_map, sc->txs_base,
	    AE_TXS_COUNT_DEFAULT * 4, ae_dmamap_cb, &busaddr, BUS_DMA_NOWAIT);
	if (error != 0 || busaddr == 0) {
		device_printf(sc->dev,
		    "could not load DMA map for TxS ring.\n");
		return (error);
	}
	sc->dma_txs_busaddr = busaddr;

	/*
	 * Allocate RxD DMA memory.
	 */
	error = bus_dmamem_alloc(sc->dma_rxd_tag, (void **)&sc->rxd_base_dma,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO | BUS_DMA_COHERENT,
	    &sc->dma_rxd_map);
	if (error != 0) {
		device_printf(sc->dev,
		    "could not allocate DMA memory for RxD ring.\n");
		return (error);
	}
	error = bus_dmamap_load(sc->dma_rxd_tag, sc->dma_rxd_map,
	    sc->rxd_base_dma, AE_RXD_COUNT_DEFAULT * 1536 + AE_RXD_PADDING,
	    ae_dmamap_cb, &busaddr, BUS_DMA_NOWAIT);
	if (error != 0 || busaddr == 0) {
		device_printf(sc->dev,
		    "could not load DMA map for RxD ring.\n");
		return (error);
	}
	sc->dma_rxd_busaddr = busaddr + AE_RXD_PADDING;
	sc->rxd_base = (ae_rxd_t *)(sc->rxd_base_dma + AE_RXD_PADDING);

	return (0);
}