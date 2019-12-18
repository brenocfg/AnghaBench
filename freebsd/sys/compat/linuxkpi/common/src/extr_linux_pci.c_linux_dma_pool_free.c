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
struct linux_dma_obj {int dummy; } ;
struct dma_pool {int /*<<< orphan*/  pool_zone; int /*<<< orphan*/  pool_ptree; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_POOL_LOCK (struct dma_pool*) ; 
 int /*<<< orphan*/  DMA_POOL_UNLOCK (struct dma_pool*) ; 
 struct linux_dma_obj* LINUX_DMA_PCTRIE_LOOKUP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINUX_DMA_PCTRIE_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree_arg (int /*<<< orphan*/ ,struct linux_dma_obj*,struct dma_pool*) ; 

void
linux_dma_pool_free(struct dma_pool *pool, void *vaddr, dma_addr_t dma_addr)
{
	struct linux_dma_obj *obj;

	DMA_POOL_LOCK(pool);
	obj = LINUX_DMA_PCTRIE_LOOKUP(&pool->pool_ptree, dma_addr);
	if (obj == NULL) {
		DMA_POOL_UNLOCK(pool);
		return;
	}
	LINUX_DMA_PCTRIE_REMOVE(&pool->pool_ptree, dma_addr);
	DMA_POOL_UNLOCK(pool);

	uma_zfree_arg(pool->pool_zone, obj, pool);
}