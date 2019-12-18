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
struct fwdma_alloc {void* v_addr; int /*<<< orphan*/  bus_addr; int /*<<< orphan*/  dma_map; int /*<<< orphan*/  dma_tag; } ;
struct firewire_comm {int /*<<< orphan*/  dmat; } ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  FW_GMTX (struct firewire_comm*) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 int /*<<< orphan*/  fwdma_map_cb ; 
 int /*<<< orphan*/  printf (char*) ; 

void *
fwdma_malloc(struct firewire_comm *fc, int alignment, bus_size_t size,
	struct fwdma_alloc *dma, int flag)
{
	int err;

	dma->v_addr = NULL;
	err = bus_dma_tag_create(
		/*parent*/ fc->dmat,
		/*alignment*/ alignment,
		/*boundary*/ 0,
		/*lowaddr*/ BUS_SPACE_MAXADDR_32BIT,
		/*highaddr*/ BUS_SPACE_MAXADDR,
		/*filter*/NULL, /*filterarg*/NULL,
		/*maxsize*/ size,
		/*nsegments*/ 1,
		/*maxsegsz*/ BUS_SPACE_MAXSIZE_32BIT,
		/*flags*/ BUS_DMA_ALLOCNOW,
		/*lockfunc*/busdma_lock_mutex,
		/*lockarg*/FW_GMTX(fc),
		&dma->dma_tag);
	if (err) {
		printf("fwdma_malloc: failed(1)\n");
		return (NULL);
	}

	err = bus_dmamem_alloc(dma->dma_tag, &dma->v_addr,
		flag, &dma->dma_map);
	if (err) {
		printf("fwdma_malloc: failed(2)\n");
		/* XXX destroy tag */
		return (NULL);
	}

	bus_dmamap_load(dma->dma_tag, dma->dma_map, dma->v_addr,
		size, fwdma_map_cb, &dma->bus_addr, /*flags*/0);

	return (dma->v_addr);
}