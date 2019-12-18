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
struct linux_dma_obj {void* vaddr; int /*<<< orphan*/  dma_addr; } ;
struct dma_pool {int /*<<< orphan*/  pool_zone; int /*<<< orphan*/  pool_ptree; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_POOL_LOCK (struct dma_pool*) ; 
 int /*<<< orphan*/  DMA_POOL_UNLOCK (struct dma_pool*) ; 
 scalar_t__ LINUX_DMA_PCTRIE_INSERT (int /*<<< orphan*/ *,struct linux_dma_obj*) ; 
 struct linux_dma_obj* uma_zalloc_arg (int /*<<< orphan*/ ,struct dma_pool*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree_arg (int /*<<< orphan*/ ,struct linux_dma_obj*,struct dma_pool*) ; 

void *
linux_dma_pool_alloc(struct dma_pool *pool, gfp_t mem_flags,
    dma_addr_t *handle)
{
	struct linux_dma_obj *obj;

	obj = uma_zalloc_arg(pool->pool_zone, pool, mem_flags);
	if (obj == NULL)
		return (NULL);

	DMA_POOL_LOCK(pool);
	if (LINUX_DMA_PCTRIE_INSERT(&pool->pool_ptree, obj) != 0) {
		DMA_POOL_UNLOCK(pool);
		uma_zfree_arg(pool->pool_zone, obj, pool);
		return (NULL);
	}
	DMA_POOL_UNLOCK(pool);

	*handle = obj->dma_addr;
	return (obj->vaddr);
}