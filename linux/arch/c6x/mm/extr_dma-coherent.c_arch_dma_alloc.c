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
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  __alloc_dma_pages (int) ; 
 int /*<<< orphan*/  dma_size ; 
 int get_count_order (size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 void* phys_to_virt (int /*<<< orphan*/ ) ; 

void *arch_dma_alloc(struct device *dev, size_t size, dma_addr_t *handle,
		gfp_t gfp, unsigned long attrs)
{
	void *ret;
	u32 paddr;
	int order;

	if (!dma_size || !size)
		return NULL;

	order = get_count_order(((size - 1) >> PAGE_SHIFT) + 1);

	paddr = __alloc_dma_pages(order);

	if (handle)
		*handle = paddr;

	if (!paddr)
		return NULL;

	ret = phys_to_virt(paddr);
	memset(ret, 0, 1 << order);
	return ret;
}