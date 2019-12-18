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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  pt2_entry_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PTE2_KRW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_preboot_vtopte2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte2_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pmap_preboot_map_pages(vm_paddr_t pa, vm_offset_t va, u_int num)
{
	u_int i;
	pt2_entry_t *pte2p;

	/* Map all the pages. */
	for (i = 0; i < num; i++) {
		pte2p = pmap_preboot_vtopte2(va);
		pte2_store(pte2p, PTE2_KRW(pa));
		va += PAGE_SIZE;
		pa += PAGE_SIZE;
	}
}