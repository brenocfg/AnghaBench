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
struct scatterlist {int dummy; } ;
struct page {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SIZE ; 
 int __GFP_ZERO ; 
 struct page* alloc_pages (int,int) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mthca_alloc_icm_pages(struct scatterlist *mem, int order, gfp_t gfp_mask)
{
	struct page *page;

	/*
	 * Use __GFP_ZERO because buggy firmware assumes ICM pages are
	 * cleared, and subtle failures are seen if they aren't.
	 */
	page = alloc_pages(gfp_mask | __GFP_ZERO, order);
	if (!page)
		return -ENOMEM;

	sg_set_page(mem, page, PAGE_SIZE << order, 0);
	return 0;
}