#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  TYPE_2__* pmap_t ;
struct TYPE_4__ {scalar_t__ resident_count; } ;
struct TYPE_5__ {int /*<<< orphan*/  pm_l0_paddr; int /*<<< orphan*/  pm_cookie; int /*<<< orphan*/  pm_root; TYPE_1__ pm_stats; } ;

/* Variables and functions */
 int ASID_FIRST_AVAILABLE ; 
 int COOKIE_TO_ASID (int /*<<< orphan*/ ) ; 
 scalar_t__ COOKIE_TO_EPOCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 scalar_t__ asid_epoch ; 
 int /*<<< orphan*/  asid_set ; 
 int /*<<< orphan*/  asid_set_mutex ; 
 int asid_set_size ; 
 int /*<<< orphan*/  bit_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_free_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_unwire_noq (int /*<<< orphan*/ ) ; 
 int vm_radix_is_empty (int /*<<< orphan*/ *) ; 

void
pmap_release(pmap_t pmap)
{
	vm_page_t m;
	int asid;

	KASSERT(pmap->pm_stats.resident_count == 0,
	    ("pmap_release: pmap resident count %ld != 0",
	    pmap->pm_stats.resident_count));
	KASSERT(vm_radix_is_empty(&pmap->pm_root),
	    ("pmap_release: pmap has reserved page table page(s)"));

	mtx_lock_spin(&asid_set_mutex);
	if (COOKIE_TO_EPOCH(pmap->pm_cookie) == asid_epoch) {
		asid = COOKIE_TO_ASID(pmap->pm_cookie);
		KASSERT(asid >= ASID_FIRST_AVAILABLE && asid < asid_set_size,
		    ("pmap_release: pmap cookie has out-of-range asid"));
		bit_clear(asid_set, asid);
	}
	mtx_unlock_spin(&asid_set_mutex);

	m = PHYS_TO_VM_PAGE(pmap->pm_l0_paddr);
	vm_page_unwire_noq(m);
	vm_page_free_zero(m);
}