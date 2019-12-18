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
struct page {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  __dma_clear_buffer (struct page*,size_t,int) ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long get_order (size_t) ; 
 int /*<<< orphan*/  split_page (struct page*,unsigned long) ; 

__attribute__((used)) static struct page *__dma_alloc_buffer(struct device *dev, size_t size,
				       gfp_t gfp, int coherent_flag)
{
	unsigned long order = get_order(size);
	struct page *page, *p, *e;

	page = alloc_pages(gfp, order);
	if (!page)
		return NULL;

	/*
	 * Now split the huge page and free the excess pages
	 */
	split_page(page, order);
	for (p = page + (size >> PAGE_SHIFT), e = page + (1 << order); p < e; p++)
		__free_page(p);

	__dma_clear_buffer(page, size, coherent_flag);

	return page;
}