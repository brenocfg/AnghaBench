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
struct linux_dma_priv {int dummy; } ;
struct linux_dma_obj {int /*<<< orphan*/  dmamap; int /*<<< orphan*/  vaddr; } ;
struct dma_pool {int /*<<< orphan*/  pool_dmat; TYPE_1__* pool_device; } ;
struct TYPE_2__ {struct linux_dma_priv* dma_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_dma_obj_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct linux_dma_obj*) ; 

__attribute__((used)) static void
dma_pool_obj_release(void *arg, void **store, int count)
{
	struct dma_pool *pool = arg;
	struct linux_dma_priv *priv;
	struct linux_dma_obj *obj;
	int i;

	priv = pool->pool_device->dma_priv;
	for (i = 0; i < count; i++) {
		obj = store[i];
		bus_dmamem_free(pool->pool_dmat, obj->vaddr, obj->dmamap);
		uma_zfree(linux_dma_obj_zone, obj);
	}
}