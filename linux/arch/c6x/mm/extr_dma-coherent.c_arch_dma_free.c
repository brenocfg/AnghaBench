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
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  __free_dma_pages (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_size ; 
 int get_count_order (size_t) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

void arch_dma_free(struct device *dev, size_t size, void *vaddr,
		dma_addr_t dma_handle, unsigned long attrs)
{
	int order;

	if (!dma_size || !size)
		return;

	order = get_count_order(((size - 1) >> PAGE_SHIFT) + 1);

	__free_dma_pages(virt_to_phys(vaddr), order);
}