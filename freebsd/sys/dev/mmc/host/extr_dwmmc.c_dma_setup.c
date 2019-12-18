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
struct idmac_desc {int dummy; } ;
struct dwmmc_softc {int desc_count; int /*<<< orphan*/  dev; int /*<<< orphan*/  buf_map; int /*<<< orphan*/  buf_tag; scalar_t__ desc_ring_paddr; TYPE_1__* desc_ring; int /*<<< orphan*/  desc_map; int /*<<< orphan*/  desc_tag; } ;
struct TYPE_2__ {scalar_t__ des3; scalar_t__ des1; int /*<<< orphan*/  des0; } ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  DES0_CH ; 
 int DESC_SIZE ; 
 int MMC_SECTOR_SIZE ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwmmc_get1paddr ; 

__attribute__((used)) static int
dma_setup(struct dwmmc_softc *sc)
{
	int error;
	int nidx;
	int idx;

	/*
	 * Set up TX descriptor ring, descriptors, and dma maps.
	 */
	error = bus_dma_tag_create(
	    bus_get_dma_tag(sc->dev),	/* Parent tag. */
	    4096, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    DESC_SIZE, 1, 		/* maxsize, nsegments */
	    DESC_SIZE,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->desc_tag);
	if (error != 0) {
		device_printf(sc->dev,
		    "could not create ring DMA tag.\n");
		return (1);
	}

	error = bus_dmamem_alloc(sc->desc_tag, (void**)&sc->desc_ring,
	    BUS_DMA_COHERENT | BUS_DMA_WAITOK | BUS_DMA_ZERO,
	    &sc->desc_map);
	if (error != 0) {
		device_printf(sc->dev,
		    "could not allocate descriptor ring.\n");
		return (1);
	}

	error = bus_dmamap_load(sc->desc_tag, sc->desc_map,
	    sc->desc_ring, DESC_SIZE, dwmmc_get1paddr,
	    &sc->desc_ring_paddr, 0);
	if (error != 0) {
		device_printf(sc->dev,
		    "could not load descriptor ring map.\n");
		return (1);
	}

	for (idx = 0; idx < sc->desc_count; idx++) {
		sc->desc_ring[idx].des0 = DES0_CH;
		sc->desc_ring[idx].des1 = 0;
		nidx = (idx + 1) % sc->desc_count;
		sc->desc_ring[idx].des3 = sc->desc_ring_paddr + \
		    (nidx * sizeof(struct idmac_desc));
	}

	error = bus_dma_tag_create(
	    bus_get_dma_tag(sc->dev),	/* Parent tag. */
	    4096, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    sc->desc_count * MMC_SECTOR_SIZE, /* maxsize */
	    sc->desc_count,		/* nsegments */
	    MMC_SECTOR_SIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->buf_tag);
	if (error != 0) {
		device_printf(sc->dev,
		    "could not create ring DMA tag.\n");
		return (1);
	}

	error = bus_dmamap_create(sc->buf_tag, 0,
	    &sc->buf_map);
	if (error != 0) {
		device_printf(sc->dev,
		    "could not create TX buffer DMA map.\n");
		return (1);
	}

	return (0);
}