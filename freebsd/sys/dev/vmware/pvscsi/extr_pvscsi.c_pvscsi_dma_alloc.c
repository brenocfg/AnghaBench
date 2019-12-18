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
struct pvscsi_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  parent_dmat; } ;
struct pvscsi_dma {int /*<<< orphan*/  size; int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  map; int /*<<< orphan*/  tag; } ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int BUS_DMA_NOWAIT ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct pvscsi_dma*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pvscsi_dma_cb ; 
 int /*<<< orphan*/  pvscsi_dma_free (struct pvscsi_softc*,struct pvscsi_dma*) ; 

__attribute__((used)) static int
pvscsi_dma_alloc(struct pvscsi_softc *sc, struct pvscsi_dma *dma,
    bus_size_t size, bus_size_t alignment)
{
	int error;

	bzero(dma, sizeof(*dma));

	error = bus_dma_tag_create(sc->parent_dmat, alignment, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL, size, 1, size,
	    BUS_DMA_ALLOCNOW, NULL, NULL, &dma->tag);
	if (error) {
		device_printf(sc->dev, "error creating dma tag, error %d\n",
		    error);
		goto fail;
	}

	error = bus_dmamem_alloc(dma->tag, &dma->vaddr,
	    BUS_DMA_NOWAIT | BUS_DMA_ZERO, &dma->map);
	if (error) {
		device_printf(sc->dev, "error allocating dma mem, error %d\n",
		    error);
		goto fail;
	}

	error = bus_dmamap_load(dma->tag, dma->map, dma->vaddr, size,
	    pvscsi_dma_cb, &dma->paddr, BUS_DMA_NOWAIT);
	if (error) {
		device_printf(sc->dev, "error mapping dma mam, error %d\n",
		    error);
		goto fail;
	}

	dma->size = size;

fail:
	if (error) {
		pvscsi_dma_free(sc, dma);
	}
	return (error);
}