#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  parent_dmat; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ mxge_softc_t ;
struct TYPE_6__ {int /*<<< orphan*/  dmat; int /*<<< orphan*/  map; int /*<<< orphan*/  addr; int /*<<< orphan*/  bus_addr; } ;
typedef  TYPE_2__ mxge_dma_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int bus_size_t ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mxge_dmamap_callback ; 

__attribute__((used)) static int
mxge_dma_alloc(mxge_softc_t *sc, mxge_dma_t *dma, size_t bytes,
		   bus_size_t alignment)
{
	int err;
	device_t dev = sc->dev;
	bus_size_t boundary, maxsegsize;

	if (bytes > 4096 && alignment == 4096) {
		boundary = 0;
		maxsegsize = bytes;
	} else {
		boundary = 4096;
		maxsegsize = 4096;
	}

	/* allocate DMAable memory tags */
	err = bus_dma_tag_create(sc->parent_dmat,	/* parent */
				 alignment,		/* alignment */
				 boundary,		/* boundary */
				 BUS_SPACE_MAXADDR,	/* low */
				 BUS_SPACE_MAXADDR,	/* high */
				 NULL, NULL,		/* filter */
				 bytes,			/* maxsize */
				 1,			/* num segs */
				 maxsegsize,		/* maxsegsize */
				 BUS_DMA_COHERENT,	/* flags */
				 NULL, NULL,		/* lock */
				 &dma->dmat);		/* tag */
	if (err != 0) {
		device_printf(dev, "couldn't alloc tag (err = %d)\n", err);
		return err;
	}

	/* allocate DMAable memory & map */
	err = bus_dmamem_alloc(dma->dmat, &dma->addr,
			       (BUS_DMA_WAITOK | BUS_DMA_COHERENT
				| BUS_DMA_ZERO),  &dma->map);
	if (err != 0) {
		device_printf(dev, "couldn't alloc mem (err = %d)\n", err);
		goto abort_with_dmat;
	}

	/* load the memory */
	err = bus_dmamap_load(dma->dmat, dma->map, dma->addr, bytes,
			      mxge_dmamap_callback,
			      (void *)&dma->bus_addr, 0);
	if (err != 0) {
		device_printf(dev, "couldn't load map (err = %d)\n", err);
		goto abort_with_mem;
	}
	return 0;

abort_with_mem:
	bus_dmamem_free(dma->dmat, dma->addr, dma->map);
abort_with_dmat:
	(void)bus_dma_tag_destroy(dma->dmat);
	return err;
}