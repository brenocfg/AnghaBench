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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  register_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_DESCR_VALID ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ishst ; 
 int /*<<< orphan*/  pmap_clear_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_invalidate_range_nopin (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pmap_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmap_update_entry(pmap_t pmap, pd_entry_t *pte, pd_entry_t newpte,
    vm_offset_t va, vm_size_t size)
{
	register_t intr;

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);

	/*
	 * Ensure we don't get switched out with the page table in an
	 * inconsistent state. We also need to ensure no interrupts fire
	 * as they may make use of an address we are about to invalidate.
	 */
	intr = intr_disable();

	/*
	 * Clear the old mapping's valid bit, but leave the rest of the entry
	 * unchanged, so that a lockless, concurrent pmap_kextract() can still
	 * lookup the physical address.
	 */
	pmap_clear_bits(pte, ATTR_DESCR_VALID);
	pmap_invalidate_range_nopin(pmap, va, va + size);

	/* Create the new mapping */
	pmap_store(pte, newpte);
	dsb(ishst);

	intr_restore(intr);
}