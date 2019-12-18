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
struct dma_device {int dummy; } ;
struct ccp_device {int /*<<< orphan*/  dma_cmd_cache; int /*<<< orphan*/  dma_desc_cache; struct dma_device dma_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_device_unregister (struct dma_device*) ; 
 int /*<<< orphan*/  dmaengine ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 

void ccp_dmaengine_unregister(struct ccp_device *ccp)
{
	struct dma_device *dma_dev = &ccp->dma_dev;

	if (!dmaengine)
		return;

	dma_async_device_unregister(dma_dev);

	kmem_cache_destroy(ccp->dma_desc_cache);
	kmem_cache_destroy(ccp->dma_cmd_cache);
}