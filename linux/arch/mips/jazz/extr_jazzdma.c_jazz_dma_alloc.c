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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MAPPING_ERROR ; 
 void* dma_direct_alloc_pages (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dma_direct_free_pages (struct device*,size_t,void*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  vdma_alloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

__attribute__((used)) static void *jazz_dma_alloc(struct device *dev, size_t size,
		dma_addr_t *dma_handle, gfp_t gfp, unsigned long attrs)
{
	void *ret;

	ret = dma_direct_alloc_pages(dev, size, dma_handle, gfp, attrs);
	if (!ret)
		return NULL;

	*dma_handle = vdma_alloc(virt_to_phys(ret), size);
	if (*dma_handle == DMA_MAPPING_ERROR) {
		dma_direct_free_pages(dev, size, ret, *dma_handle, attrs);
		return NULL;
	}

	return ret;
}