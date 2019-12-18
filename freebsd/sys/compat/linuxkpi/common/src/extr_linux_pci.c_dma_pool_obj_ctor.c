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
struct linux_dma_obj {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  dmamap; } ;
struct dma_pool {int /*<<< orphan*/  pool_entry_size; int /*<<< orphan*/  pool_dmat; } ;
struct TYPE_3__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  DMA_POOL_LOCK (struct dma_pool*) ; 
 int /*<<< orphan*/  DMA_POOL_UNLOCK (struct dma_pool*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int _bus_dmamap_load_phys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  vtophys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
dma_pool_obj_ctor(void *mem, int size, void *arg, int flags)
{
	struct linux_dma_obj *obj = mem;
	struct dma_pool *pool = arg;
	int error, nseg;
	bus_dma_segment_t seg;

	nseg = -1;
	DMA_POOL_LOCK(pool);
	error = _bus_dmamap_load_phys(pool->pool_dmat, obj->dmamap,
	    vtophys(obj->vaddr), pool->pool_entry_size, BUS_DMA_NOWAIT,
	    &seg, &nseg);
	DMA_POOL_UNLOCK(pool);
	if (error != 0) {
		return (error);
	}
	KASSERT(++nseg == 1, ("More than one segment (nseg=%d)", nseg));
	obj->dma_addr = seg.ds_addr;

	return (0);
}