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
struct sec_softc {int /*<<< orphan*/  sc_dev; } ;
struct sec_dma_mem {int /*<<< orphan*/ * dma_vaddr; int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  dma_map; scalar_t__ dma_is_map; } ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int BUS_DMA_NOWAIT ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int EBUSY ; 
 int /*<<< orphan*/  SEC_DMA_ALIGNMENT ; 
 int bus_dma_tag_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sec_dma_mem*,int) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sec_alloc_dma_mem_cb ; 

__attribute__((used)) static int
sec_alloc_dma_mem(struct sec_softc *sc, struct sec_dma_mem *dma_mem,
    bus_size_t size)
{
	int error;

	if (dma_mem->dma_vaddr != NULL)
		return (EBUSY);

	error = bus_dma_tag_create(NULL,	/* parent */
		SEC_DMA_ALIGNMENT, 0,		/* alignment, boundary */
		BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
		BUS_SPACE_MAXADDR,		/* highaddr */
		NULL, NULL,			/* filtfunc, filtfuncarg */
		size, 1,			/* maxsize, nsegments */
		size, 0,			/* maxsegsz, flags */
		NULL, NULL,			/* lockfunc, lockfuncarg */
		&(dma_mem->dma_tag));		/* dmat */

	if (error) {
		device_printf(sc->sc_dev, "failed to allocate busdma tag, error"
		    " %i!\n", error);
		goto err1;
	}

	error = bus_dmamem_alloc(dma_mem->dma_tag, &(dma_mem->dma_vaddr),
	    BUS_DMA_NOWAIT | BUS_DMA_ZERO, &(dma_mem->dma_map));

	if (error) {
		device_printf(sc->sc_dev, "failed to allocate DMA safe"
		    " memory, error %i!\n", error);
		goto err2;
	}

	error = bus_dmamap_load(dma_mem->dma_tag, dma_mem->dma_map,
		    dma_mem->dma_vaddr, size, sec_alloc_dma_mem_cb, dma_mem,
		    BUS_DMA_NOWAIT);

	if (error) {
		device_printf(sc->sc_dev, "cannot get address of the DMA"
		    " memory, error %i\n", error);
		goto err3;
	}

	dma_mem->dma_is_map = 0;
	return (0);

err3:
	bus_dmamem_free(dma_mem->dma_tag, dma_mem->dma_vaddr, dma_mem->dma_map);
err2:
	bus_dma_tag_destroy(dma_mem->dma_tag);
err1:
	dma_mem->dma_vaddr = NULL;
	return(error);
}