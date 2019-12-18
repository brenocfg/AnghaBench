#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  TYPE_2__* vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ u_long ;
struct spglist {int dummy; } ;
typedef  int pt_entry_t ;
typedef  int pdp_entry_t ;
typedef  int pd_entry_t ;
struct TYPE_6__ {int /*<<< orphan*/  ss; } ;
struct TYPE_8__ {TYPE_1__ s; } ;
struct TYPE_7__ {scalar_t__ ref_count; } ;

/* Variables and functions */
 int AMDID_PAGE1GB ; 
 scalar_t__ DMAP_MIN_ADDRESS ; 
 int /*<<< orphan*/  DMAP_TO_PHYS (scalar_t__) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ NBPDP ; 
 scalar_t__ NBPDR ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PDPMASK ; 
 scalar_t__ PDRMASK ; 
 TYPE_2__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 scalar_t__ PMAP_ADDRESS_IN_LARGEMAP (scalar_t__) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_INIT (struct spglist*) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (struct spglist*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int X86_PG_PS ; 
 int X86_PG_V ; 
 int amd_feature ; 
 scalar_t__ dmaplimit ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  large_vmem ; 
 int /*<<< orphan*/  pde_store (int*,int /*<<< orphan*/ ) ; 
 TYPE_3__ plinks ; 
 int /*<<< orphan*/  pmap_invalidate_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int* pmap_large_map_pdpe (scalar_t__) ; 
 int* pmap_pde_to_pte (int*,scalar_t__) ; 
 int* pmap_pdpe_to_pde (int*,scalar_t__) ; 
 int /*<<< orphan*/  pte_clear (int*) ; 
 int /*<<< orphan*/  vm_page_free_pages_toq (struct spglist*,int) ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

void
pmap_large_unmap(void *svaa, vm_size_t len)
{
	vm_offset_t sva, va;
	vm_size_t inc;
	pdp_entry_t *pdpe, pdp;
	pd_entry_t *pde, pd;
	pt_entry_t *pte;
	vm_page_t m;
	struct spglist spgf;

	sva = (vm_offset_t)svaa;
	if (len == 0 || sva + len < sva || (sva >= DMAP_MIN_ADDRESS &&
	    sva + len <= DMAP_MIN_ADDRESS + dmaplimit))
		return;

	SLIST_INIT(&spgf);
	KASSERT(PMAP_ADDRESS_IN_LARGEMAP(sva) &&
	    PMAP_ADDRESS_IN_LARGEMAP(sva + len - 1),
	    ("not largemap range %#lx %#lx", (u_long)svaa, (u_long)svaa + len));
	PMAP_LOCK(kernel_pmap);
	for (va = sva; va < sva + len; va += inc) {
		pdpe = pmap_large_map_pdpe(va);
		pdp = *pdpe;
		KASSERT((pdp & X86_PG_V) != 0,
		    ("invalid pdp va %#lx pdpe %#lx pdp %#lx", va,
		    (u_long)pdpe, pdp));
		if ((pdp & X86_PG_PS) != 0) {
			KASSERT((amd_feature & AMDID_PAGE1GB) != 0,
			    ("no 1G pages, va %#lx pdpe %#lx pdp %#lx", va,
			    (u_long)pdpe, pdp));
			KASSERT((va & PDPMASK) == 0,
			    ("PDPMASK bit set, va %#lx pdpe %#lx pdp %#lx", va,
			    (u_long)pdpe, pdp));
			KASSERT(va + NBPDP <= sva + len,
			    ("unmap covers partial 1GB page, sva %#lx va %#lx "
			    "pdpe %#lx pdp %#lx len %#lx", sva, va,
			    (u_long)pdpe, pdp, len));
			*pdpe = 0;
			inc = NBPDP;
			continue;
		}
		pde = pmap_pdpe_to_pde(pdpe, va);
		pd = *pde;
		KASSERT((pd & X86_PG_V) != 0,
		    ("invalid pd va %#lx pde %#lx pd %#lx", va,
		    (u_long)pde, pd));
		if ((pd & X86_PG_PS) != 0) {
			KASSERT((va & PDRMASK) == 0,
			    ("PDRMASK bit set, va %#lx pde %#lx pd %#lx", va,
			    (u_long)pde, pd));
			KASSERT(va + NBPDR <= sva + len,
			    ("unmap covers partial 2MB page, sva %#lx va %#lx "
			    "pde %#lx pd %#lx len %#lx", sva, va, (u_long)pde,
			    pd, len));
			pde_store(pde, 0);
			inc = NBPDR;
			m = PHYS_TO_VM_PAGE(DMAP_TO_PHYS((vm_offset_t)pde));
			m->ref_count--;
			if (m->ref_count == 0) {
				*pdpe = 0;
				SLIST_INSERT_HEAD(&spgf, m, plinks.s.ss);
			}
			continue;
		}
		pte = pmap_pde_to_pte(pde, va);
		KASSERT((*pte & X86_PG_V) != 0,
		    ("invalid pte va %#lx pte %#lx pt %#lx", va,
		    (u_long)pte, *pte));
		pte_clear(pte);
		inc = PAGE_SIZE;
		m = PHYS_TO_VM_PAGE(DMAP_TO_PHYS((vm_offset_t)pte));
		m->ref_count--;
		if (m->ref_count == 0) {
			*pde = 0;
			SLIST_INSERT_HEAD(&spgf, m, plinks.s.ss);
			m = PHYS_TO_VM_PAGE(DMAP_TO_PHYS((vm_offset_t)pde));
			m->ref_count--;
			if (m->ref_count == 0) {
				*pdpe = 0;
				SLIST_INSERT_HEAD(&spgf, m, plinks.s.ss);
			}
		}
	}
	pmap_invalidate_range(kernel_pmap, sva, sva + len);
	PMAP_UNLOCK(kernel_pmap);
	vm_page_free_pages_toq(&spgf, false);
	vmem_free(large_vmem, sva, len);
}