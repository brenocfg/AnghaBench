#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  scalar_t__ pd_entry_t ;
struct TYPE_3__ {int /*<<< orphan*/  system_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MIPS_KSEG0_LARGEST_PHYS ; 
 scalar_t__ MIPS_PHYS_TO_DIRECT (int /*<<< orphan*/ ) ; 
 int NBPDR ; 
 int /*<<< orphan*/  NBSEG ; 
 int NPTEPG ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PDRMASK ; 
 int /*<<< orphan*/  PTE_G ; 
 int VM_ALLOC_INTERRUPT ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ *) ; 
 TYPE_1__* kernel_map ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int kernel_vm_end ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nkpt ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/ * pmap_alloc_direct_page (int /*<<< orphan*/ ,int) ; 
 scalar_t__* pmap_pdpe_to_pde (scalar_t__*,int) ; 
 scalar_t__* pmap_segmap (int /*<<< orphan*/ ,int) ; 
 int roundup2 (int,int /*<<< orphan*/ ) ; 
 int vm_map_max (TYPE_1__*) ; 
 scalar_t__ vm_page_reclaim_contig (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
pmap_growkernel(vm_offset_t addr)
{
	vm_page_t nkpg;
	pd_entry_t *pde, *pdpe;
	pt_entry_t *pte;
	int i, req_class;

	mtx_assert(&kernel_map->system_mtx, MA_OWNED);
	req_class = VM_ALLOC_INTERRUPT;
	addr = roundup2(addr, NBSEG);
	if (addr - 1 >= vm_map_max(kernel_map))
		addr = vm_map_max(kernel_map);
	while (kernel_vm_end < addr) {
		pdpe = pmap_segmap(kernel_pmap, kernel_vm_end);
#ifdef __mips_n64
		if (*pdpe == 0) {
			/* new intermediate page table entry */
			nkpg = pmap_alloc_direct_page(nkpt, req_class);
			if (nkpg == NULL)
				panic("pmap_growkernel: no memory to grow kernel");
			*pdpe = (pd_entry_t)MIPS_PHYS_TO_DIRECT(VM_PAGE_TO_PHYS(nkpg));
			continue; /* try again */
		}
#endif
		pde = pmap_pdpe_to_pde(pdpe, kernel_vm_end);
		if (*pde != 0) {
			kernel_vm_end = (kernel_vm_end + NBPDR) & ~PDRMASK;
			if (kernel_vm_end - 1 >= vm_map_max(kernel_map)) {
				kernel_vm_end = vm_map_max(kernel_map);
				break;
			}
			continue;
		}

		/*
		 * This index is bogus, but out of the way
		 */
		nkpg = pmap_alloc_direct_page(nkpt, req_class);
#ifndef __mips_n64
		if (nkpg == NULL && vm_page_reclaim_contig(req_class, 1,
		    0, MIPS_KSEG0_LARGEST_PHYS, PAGE_SIZE, 0))
			nkpg = pmap_alloc_direct_page(nkpt, req_class);
#endif
		if (nkpg == NULL)
			panic("pmap_growkernel: no memory to grow kernel");
		nkpt++;
		*pde = (pd_entry_t)MIPS_PHYS_TO_DIRECT(VM_PAGE_TO_PHYS(nkpg));

		/*
		 * The R[4-7]?00 stores only one copy of the Global bit in
		 * the translation lookaside buffer for each 2 page entry.
		 * Thus invalid entrys must have the Global bit set so when
		 * Entry LO and Entry HI G bits are anded together they will
		 * produce a global bit to store in the tlb.
		 */
		pte = (pt_entry_t *)*pde;
		for (i = 0; i < NPTEPG; i++)
			pte[i] = PTE_G;

		kernel_vm_end = (kernel_vm_end + NBPDR) & ~PDRMASK;
		if (kernel_vm_end - 1 >= vm_map_max(kernel_map)) {
			kernel_vm_end = vm_map_max(kernel_map);
			break;
		}
	}
}