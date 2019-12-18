#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vmem_addr_t ;
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
typedef  scalar_t__ pt_entry_t ;
typedef  scalar_t__ pdp_entry_t ;
typedef  scalar_t__ pd_entry_t ;
struct TYPE_2__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int AMDID_PAGE1GB ; 
 int /*<<< orphan*/  DMAP_TO_PHYS (uintptr_t) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ NBPDP ; 
 scalar_t__ NBPDR ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PDPMASK ; 
 scalar_t__ PDRMASK ; 
 scalar_t__ PHYS_TO_DMAP (scalar_t__) ; 
 TYPE_1__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ X86_PG_A ; 
 scalar_t__ X86_PG_PS ; 
 scalar_t__ X86_PG_RW ; 
 scalar_t__ X86_PG_V ; 
 int amd_feature ; 
 scalar_t__ dmaplimit ; 
 int /*<<< orphan*/  kernel_pmap ; 
 scalar_t__ pg_g ; 
 scalar_t__ pg_nx ; 
 scalar_t__ pmap_cache_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmap_change_attr (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int pmap_large_map_getva (scalar_t__,scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__* pmap_large_map_pde (scalar_t__) ; 
 scalar_t__* pmap_large_map_pdpe (scalar_t__) ; 
 scalar_t__* pmap_large_map_pte (scalar_t__) ; 
 scalar_t__ rounddown2 (scalar_t__,scalar_t__) ; 
 scalar_t__ roundup2 (scalar_t__,scalar_t__) ; 

int
pmap_large_map(vm_paddr_t spa, vm_size_t len, void **addr,
    vm_memattr_t mattr)
{
	pdp_entry_t *pdpe;
	pd_entry_t *pde;
	pt_entry_t *pte;
	vm_offset_t va, inc;
	vmem_addr_t vmem_res;
	vm_paddr_t pa;
	int error;

	if (len == 0 || spa + len < spa)
		return (EINVAL);

	/* See if DMAP can serve. */
	if (spa + len <= dmaplimit) {
		va = PHYS_TO_DMAP(spa);
		*addr = (void *)va;
		return (pmap_change_attr(va, len, mattr));
	}

	/*
	 * No, allocate KVA.  Fit the address with best possible
	 * alignment for superpages.  Fall back to worse align if
	 * failed.
	 */
	error = ENOMEM;
	if ((amd_feature & AMDID_PAGE1GB) != 0 && rounddown2(spa + len,
	    NBPDP) >= roundup2(spa, NBPDP) + NBPDP)
		error = pmap_large_map_getva(len, NBPDP, spa & PDPMASK,
		    &vmem_res);
	if (error != 0 && rounddown2(spa + len, NBPDR) >= roundup2(spa,
	    NBPDR) + NBPDR)
		error = pmap_large_map_getva(len, NBPDR, spa & PDRMASK,
		    &vmem_res);
	if (error != 0)
		error = pmap_large_map_getva(len, PAGE_SIZE, 0, &vmem_res);
	if (error != 0)
		return (error);

	/*
	 * Fill pagetable.  PG_M is not pre-set, we scan modified bits
	 * in the pagetable to minimize flushing.  No need to
	 * invalidate TLB, since we only update invalid entries.
	 */
	PMAP_LOCK(kernel_pmap);
	for (pa = spa, va = vmem_res; len > 0; pa += inc, va += inc,
	    len -= inc) {
		if ((amd_feature & AMDID_PAGE1GB) != 0 && len >= NBPDP &&
		    (pa & PDPMASK) == 0 && (va & PDPMASK) == 0) {
			pdpe = pmap_large_map_pdpe(va);
			MPASS(*pdpe == 0);
			*pdpe = pa | pg_g | X86_PG_PS | X86_PG_RW |
			    X86_PG_V | X86_PG_A | pg_nx |
			    pmap_cache_bits(kernel_pmap, mattr, TRUE);
			inc = NBPDP;
		} else if (len >= NBPDR && (pa & PDRMASK) == 0 &&
		    (va & PDRMASK) == 0) {
			pde = pmap_large_map_pde(va);
			MPASS(*pde == 0);
			*pde = pa | pg_g | X86_PG_PS | X86_PG_RW |
			    X86_PG_V | X86_PG_A | pg_nx |
			    pmap_cache_bits(kernel_pmap, mattr, TRUE);
			PHYS_TO_VM_PAGE(DMAP_TO_PHYS((uintptr_t)pde))->
			    ref_count++;
			inc = NBPDR;
		} else {
			pte = pmap_large_map_pte(va);
			MPASS(*pte == 0);
			*pte = pa | pg_g | X86_PG_RW | X86_PG_V |
			    X86_PG_A | pg_nx | pmap_cache_bits(kernel_pmap,
			    mattr, FALSE);
			PHYS_TO_VM_PAGE(DMAP_TO_PHYS((uintptr_t)pte))->
			    ref_count++;
			inc = PAGE_SIZE;
		}
	}
	PMAP_UNLOCK(kernel_pmap);
	MPASS(len == 0);

	*addr = (void *)vmem_res;
	return (0);
}