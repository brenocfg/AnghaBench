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
struct sec_dma_mem {int dma_is_map; int /*<<< orphan*/ * dma_vaddr; int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  dma_map; } ;
struct sec_desc_map_info {int dummy; } ;
struct mbuf {int dummy; } ;
typedef  int bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  SEC_DMA_ALIGNMENT ; 
 int SEC_FREE_LT_CNT (struct sec_softc*) ; 
 int SEC_MAX_DMA_BLOCK_SIZE ; 
#define  SEC_MBUF 130 
#define  SEC_MEMORY 129 
#define  SEC_UIO 128 
 int bus_dma_tag_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,struct sec_desc_map_info*,int /*<<< orphan*/ ) ; 
 int bus_dmamap_load_mbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct sec_desc_map_info*,int /*<<< orphan*/ ) ; 
 int bus_dmamap_load_uio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct sec_desc_map_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int m_length (struct mbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sec_dma_map_desc_cb ; 
 int /*<<< orphan*/  sec_dma_map_desc_cb2 ; 

__attribute__((used)) static int
sec_desc_map_dma(struct sec_softc *sc, struct sec_dma_mem *dma_mem, void *mem,
    bus_size_t size, int type, struct sec_desc_map_info *sdmi)
{
	int error;

	if (dma_mem->dma_vaddr != NULL)
		return (EBUSY);

	switch (type) {
	case SEC_MEMORY:
		break;
	case SEC_UIO:
		size = SEC_FREE_LT_CNT(sc) * SEC_MAX_DMA_BLOCK_SIZE;
		break;
	case SEC_MBUF:
		size = m_length((struct mbuf*)mem, NULL);
		break;
	default:
		return (EINVAL);
	}

	error = bus_dma_tag_create(NULL,	/* parent */
		SEC_DMA_ALIGNMENT, 0,		/* alignment, boundary */
		BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
		BUS_SPACE_MAXADDR,		/* highaddr */
		NULL, NULL,			/* filtfunc, filtfuncarg */
		size,				/* maxsize */
		SEC_FREE_LT_CNT(sc),		/* nsegments */
		SEC_MAX_DMA_BLOCK_SIZE, 0,	/* maxsegsz, flags */
		NULL, NULL,			/* lockfunc, lockfuncarg */
		&(dma_mem->dma_tag));		/* dmat */

	if (error) {
		device_printf(sc->sc_dev, "failed to allocate busdma tag, error"
		    " %i!\n", error);
		dma_mem->dma_vaddr = NULL;
		return (error);
	}

	error = bus_dmamap_create(dma_mem->dma_tag, 0, &(dma_mem->dma_map));

	if (error) {
		device_printf(sc->sc_dev, "failed to create DMA map, error %i!"
		    "\n", error);
		bus_dma_tag_destroy(dma_mem->dma_tag);
		return (error);
	}

	switch (type) {
	case SEC_MEMORY:
		error = bus_dmamap_load(dma_mem->dma_tag, dma_mem->dma_map,
		    mem, size, sec_dma_map_desc_cb, sdmi, BUS_DMA_NOWAIT);
		break;
	case SEC_UIO:
		error = bus_dmamap_load_uio(dma_mem->dma_tag, dma_mem->dma_map,
		    mem, sec_dma_map_desc_cb2, sdmi, BUS_DMA_NOWAIT);
		break;
	case SEC_MBUF:
		error = bus_dmamap_load_mbuf(dma_mem->dma_tag, dma_mem->dma_map,
		    mem, sec_dma_map_desc_cb2, sdmi, BUS_DMA_NOWAIT);
		break;
	}

	if (error) {
		device_printf(sc->sc_dev, "cannot get address of the DMA"
		    " memory, error %i!\n", error);
		bus_dmamap_destroy(dma_mem->dma_tag, dma_mem->dma_map);
		bus_dma_tag_destroy(dma_mem->dma_tag);
		return (error);
	}

	dma_mem->dma_is_map = 1;
	dma_mem->dma_vaddr = mem;

	return (0);
}