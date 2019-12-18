#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  real_pte_t ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_4__ {int (* hpte_updatepp ) (unsigned long,unsigned long,unsigned long,unsigned int,unsigned int,int,unsigned long) ;} ;
struct TYPE_3__ {unsigned int shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CPU_FTR_COHERENT_ICACHE ; 
 unsigned long H_PAGE_BUSY ; 
 unsigned long H_PAGE_HASHPTE ; 
 unsigned long H_PAGE_THP_HUGE ; 
 unsigned int MMU_PAGE_16G ; 
 unsigned long PAGE_SHIFT ; 
 long PTRS_PER_PMD ; 
 long PTRS_PER_PUD ; 
 unsigned long _PAGE_ACCESSED ; 
 unsigned long _PAGE_DEVMAP ; 
 unsigned long _PAGE_DIRTY ; 
 unsigned long _PAGE_HPTEFLAGS ; 
 unsigned long _PAGE_WRITE ; 
 int /*<<< orphan*/  __pte (unsigned long) ; 
 int /*<<< orphan*/  __real_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  check_pte_access (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_failure_debug (unsigned long,unsigned long,unsigned long,unsigned long,int,unsigned int,unsigned int,unsigned long) ; 
 unsigned long hash_page_do_lazy_icache (unsigned long,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long hpt_hash (unsigned long,unsigned int,int) ; 
 unsigned long hpt_vpn (unsigned long,unsigned long,int) ; 
 long hpte_insert_repeating (unsigned long,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ,unsigned int,int) ; 
 unsigned long htab_convert_pte_flags (unsigned long) ; 
 scalar_t__ likely (int) ; 
 TYPE_2__ mmu_hash_ops ; 
 TYPE_1__* mmu_psize_defs ; 
 unsigned long pte_get_hash_gslot (unsigned long,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 unsigned long pte_set_hidx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,long) ; 
 unsigned long pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (unsigned long,unsigned long,unsigned long,unsigned int,unsigned int,int,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

int __hash_page_huge(unsigned long ea, unsigned long access, unsigned long vsid,
		     pte_t *ptep, unsigned long trap, unsigned long flags,
		     int ssize, unsigned int shift, unsigned int mmu_psize)
{
	real_pte_t rpte;
	unsigned long vpn;
	unsigned long old_pte, new_pte;
	unsigned long rflags, pa;
	long slot, offset;

	BUG_ON(shift != mmu_psize_defs[mmu_psize].shift);

	/* Search the Linux page table for a match with va */
	vpn = hpt_vpn(ea, vsid, ssize);

	/*
	 * At this point, we have a pte (old_pte) which can be used to build
	 * or update an HPTE. There are 2 cases:
	 *
	 * 1. There is a valid (present) pte with no associated HPTE (this is
	 *	the most common case)
	 * 2. There is a valid (present) pte with an associated HPTE. The
	 *	current values of the pp bits in the HPTE prevent access
	 *	because we are doing software DIRTY bit management and the
	 *	page is currently not DIRTY.
	 */


	do {
		old_pte = pte_val(*ptep);
		/* If PTE busy, retry the access */
		if (unlikely(old_pte & H_PAGE_BUSY))
			return 0;
		/* If PTE permissions don't match, take page fault */
		if (unlikely(!check_pte_access(access, old_pte)))
			return 1;

		/*
		 * Try to lock the PTE, add ACCESSED and DIRTY if it was
		 * a write access
		 */
		new_pte = old_pte | H_PAGE_BUSY | _PAGE_ACCESSED;
		if (access & _PAGE_WRITE)
			new_pte |= _PAGE_DIRTY;
	} while(!pte_xchg(ptep, __pte(old_pte), __pte(new_pte)));

	/* Make sure this is a hugetlb entry */
	if (old_pte & (H_PAGE_THP_HUGE | _PAGE_DEVMAP))
		return 0;

	rflags = htab_convert_pte_flags(new_pte);
	if (unlikely(mmu_psize == MMU_PAGE_16G))
		offset = PTRS_PER_PUD;
	else
		offset = PTRS_PER_PMD;
	rpte = __real_pte(__pte(old_pte), ptep, offset);

	if (!cpu_has_feature(CPU_FTR_COHERENT_ICACHE))
		/*
		 * No CPU has hugepages but lacks no execute, so we
		 * don't need to worry about that case
		 */
		rflags = hash_page_do_lazy_icache(rflags, __pte(old_pte), trap);

	/* Check if pte already has an hpte (case 2) */
	if (unlikely(old_pte & H_PAGE_HASHPTE)) {
		/* There MIGHT be an HPTE for this pte */
		unsigned long gslot;

		gslot = pte_get_hash_gslot(vpn, shift, ssize, rpte, 0);
		if (mmu_hash_ops.hpte_updatepp(gslot, rflags, vpn, mmu_psize,
					       mmu_psize, ssize, flags) == -1)
			old_pte &= ~_PAGE_HPTEFLAGS;
	}

	if (likely(!(old_pte & H_PAGE_HASHPTE))) {
		unsigned long hash = hpt_hash(vpn, shift, ssize);

		pa = pte_pfn(__pte(old_pte)) << PAGE_SHIFT;

		/* clear HPTE slot informations in new PTE */
		new_pte = (new_pte & ~_PAGE_HPTEFLAGS) | H_PAGE_HASHPTE;

		slot = hpte_insert_repeating(hash, vpn, pa, rflags, 0,
					     mmu_psize, ssize);

		/*
		 * Hypervisor failure. Restore old pte and return -1
		 * similar to __hash_page_*
		 */
		if (unlikely(slot == -2)) {
			*ptep = __pte(old_pte);
			hash_failure_debug(ea, access, vsid, trap, ssize,
					   mmu_psize, mmu_psize, old_pte);
			return -1;
		}

		new_pte |= pte_set_hidx(ptep, rpte, 0, slot, offset);
	}

	/*
	 * No need to use ldarx/stdcx here
	 */
	*ptep = __pte(new_pte & ~H_PAGE_BUSY);
	return 0;
}