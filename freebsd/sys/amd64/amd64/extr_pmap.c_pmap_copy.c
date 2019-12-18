#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
struct spglist {int dummy; } ;
struct rwlock {int dummy; } ;
typedef  int pt_entry_t ;
typedef  int pml4_entry_t ;
typedef  TYPE_2__* pmap_t ;
typedef  int pdp_entry_t ;
typedef  int pd_entry_t ;
struct TYPE_26__ {scalar_t__ pm_type; } ;
struct TYPE_25__ {scalar_t__ ref_count; scalar_t__ pindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ NBPDP ; 
 scalar_t__ NBPDR ; 
 scalar_t__ NBPML4 ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PDPMASK ; 
 scalar_t__ PDRMASK ; 
 int PG_FRAME ; 
 int PG_MANAGED ; 
 int PG_PS ; 
 int PG_W ; 
 scalar_t__ PHYS_TO_DMAP (int) ; 
 TYPE_1__* PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_ENTER_NORECLAIM ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_2__*) ; 
 scalar_t__ PML4MASK ; 
 int /*<<< orphan*/  SLIST_INIT (struct spglist*) ; 
 scalar_t__ UPT_MIN_ADDRESS ; 
 int VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,int) ; 
 int pmap_accessed_bit (TYPE_2__*) ; 
 TYPE_1__* pmap_allocpde (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_1__* pmap_allocpte (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ pmap_emulate_ad_bits (TYPE_2__*) ; 
 int /*<<< orphan*/  pmap_invalidate_page (TYPE_2__*,scalar_t__) ; 
 int pmap_modified_bit (TYPE_2__*) ; 
 size_t pmap_pde_index (scalar_t__) ; 
 int /*<<< orphan*/  pmap_pde_mappings ; 
 scalar_t__ pmap_pde_pindex (scalar_t__) ; 
 int* pmap_pdpe_to_pde (int*,scalar_t__) ; 
 int* pmap_pml4e (TYPE_2__*,scalar_t__) ; 
 int* pmap_pml4e_to_pdpe (int*,scalar_t__) ; 
 size_t pmap_pte_index (scalar_t__) ; 
 scalar_t__ pmap_pv_insert_pde (TYPE_2__*,scalar_t__,int,int /*<<< orphan*/ ,struct rwlock**) ; 
 int /*<<< orphan*/  pmap_resident_count_inc (TYPE_2__*,int) ; 
 scalar_t__ pmap_try_insert_pv_entry (TYPE_2__*,scalar_t__,TYPE_1__*,struct rwlock**) ; 
 scalar_t__ pmap_unwire_ptp (TYPE_2__*,scalar_t__,TYPE_1__*,struct spglist*) ; 
 int pmap_valid_bit (TYPE_2__*) ; 
 int /*<<< orphan*/  rw_wunlock (struct rwlock*) ; 
 int /*<<< orphan*/  vm_page_free_pages_toq (struct spglist*,int) ; 

void
pmap_copy(pmap_t dst_pmap, pmap_t src_pmap, vm_offset_t dst_addr, vm_size_t len,
    vm_offset_t src_addr)
{
	struct rwlock *lock;
	struct spglist free;
	pml4_entry_t *pml4e;
	pdp_entry_t *pdpe;
	pd_entry_t *pde, srcptepaddr;
	pt_entry_t *dst_pte, PG_A, PG_M, PG_V, ptetemp, *src_pte;
	vm_offset_t addr, end_addr, va_next;
	vm_page_t dst_pdpg, dstmpte, srcmpte;

	if (dst_addr != src_addr)
		return;

	if (dst_pmap->pm_type != src_pmap->pm_type)
		return;

	/*
	 * EPT page table entries that require emulation of A/D bits are
	 * sensitive to clearing the PG_A bit (aka EPT_PG_READ). Although
	 * we clear PG_M (aka EPT_PG_WRITE) concomitantly, the PG_U bit
	 * (aka EPT_PG_EXECUTE) could still be set. Since some EPT
	 * implementations flag an EPT misconfiguration for exec-only
	 * mappings we skip this function entirely for emulated pmaps.
	 */
	if (pmap_emulate_ad_bits(dst_pmap))
		return;

	end_addr = src_addr + len;
	lock = NULL;
	if (dst_pmap < src_pmap) {
		PMAP_LOCK(dst_pmap);
		PMAP_LOCK(src_pmap);
	} else {
		PMAP_LOCK(src_pmap);
		PMAP_LOCK(dst_pmap);
	}

	PG_A = pmap_accessed_bit(dst_pmap);
	PG_M = pmap_modified_bit(dst_pmap);
	PG_V = pmap_valid_bit(dst_pmap);

	for (addr = src_addr; addr < end_addr; addr = va_next) {
		KASSERT(addr < UPT_MIN_ADDRESS,
		    ("pmap_copy: invalid to pmap_copy page tables"));

		pml4e = pmap_pml4e(src_pmap, addr);
		if ((*pml4e & PG_V) == 0) {
			va_next = (addr + NBPML4) & ~PML4MASK;
			if (va_next < addr)
				va_next = end_addr;
			continue;
		}

		pdpe = pmap_pml4e_to_pdpe(pml4e, addr);
		if ((*pdpe & PG_V) == 0) {
			va_next = (addr + NBPDP) & ~PDPMASK;
			if (va_next < addr)
				va_next = end_addr;
			continue;
		}

		va_next = (addr + NBPDR) & ~PDRMASK;
		if (va_next < addr)
			va_next = end_addr;

		pde = pmap_pdpe_to_pde(pdpe, addr);
		srcptepaddr = *pde;
		if (srcptepaddr == 0)
			continue;
			
		if (srcptepaddr & PG_PS) {
			if ((addr & PDRMASK) != 0 || addr + NBPDR > end_addr)
				continue;
			dst_pdpg = pmap_allocpde(dst_pmap, addr, NULL);
			if (dst_pdpg == NULL)
				break;
			pde = (pd_entry_t *)
			    PHYS_TO_DMAP(VM_PAGE_TO_PHYS(dst_pdpg));
			pde = &pde[pmap_pde_index(addr)];
			if (*pde == 0 && ((srcptepaddr & PG_MANAGED) == 0 ||
			    pmap_pv_insert_pde(dst_pmap, addr, srcptepaddr,
			    PMAP_ENTER_NORECLAIM, &lock))) {
				*pde = srcptepaddr & ~PG_W;
				pmap_resident_count_inc(dst_pmap, NBPDR /
				    PAGE_SIZE);
				atomic_add_long(&pmap_pde_mappings, 1);
			} else
				dst_pdpg->ref_count--;
			continue;
		}

		srcptepaddr &= PG_FRAME;
		srcmpte = PHYS_TO_VM_PAGE(srcptepaddr);
		KASSERT(srcmpte->ref_count > 0,
		    ("pmap_copy: source page table page is unused"));

		if (va_next > end_addr)
			va_next = end_addr;

		src_pte = (pt_entry_t *)PHYS_TO_DMAP(srcptepaddr);
		src_pte = &src_pte[pmap_pte_index(addr)];
		dstmpte = NULL;
		for (; addr < va_next; addr += PAGE_SIZE, src_pte++) {
			ptetemp = *src_pte;

			/*
			 * We only virtual copy managed pages.
			 */
			if ((ptetemp & PG_MANAGED) == 0)
				continue;

			if (dstmpte != NULL) {
				KASSERT(dstmpte->pindex ==
				    pmap_pde_pindex(addr),
				    ("dstmpte pindex/addr mismatch"));
				dstmpte->ref_count++;
			} else if ((dstmpte = pmap_allocpte(dst_pmap, addr,
			    NULL)) == NULL)
				goto out;
			dst_pte = (pt_entry_t *)
			    PHYS_TO_DMAP(VM_PAGE_TO_PHYS(dstmpte));
			dst_pte = &dst_pte[pmap_pte_index(addr)];
			if (*dst_pte == 0 &&
			    pmap_try_insert_pv_entry(dst_pmap, addr,
			    PHYS_TO_VM_PAGE(ptetemp & PG_FRAME), &lock)) {
				/*
				 * Clear the wired, modified, and accessed
				 * (referenced) bits during the copy.
				 */
				*dst_pte = ptetemp & ~(PG_W | PG_M | PG_A);
				pmap_resident_count_inc(dst_pmap, 1);
			} else {
				SLIST_INIT(&free);
				if (pmap_unwire_ptp(dst_pmap, addr, dstmpte,
				    &free)) {
					/*
					 * Although "addr" is not mapped,
					 * paging-structure caches could
					 * nonetheless have entries that refer
					 * to the freed page table pages.
					 * Invalidate those entries.
					 */
					pmap_invalidate_page(dst_pmap, addr);
					vm_page_free_pages_toq(&free, true);
				}
				goto out;
			}
			/* Have we copied all of the valid mappings? */ 
			if (dstmpte->ref_count >= srcmpte->ref_count)
				break;
		}
	}
out:
	if (lock != NULL)
		rw_wunlock(lock);
	PMAP_UNLOCK(src_pmap);
	PMAP_UNLOCK(dst_pmap);
}