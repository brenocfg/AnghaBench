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
struct dma_pool {int type; int /*<<< orphan*/  dev_name; } ;

/* Variables and functions */
 int IS_UC ; 
 int IS_WC ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int set_pages_array_uc (struct page**,unsigned int) ; 
 int set_pages_array_wc (struct page**,unsigned int) ; 

__attribute__((used)) static int ttm_set_pages_caching(struct dma_pool *pool,
				 struct page **pages, unsigned cpages)
{
	int r = 0;
	/* Set page caching */
	if (pool->type & IS_UC) {
		r = set_pages_array_uc(pages, cpages);
		if (r)
			pr_err("%s: Failed to set %d pages to uc!\n",
			       pool->dev_name, cpages);
	}
	if (pool->type & IS_WC) {
		r = set_pages_array_wc(pages, cpages);
		if (r)
			pr_err("%s: Failed to set %d pages to wc!\n",
			       pool->dev_name, cpages);
	}
	return r;
}