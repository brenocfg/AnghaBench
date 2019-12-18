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
typedef  int vm_offset_t ;
struct rwlock {int dummy; } ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pd_entry_t ;

/* Variables and functions */
 int ATTR_AF ; 
 int ATTR_AP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATTR_AP_RO ; 
 int ATTR_DESCR_MASK ; 
 int ATTR_MASK ; 
 int ATTR_SW_MANAGED ; 
 int ATTR_SW_WIRED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int L0_OFFSET ; 
 int L0_SIZE ; 
 int L1_OFFSET ; 
 int L1_SIZE ; 
 int L2_BLOCK ; 
 int L2_OFFSET ; 
 int L2_SIZE ; 
 int L2_TABLE ; 
 int L3_PAGE ; 
 scalar_t__ L3_SIZE ; 
 int MADV_DONTNEED ; 
 int MADV_FREE ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_fcmpset_long (int*,int*,int) ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 int /*<<< orphan*/  pmap_clear_bits (int*,int) ; 
 int /*<<< orphan*/  pmap_demote_l2_locked (int /*<<< orphan*/ ,int*,int,struct rwlock**) ; 
 int /*<<< orphan*/  pmap_invalidate_range (int /*<<< orphan*/ ,int,int) ; 
 int* pmap_l0 (int /*<<< orphan*/ ,int) ; 
 int* pmap_l0_to_l1 (int*,int) ; 
 int* pmap_l1_to_l2 (int*,int) ; 
 int* pmap_l2_to_l3 (int*,int) ; 
 int pmap_load (int*) ; 
 scalar_t__ pmap_pte_dirty (int) ; 
 int /*<<< orphan*/  pmap_remove_l3 (int /*<<< orphan*/ ,int*,int,int,int /*<<< orphan*/ *,struct rwlock**) ; 
 int /*<<< orphan*/  rw_wunlock (struct rwlock*) ; 
 int /*<<< orphan*/  vm_page_dirty (int /*<<< orphan*/ ) ; 

void
pmap_advise(pmap_t pmap, vm_offset_t sva, vm_offset_t eva, int advice)
{
	struct rwlock *lock;
	vm_offset_t va, va_next;
	vm_page_t m;
	pd_entry_t *l0, *l1, *l2, oldl2;
	pt_entry_t *l3, oldl3;

	if (advice != MADV_DONTNEED && advice != MADV_FREE)
		return;

	PMAP_LOCK(pmap);
	for (; sva < eva; sva = va_next) {
		l0 = pmap_l0(pmap, sva);
		if (pmap_load(l0) == 0) {
			va_next = (sva + L0_SIZE) & ~L0_OFFSET;
			if (va_next < sva)
				va_next = eva;
			continue;
		}
		l1 = pmap_l0_to_l1(l0, sva);
		if (pmap_load(l1) == 0) {
			va_next = (sva + L1_SIZE) & ~L1_OFFSET;
			if (va_next < sva)
				va_next = eva;
			continue;
		}
		va_next = (sva + L2_SIZE) & ~L2_OFFSET;
		if (va_next < sva)
			va_next = eva;
		l2 = pmap_l1_to_l2(l1, sva);
		oldl2 = pmap_load(l2);
		if (oldl2 == 0)
			continue;
		if ((oldl2 & ATTR_DESCR_MASK) == L2_BLOCK) {
			if ((oldl2 & ATTR_SW_MANAGED) == 0)
				continue;
			lock = NULL;
			if (!pmap_demote_l2_locked(pmap, l2, sva, &lock)) {
				if (lock != NULL)
					rw_wunlock(lock);

				/*
				 * The 2MB page mapping was destroyed.
				 */
				continue;
			}

			/*
			 * Unless the page mappings are wired, remove the
			 * mapping to a single page so that a subsequent
			 * access may repromote.  Choosing the last page
			 * within the address range [sva, min(va_next, eva))
			 * generally results in more repromotions.  Since the
			 * underlying page table page is fully populated, this
			 * removal never frees a page table page.
			 */
			if ((oldl2 & ATTR_SW_WIRED) == 0) {
				va = eva;
				if (va > va_next)
					va = va_next;
				va -= PAGE_SIZE;
				KASSERT(va >= sva,
				    ("pmap_advise: no address gap"));
				l3 = pmap_l2_to_l3(l2, va);
				KASSERT(pmap_load(l3) != 0,
				    ("pmap_advise: invalid PTE"));
				pmap_remove_l3(pmap, l3, va, pmap_load(l2),
				    NULL, &lock);
			}
			if (lock != NULL)
				rw_wunlock(lock);
		}
		KASSERT((pmap_load(l2) & ATTR_DESCR_MASK) == L2_TABLE,
		    ("pmap_advise: invalid L2 entry after demotion"));
		if (va_next > eva)
			va_next = eva;
		va = va_next;
		for (l3 = pmap_l2_to_l3(l2, sva); sva != va_next; l3++,
		    sva += L3_SIZE) {
			oldl3 = pmap_load(l3);
			if ((oldl3 & (ATTR_SW_MANAGED | ATTR_DESCR_MASK)) !=
			    (ATTR_SW_MANAGED | L3_PAGE))
				goto maybe_invlrng;
			else if (pmap_pte_dirty(oldl3)) {
				if (advice == MADV_DONTNEED) {
					/*
					 * Future calls to pmap_is_modified()
					 * can be avoided by making the page
					 * dirty now.
					 */
					m = PHYS_TO_VM_PAGE(oldl3 & ~ATTR_MASK);
					vm_page_dirty(m);
				}
				while (!atomic_fcmpset_long(l3, &oldl3,
				    (oldl3 & ~ATTR_AF) | ATTR_AP(ATTR_AP_RO)))
					cpu_spinwait();
			} else if ((oldl3 & ATTR_AF) != 0)
				pmap_clear_bits(l3, ATTR_AF);
			else
				goto maybe_invlrng;
			if (va == va_next)
				va = sva;
			continue;
maybe_invlrng:
			if (va != va_next) {
				pmap_invalidate_range(pmap, va, sva);
				va = va_next;
			}
		}
		if (va != va_next)
			pmap_invalidate_range(pmap, va, sva);
	}
	PMAP_UNLOCK(pmap);
}