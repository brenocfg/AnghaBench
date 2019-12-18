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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  bge_parent_tag; } ;
struct bge_softc {int bge_flags; int /*<<< orphan*/  bge_dev; TYPE_1__ bge_cdata; } ;
struct bge_dmamap_arg {scalar_t__ bge_busaddr; } ;
typedef  scalar_t__ bus_size_t ;
typedef  int /*<<< orphan*/ * bus_dmamap_t ;
typedef  int /*<<< orphan*/ * bus_dma_tag_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 scalar_t__ BGE_ADDR_HI (scalar_t__) ; 
 int BGE_FLAG_4G_BNDRY_BUG ; 
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_NOWAIT ; 
 int BUS_DMA_ZERO ; 
 scalar_t__ BUS_SPACE_MAXADDR ; 
 scalar_t__ BUS_SPACE_MAXADDR_32BIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  bge_dma_map_addr ; 
 scalar_t__ bootverbose ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,struct bge_dmamap_arg*,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ *,void**,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int
bge_dma_ring_alloc(struct bge_softc *sc, bus_size_t alignment,
    bus_size_t maxsize, bus_dma_tag_t *tag, uint8_t **ring, bus_dmamap_t *map,
    bus_addr_t *paddr, const char *msg)
{
	struct bge_dmamap_arg ctx;
	bus_addr_t lowaddr;
	bus_size_t ring_end;
	int error;

	lowaddr = BUS_SPACE_MAXADDR;
again:
	error = bus_dma_tag_create(sc->bge_cdata.bge_parent_tag,
	    alignment, 0, lowaddr, BUS_SPACE_MAXADDR, NULL,
	    NULL, maxsize, 1, maxsize, 0, NULL, NULL, tag);
	if (error != 0) {
		device_printf(sc->bge_dev,
		    "could not create %s dma tag\n", msg);
		return (ENOMEM);
	}
	/* Allocate DMA'able memory for ring. */
	error = bus_dmamem_alloc(*tag, (void **)ring,
	    BUS_DMA_NOWAIT | BUS_DMA_ZERO | BUS_DMA_COHERENT, map);
	if (error != 0) {
		device_printf(sc->bge_dev,
		    "could not allocate DMA'able memory for %s\n", msg);
		return (ENOMEM);
	}
	/* Load the address of the ring. */
	ctx.bge_busaddr = 0;
	error = bus_dmamap_load(*tag, *map, *ring, maxsize, bge_dma_map_addr,
	    &ctx, BUS_DMA_NOWAIT);
	if (error != 0) {
		device_printf(sc->bge_dev,
		    "could not load DMA'able memory for %s\n", msg);
		return (ENOMEM);
	}
	*paddr = ctx.bge_busaddr;
	ring_end = *paddr + maxsize;
	if ((sc->bge_flags & BGE_FLAG_4G_BNDRY_BUG) != 0 &&
	    BGE_ADDR_HI(*paddr) != BGE_ADDR_HI(ring_end)) {
		/*
		 * 4GB boundary crossed.  Limit maximum allowable DMA
		 * address space to 32bit and try again.
		 */
		bus_dmamap_unload(*tag, *map);
		bus_dmamem_free(*tag, *ring, *map);
		bus_dma_tag_destroy(*tag);
		if (bootverbose)
			device_printf(sc->bge_dev, "4GB boundary crossed, "
			    "limit DMA address space to 32bit for %s\n", msg);
		*ring = NULL;
		*tag = NULL;
		*map = NULL;
		lowaddr = BUS_SPACE_MAXADDR_32BIT;
		goto again;
	}
	return (0);
}