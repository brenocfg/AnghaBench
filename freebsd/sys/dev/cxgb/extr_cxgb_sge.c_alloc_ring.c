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
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/ * bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; int /*<<< orphan*/ * parent_dmat; } ;
typedef  TYPE_1__ adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PAGE_SIZE ; 
 int TX_MAX_SEGS ; 
 size_t TX_MAX_SIZE ; 
 int /*<<< orphan*/  alloc_ring_cb ; 
 int bus_dma_tag_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (void*,size_t) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 void* malloc (size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
alloc_ring(adapter_t *sc, size_t nelem, size_t elem_size, size_t sw_size,
    bus_addr_t *phys, void *desc, void *sdesc, bus_dma_tag_t *tag,
    bus_dmamap_t *map, bus_dma_tag_t parent_entry_tag, bus_dma_tag_t *entry_tag)
{
	size_t len = nelem * elem_size;
	void *s = NULL;
	void *p = NULL;
	int err;

	if ((err = bus_dma_tag_create(sc->parent_dmat, PAGE_SIZE, 0,
				      BUS_SPACE_MAXADDR_32BIT,
				      BUS_SPACE_MAXADDR, NULL, NULL, len, 1,
				      len, 0, NULL, NULL, tag)) != 0) {
		device_printf(sc->dev, "Cannot allocate descriptor tag\n");
		return (ENOMEM);
	}

	if ((err = bus_dmamem_alloc(*tag, (void **)&p, BUS_DMA_NOWAIT,
				    map)) != 0) {
		device_printf(sc->dev, "Cannot allocate descriptor memory\n");
		return (ENOMEM);
	}

	bus_dmamap_load(*tag, *map, p, len, alloc_ring_cb, phys, 0);
	bzero(p, len);
	*(void **)desc = p;

	if (sw_size) {
		len = nelem * sw_size;
		s = malloc(len, M_DEVBUF, M_WAITOK|M_ZERO);
		*(void **)sdesc = s;
	}
	if (parent_entry_tag == NULL)
		return (0);
	    
	if ((err = bus_dma_tag_create(parent_entry_tag, 1, 0,
				      BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR,
		                      NULL, NULL, TX_MAX_SIZE, TX_MAX_SEGS,
				      TX_MAX_SIZE, BUS_DMA_ALLOCNOW,
		                      NULL, NULL, entry_tag)) != 0) {
		device_printf(sc->dev, "Cannot allocate descriptor entry tag\n");
		return (ENOMEM);
	}
	return (0);
}