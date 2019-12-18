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
typedef  scalar_t__ vm_page_t ;
typedef  int vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
struct vm_page {int dummy; } ;
typedef  int pdp_entry_t ;
typedef  int pd_entry_t ;

/* Variables and functions */
 int NBPDR ; 
 int NPDEPG ; 
 int PAGE_SIZE ; 
 int PG_PS ; 
 scalar_t__ PHYS_TO_DMAP (int) ; 
 scalar_t__ VM_MIN_KERNEL_ADDRESS ; 
 int X86_PG_A ; 
 int X86_PG_M ; 
 int X86_PG_RW ; 
 int X86_PG_V ; 
 int _vm_phys_domain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_add_page (int) ; 
 scalar_t__ first_page ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  pagezero (void*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pde_store (int*,int) ; 
 int pg_g ; 
 int pg_nx ; 
 int* pmap_pdpe (int /*<<< orphan*/ ,scalar_t__) ; 
 int* pmap_pdpe_to_pde (int*,scalar_t__) ; 
 int /*<<< orphan*/  ptoa (long) ; 
 scalar_t__ vm_page_array ; 
 long vm_page_array_size ; 
 int vm_phys_early_alloc (int,int) ; 

void
pmap_page_array_startup(long pages)
{
	pdp_entry_t *pdpe;
	pd_entry_t *pde, newpdir;
	vm_offset_t va, start, end;
	vm_paddr_t pa;
	long pfn;
	int domain, i;

	vm_page_array_size = pages;

	start = VM_MIN_KERNEL_ADDRESS;
	end = start + pages * sizeof(struct vm_page);
	for (va = start; va < end; va += NBPDR) {
		pfn = first_page + (va - start) / sizeof(struct vm_page);
		domain = _vm_phys_domain(ptoa(pfn));
		pdpe = pmap_pdpe(kernel_pmap, va);
		if ((*pdpe & X86_PG_V) == 0) {
			pa = vm_phys_early_alloc(domain, PAGE_SIZE);
			dump_add_page(pa);
			pagezero((void *)PHYS_TO_DMAP(pa));
			*pdpe = (pdp_entry_t)(pa | X86_PG_V | X86_PG_RW |
			    X86_PG_A | X86_PG_M);
		}
		pde = pmap_pdpe_to_pde(pdpe, va);
		if ((*pde & X86_PG_V) != 0)
			panic("Unexpected pde");
		pa = vm_phys_early_alloc(domain, NBPDR);
		for (i = 0; i < NPDEPG; i++)
			dump_add_page(pa + i * PAGE_SIZE);
		newpdir = (pd_entry_t)(pa | X86_PG_V | X86_PG_RW | X86_PG_A |
		    X86_PG_M | PG_PS | pg_g | pg_nx);
		pde_store(pde, newpdir);
	}
	vm_page_array = (vm_page_t)start;
}