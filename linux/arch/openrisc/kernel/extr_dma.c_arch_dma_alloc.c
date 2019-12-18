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
typedef  int gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __pa (void*) ; 
 void* alloc_pages_exact (size_t,int) ; 
 int /*<<< orphan*/  free_pages_exact (void*,size_t) ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/  set_nocache_walk_ops ; 
 scalar_t__ walk_page_range (int /*<<< orphan*/ *,unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void *
arch_dma_alloc(struct device *dev, size_t size, dma_addr_t *dma_handle,
		gfp_t gfp, unsigned long attrs)
{
	unsigned long va;
	void *page;

	page = alloc_pages_exact(size, gfp | __GFP_ZERO);
	if (!page)
		return NULL;

	/* This gives us the real physical address of the first page. */
	*dma_handle = __pa(page);

	va = (unsigned long)page;

	/*
	 * We need to iterate through the pages, clearing the dcache for
	 * them and setting the cache-inhibit bit.
	 */
	if (walk_page_range(&init_mm, va, va + size, &set_nocache_walk_ops,
			NULL)) {
		free_pages_exact(page, size);
		return NULL;
	}

	return (void *)va;
}