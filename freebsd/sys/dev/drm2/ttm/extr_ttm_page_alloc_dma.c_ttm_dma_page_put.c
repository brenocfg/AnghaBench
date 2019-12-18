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
struct dma_pool {int type; int /*<<< orphan*/  dev_name; } ;
struct dma_page {int /*<<< orphan*/  page_list; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int IS_CACHED ; 
 int /*<<< orphan*/  __ttm_dma_free_page (struct dma_pool*,struct dma_page*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ set_pages_array_wb (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ttm_dma_page_put(struct dma_pool *pool, struct dma_page *d_page)
{
	/* Don't set WB on WB page pool. */
	if (!(pool->type & IS_CACHED) && set_pages_array_wb(&d_page->p, 1))
		pr_err("%s: Failed to set %d pages to wb!\n",
		       pool->dev_name, 1);

	list_del(&d_page->page_list);
	__ttm_dma_free_page(pool, d_page);
}