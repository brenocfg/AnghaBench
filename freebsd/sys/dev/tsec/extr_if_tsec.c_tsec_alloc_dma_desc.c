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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 int BUS_DMA_NOWAIT ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int ENXIO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int bus_dma_tag_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  tsec_map_dma_addr ; 

__attribute__((used)) static int
tsec_alloc_dma_desc(device_t dev, bus_dma_tag_t *dtag, bus_dmamap_t *dmap,
    bus_size_t dsize, void **vaddr, void *raddr, const char *dname)
{
	int error;

	/* Allocate a busdma tag and DMA safe memory for TX/RX descriptors. */
	error = bus_dma_tag_create(NULL,	/* parent */
	    PAGE_SIZE, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,		/* lowaddr */
	    BUS_SPACE_MAXADDR,			/* highaddr */
	    NULL, NULL,				/* filtfunc, filtfuncarg */
	    dsize, 1,				/* maxsize, nsegments */
	    dsize, 0,				/* maxsegsz, flags */
	    NULL, NULL,				/* lockfunc, lockfuncarg */
	    dtag);				/* dmat */

	if (error) {
		device_printf(dev, "failed to allocate busdma %s tag\n",
		    dname);
		(*vaddr) = NULL;
		return (ENXIO);
	}

	error = bus_dmamem_alloc(*dtag, vaddr, BUS_DMA_NOWAIT | BUS_DMA_ZERO,
	    dmap);
	if (error) {
		device_printf(dev, "failed to allocate %s DMA safe memory\n",
		    dname);
		bus_dma_tag_destroy(*dtag);
		(*vaddr) = NULL;
		return (ENXIO);
	}

	error = bus_dmamap_load(*dtag, *dmap, *vaddr, dsize,
	    tsec_map_dma_addr, raddr, BUS_DMA_NOWAIT);
	if (error) {
		device_printf(dev, "cannot get address of the %s "
		    "descriptors\n", dname);
		bus_dmamem_free(*dtag, *vaddr, *dmap);
		bus_dma_tag_destroy(*dtag);
		(*vaddr) = NULL;
		return (ENXIO);
	}

	return (0);
}