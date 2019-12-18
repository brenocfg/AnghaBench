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
struct aic_softc {int dma_size; int /*<<< orphan*/  buf_base; int /*<<< orphan*/  buf_base_phys; int /*<<< orphan*/  dma_map; int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  aic_dmamap_cb ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
aic_dma_setup(struct aic_softc *sc)
{
	device_t dev;
	int err;

	dev = sc->dev;

	/* DMA buffer size. */
	sc->dma_size = 131072;

	/*
	 * Must use dma_size boundary as modulo feature required.
	 * Modulo feature allows setup circular buffer.
	 */
	err = bus_dma_tag_create(
	    bus_get_dma_tag(sc->dev),
	    4, sc->dma_size,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    sc->dma_size, 1,		/* maxsize, nsegments */
	    sc->dma_size, 0,		/* maxsegsize, flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->dma_tag);
	if (err) {
		device_printf(dev, "cannot create bus dma tag\n");
		return (-1);
	}

	err = bus_dmamem_alloc(sc->dma_tag, (void **)&sc->buf_base,
	    BUS_DMA_WAITOK | BUS_DMA_COHERENT, &sc->dma_map);
	if (err) {
		device_printf(dev, "cannot allocate memory\n");
		return (-1);
	}

	err = bus_dmamap_load(sc->dma_tag, sc->dma_map, sc->buf_base,
	    sc->dma_size, aic_dmamap_cb, &sc->buf_base_phys, BUS_DMA_WAITOK);
	if (err) {
		device_printf(dev, "cannot load DMA map\n");
		return (-1);
	}

	bzero(sc->buf_base, sc->dma_size);

	return (0);
}