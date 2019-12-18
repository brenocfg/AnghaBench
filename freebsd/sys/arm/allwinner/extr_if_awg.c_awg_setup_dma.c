#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ desc_ring_paddr; int /*<<< orphan*/  desc_map; int /*<<< orphan*/  desc_tag; TYPE_4__* buf_map; int /*<<< orphan*/  buf_tag; TYPE_5__* desc_ring; int /*<<< orphan*/  buf_spare_map; } ;
struct TYPE_7__ {scalar_t__ desc_ring_paddr; TYPE_1__* buf_map; int /*<<< orphan*/  buf_tag; scalar_t__ queued; TYPE_5__* desc_ring; int /*<<< orphan*/  desc_map; int /*<<< orphan*/  desc_tag; } ;
struct awg_softc {TYPE_3__ rx; TYPE_2__ tx; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_10__ {void* next; } ;
struct TYPE_9__ {int /*<<< orphan*/ * mbuf; int /*<<< orphan*/  map; } ;
struct TYPE_6__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int DESC_ALIGN ; 
 scalar_t__ DESC_OFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMAC_RX_DMA_LIST ; 
 int /*<<< orphan*/  EMAC_TX_DMA_LIST ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int RX_DESC_COUNT ; 
 int /*<<< orphan*/  RX_DESC_SIZE ; 
 int /*<<< orphan*/  RX_NEXT (int) ; 
 int TX_DESC_COUNT ; 
 int /*<<< orphan*/  TX_DESC_SIZE ; 
 int TX_MAX_SEGS ; 
 int /*<<< orphan*/  TX_NEXT (int) ; 
 int /*<<< orphan*/  WR4 (struct awg_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  awg_dmamap_cb ; 
 int awg_newbuf_rx (struct awg_softc*,int) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 struct awg_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 void* htole32 (scalar_t__) ; 

__attribute__((used)) static int
awg_setup_dma(device_t dev)
{
	struct awg_softc *sc;
	int error, i;

	sc = device_get_softc(dev);

	/* Setup TX ring */
	error = bus_dma_tag_create(
	    bus_get_dma_tag(dev),	/* Parent tag */
	    DESC_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    TX_DESC_SIZE, 1,		/* maxsize, nsegs */
	    TX_DESC_SIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->tx.desc_tag);
	if (error != 0) {
		device_printf(dev, "cannot create TX descriptor ring tag\n");
		return (error);
	}

	error = bus_dmamem_alloc(sc->tx.desc_tag, (void **)&sc->tx.desc_ring,
	    BUS_DMA_COHERENT | BUS_DMA_WAITOK | BUS_DMA_ZERO, &sc->tx.desc_map);
	if (error != 0) {
		device_printf(dev, "cannot allocate TX descriptor ring\n");
		return (error);
	}

	error = bus_dmamap_load(sc->tx.desc_tag, sc->tx.desc_map,
	    sc->tx.desc_ring, TX_DESC_SIZE, awg_dmamap_cb,
	    &sc->tx.desc_ring_paddr, 0);
	if (error != 0) {
		device_printf(dev, "cannot load TX descriptor ring\n");
		return (error);
	}

	for (i = 0; i < TX_DESC_COUNT; i++)
		sc->tx.desc_ring[i].next =
		    htole32(sc->tx.desc_ring_paddr + DESC_OFF(TX_NEXT(i)));

	error = bus_dma_tag_create(
	    bus_get_dma_tag(dev),	/* Parent tag */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES, TX_MAX_SEGS,	/* maxsize, nsegs */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->tx.buf_tag);
	if (error != 0) {
		device_printf(dev, "cannot create TX buffer tag\n");
		return (error);
	}

	sc->tx.queued = 0;
	for (i = 0; i < TX_DESC_COUNT; i++) {
		error = bus_dmamap_create(sc->tx.buf_tag, 0,
		    &sc->tx.buf_map[i].map);
		if (error != 0) {
			device_printf(dev, "cannot create TX buffer map\n");
			return (error);
		}
	}

	/* Setup RX ring */
	error = bus_dma_tag_create(
	    bus_get_dma_tag(dev),	/* Parent tag */
	    DESC_ALIGN, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    RX_DESC_SIZE, 1,		/* maxsize, nsegs */
	    RX_DESC_SIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->rx.desc_tag);
	if (error != 0) {
		device_printf(dev, "cannot create RX descriptor ring tag\n");
		return (error);
	}

	error = bus_dmamem_alloc(sc->rx.desc_tag, (void **)&sc->rx.desc_ring,
	    BUS_DMA_COHERENT | BUS_DMA_WAITOK | BUS_DMA_ZERO, &sc->rx.desc_map);
	if (error != 0) {
		device_printf(dev, "cannot allocate RX descriptor ring\n");
		return (error);
	}

	error = bus_dmamap_load(sc->rx.desc_tag, sc->rx.desc_map,
	    sc->rx.desc_ring, RX_DESC_SIZE, awg_dmamap_cb,
	    &sc->rx.desc_ring_paddr, 0);
	if (error != 0) {
		device_printf(dev, "cannot load RX descriptor ring\n");
		return (error);
	}

	error = bus_dma_tag_create(
	    bus_get_dma_tag(dev),	/* Parent tag */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES, 1,		/* maxsize, nsegs */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->rx.buf_tag);
	if (error != 0) {
		device_printf(dev, "cannot create RX buffer tag\n");
		return (error);
	}

	error = bus_dmamap_create(sc->rx.buf_tag, 0, &sc->rx.buf_spare_map);
	if (error != 0) {
		device_printf(dev,
		    "cannot create RX buffer spare map\n");
		return (error);
	}

	for (i = 0; i < RX_DESC_COUNT; i++) {
		sc->rx.desc_ring[i].next =
		    htole32(sc->rx.desc_ring_paddr + DESC_OFF(RX_NEXT(i)));

		error = bus_dmamap_create(sc->rx.buf_tag, 0,
		    &sc->rx.buf_map[i].map);
		if (error != 0) {
			device_printf(dev, "cannot create RX buffer map\n");
			return (error);
		}
		sc->rx.buf_map[i].mbuf = NULL;
		error = awg_newbuf_rx(sc, i);
		if (error != 0) {
			device_printf(dev, "cannot create RX buffer\n");
			return (error);
		}
	}
	bus_dmamap_sync(sc->rx.desc_tag, sc->rx.desc_map,
	    BUS_DMASYNC_PREWRITE);

	/* Write transmit and receive descriptor base address registers */
	WR4(sc, EMAC_TX_DMA_LIST, sc->tx.desc_ring_paddr);
	WR4(sc, EMAC_RX_DMA_LIST, sc->rx.desc_ring_paddr);

	return (0);
}