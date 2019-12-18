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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_STATS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  pmap_kenter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_nqenter ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlb_range_demap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tte_list_global_lock ; 

void
pmap_qenter(vm_offset_t sva, vm_page_t *m, int count)
{
	vm_offset_t va;

	PMAP_STATS_INC(pmap_nqenter);
	va = sva;
	rw_wlock(&tte_list_global_lock);
	while (count-- > 0) {
		pmap_kenter(va, *m);
		va += PAGE_SIZE;
		m++;
	}
	rw_wunlock(&tte_list_global_lock);
	tlb_range_demap(kernel_pmap, sva, va);
}