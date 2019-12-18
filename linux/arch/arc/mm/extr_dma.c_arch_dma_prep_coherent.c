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

/* Variables and functions */
 int /*<<< orphan*/  dma_cache_wback_inv (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 

void arch_dma_prep_coherent(struct page *page, size_t size)
{
	/*
	 * Evict any existing L1 and/or L2 lines for the backing page
	 * in case it was used earlier as a normal "cached" page.
	 * Yeah this bit us - STAR 9000898266
	 *
	 * Although core does call flush_cache_vmap(), it gets kvaddr hence
	 * can't be used to efficiently flush L1 and/or L2 which need paddr
	 * Currently flush_cache_vmap nukes the L1 cache completely which
	 * will be optimized as a separate commit
	 */
	dma_cache_wback_inv(page_to_phys(page), size);
}