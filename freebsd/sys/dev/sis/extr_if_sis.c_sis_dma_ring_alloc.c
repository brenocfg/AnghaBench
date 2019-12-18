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
typedef  int /*<<< orphan*/  uint8_t ;
struct sis_softc {int /*<<< orphan*/  sis_dev; int /*<<< orphan*/  sis_parent_tag; } ;
struct sis_dmamap_arg {scalar_t__ sis_busaddr; } ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_NOWAIT ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int ENOMEM ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sis_dmamap_arg*,int) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  sis_dmamap_cb ; 

__attribute__((used)) static int
sis_dma_ring_alloc(struct sis_softc *sc, bus_size_t alignment,
    bus_size_t maxsize, bus_dma_tag_t *tag, uint8_t **ring, bus_dmamap_t *map,
    bus_addr_t *paddr, const char *msg)
{
	struct sis_dmamap_arg	ctx;
	int			error;

	error = bus_dma_tag_create(sc->sis_parent_tag, alignment, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL, maxsize, 1,
	    maxsize, 0, NULL, NULL, tag);
	if (error != 0) {
		device_printf(sc->sis_dev,
		    "could not create %s dma tag\n", msg);
		return (ENOMEM);
	}
	/* Allocate DMA'able memory for ring. */
	error = bus_dmamem_alloc(*tag, (void **)ring,
	    BUS_DMA_NOWAIT | BUS_DMA_ZERO | BUS_DMA_COHERENT, map);
	if (error != 0) {
		device_printf(sc->sis_dev,
		    "could not allocate DMA'able memory for %s\n", msg);
		return (ENOMEM);
	}
	/* Load the address of the ring. */
	ctx.sis_busaddr = 0;
	error = bus_dmamap_load(*tag, *map, *ring, maxsize, sis_dmamap_cb,
	    &ctx, BUS_DMA_NOWAIT);
	if (error != 0) {
		device_printf(sc->sis_dev,
		    "could not load DMA'able memory for %s\n", msg);
		return (ENOMEM);
	}
	*paddr = ctx.sis_busaddr;
	return (0);
}