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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct ena_adapter {int /*<<< orphan*/  dma_width; } ;
struct TYPE_3__ {scalar_t__ paddr; int /*<<< orphan*/ * vaddr; int /*<<< orphan*/ * tag; int /*<<< orphan*/  map; } ;
typedef  TYPE_1__ ena_mem_handle_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int bus_size_t ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_ZERO ; 
 scalar_t__ BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  ENA_ALERT ; 
 scalar_t__ ENA_DMA_BIT_MASK (int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ *,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 struct ena_adapter* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_dmamap_callback ; 
 int /*<<< orphan*/  ena_trace (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ unlikely (int) ; 

int
ena_dma_alloc(device_t dmadev, bus_size_t size,
    ena_mem_handle_t *dma , int mapflags)
{
	struct ena_adapter* adapter = device_get_softc(dmadev);
	uint32_t maxsize;
	uint64_t dma_space_addr;
	int error;

	maxsize = ((size - 1) / PAGE_SIZE + 1) * PAGE_SIZE;

	dma_space_addr = ENA_DMA_BIT_MASK(adapter->dma_width);
	if (unlikely(dma_space_addr == 0))
		dma_space_addr = BUS_SPACE_MAXADDR;

	error = bus_dma_tag_create(bus_get_dma_tag(dmadev), /* parent */
	    8, 0,	      /* alignment, bounds 		*/
	    dma_space_addr,   /* lowaddr of exclusion window	*/
	    BUS_SPACE_MAXADDR,/* highaddr of exclusion window	*/
	    NULL, NULL,	      /* filter, filterarg 		*/
	    maxsize,	      /* maxsize 			*/
	    1,		      /* nsegments 			*/
	    maxsize,	      /* maxsegsize 			*/
	    BUS_DMA_ALLOCNOW, /* flags 				*/
	    NULL,	      /* lockfunc 			*/
	    NULL,	      /* lockarg 			*/
	    &dma->tag);
	if (unlikely(error != 0)) {
		ena_trace(ENA_ALERT, "bus_dma_tag_create failed: %d\n", error);
		goto fail_tag;
	}

	error = bus_dmamem_alloc(dma->tag, (void**) &dma->vaddr,
	    BUS_DMA_COHERENT | BUS_DMA_ZERO, &dma->map);
	if (unlikely(error != 0)) {
		ena_trace(ENA_ALERT, "bus_dmamem_alloc(%ju) failed: %d\n",
		    (uintmax_t)size, error);
		goto fail_map_create;
	}

	dma->paddr = 0;
	error = bus_dmamap_load(dma->tag, dma->map, dma->vaddr,
	    size, ena_dmamap_callback, &dma->paddr, mapflags);
	if (unlikely((error != 0) || (dma->paddr == 0))) {
		ena_trace(ENA_ALERT, ": bus_dmamap_load failed: %d\n", error);
		goto fail_map_load;
	}

	bus_dmamap_sync(dma->tag, dma->map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	return (0);

fail_map_load:
	bus_dmamem_free(dma->tag, dma->vaddr, dma->map);
fail_map_create:
	bus_dma_tag_destroy(dma->tag);
fail_tag:
	dma->tag = NULL;
	dma->vaddr = NULL;
	dma->paddr = 0;

	return (error);
}