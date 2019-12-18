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
 int /*<<< orphan*/  cache_op (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wbinv_set_zero_range ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 

void arch_dma_prep_coherent(struct page *page, size_t size)
{
	cache_op(page_to_phys(page), size, dma_wbinv_set_zero_range);
}