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
 int /*<<< orphan*/  dma_cache_wback_inv (unsigned long,size_t) ; 
 scalar_t__ page_address (struct page*) ; 

void arch_dma_prep_coherent(struct page *page, size_t size)
{
	dma_cache_wback_inv((unsigned long)page_address(page), size);
}