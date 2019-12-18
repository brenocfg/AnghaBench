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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PTE_G ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  mips_dcache_wbinv_range_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_invalidate_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
pmap_kremove(vm_offset_t va)
{
	pt_entry_t *pte;

	/*
	 * Write back all caches from the page being destroyed
	 */
	mips_dcache_wbinv_range_index(va, PAGE_SIZE);

	pte = pmap_pte(kernel_pmap, va);
	*pte = PTE_G;
	pmap_invalidate_page(kernel_pmap, va);
}