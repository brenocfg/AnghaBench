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
struct linux_dma_obj {int /*<<< orphan*/  dmamap; } ;
struct dma_pool {int /*<<< orphan*/  pool_dmat; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_POOL_LOCK (struct dma_pool*) ; 
 int /*<<< orphan*/  DMA_POOL_UNLOCK (struct dma_pool*) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dma_pool_obj_dtor(void *mem, int size, void *arg)
{
	struct linux_dma_obj *obj = mem;
	struct dma_pool *pool = arg;

	DMA_POOL_LOCK(pool);
	bus_dmamap_unload(pool->pool_dmat, obj->dmamap);
	DMA_POOL_UNLOCK(pool);
}