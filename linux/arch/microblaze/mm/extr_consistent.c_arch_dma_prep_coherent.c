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
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  flush_dcache_range (scalar_t__,scalar_t__) ; 
 scalar_t__ page_to_phys (struct page*) ; 

void arch_dma_prep_coherent(struct page *page, size_t size)
{
	phys_addr_t paddr = page_to_phys(page);

	flush_dcache_range(paddr, paddr + size);
}