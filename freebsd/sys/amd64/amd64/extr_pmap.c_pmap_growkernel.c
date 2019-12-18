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
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int vm_paddr_t ;
typedef  int vm_offset_t ;
typedef  int pdp_entry_t ;
typedef  int pd_entry_t ;
struct TYPE_8__ {int /*<<< orphan*/  system_mtx; } ;
struct TYPE_7__ {int flags; } ;

/* Variables and functions */
 int KERNBASE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int NBPDR ; 
 int PDPSHIFT ; 
 int PDRMASK ; 
 int PG_ZERO ; 
 int VM_ALLOC_INTERRUPT ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_WIRED ; 
 int VM_ALLOC_ZERO ; 
 int VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 int X86_PG_A ; 
 int X86_PG_M ; 
 int X86_PG_RW ; 
 int X86_PG_V ; 
 TYPE_3__* kernel_map ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int kernel_vm_end ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nkpt ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pde_store (int*,int) ; 
 int pmap_pde_pindex (int) ; 
 int* pmap_pdpe (int /*<<< orphan*/ ,int) ; 
 int* pmap_pdpe_to_pde (int*,int) ; 
 int /*<<< orphan*/  pmap_zero_page (TYPE_1__*) ; 
 int roundup2 (int,int) ; 
 int vm_map_max (TYPE_3__*) ; 
 TYPE_1__* vm_page_alloc (int /*<<< orphan*/ *,int,int) ; 

void
pmap_growkernel(vm_offset_t addr)
{
	vm_paddr_t paddr;
	vm_page_t nkpg;
	pd_entry_t *pde, newpdir;
	pdp_entry_t *pdpe;

	mtx_assert(&kernel_map->system_mtx, MA_OWNED);

	/*
	 * Return if "addr" is within the range of kernel page table pages
	 * that were preallocated during pmap bootstrap.  Moreover, leave
	 * "kernel_vm_end" and the kernel page table as they were.
	 *
	 * The correctness of this action is based on the following
	 * argument: vm_map_insert() allocates contiguous ranges of the
	 * kernel virtual address space.  It calls this function if a range
	 * ends after "kernel_vm_end".  If the kernel is mapped between
	 * "kernel_vm_end" and "addr", then the range cannot begin at
	 * "kernel_vm_end".  In fact, its beginning address cannot be less
	 * than the kernel.  Thus, there is no immediate need to allocate
	 * any new kernel page table pages between "kernel_vm_end" and
	 * "KERNBASE".
	 */
	if (KERNBASE < addr && addr <= KERNBASE + nkpt * NBPDR)
		return;

	addr = roundup2(addr, NBPDR);
	if (addr - 1 >= vm_map_max(kernel_map))
		addr = vm_map_max(kernel_map);
	while (kernel_vm_end < addr) {
		pdpe = pmap_pdpe(kernel_pmap, kernel_vm_end);
		if ((*pdpe & X86_PG_V) == 0) {
			/* We need a new PDP entry */
			nkpg = vm_page_alloc(NULL, kernel_vm_end >> PDPSHIFT,
			    VM_ALLOC_INTERRUPT | VM_ALLOC_NOOBJ |
			    VM_ALLOC_WIRED | VM_ALLOC_ZERO);
			if (nkpg == NULL)
				panic("pmap_growkernel: no memory to grow kernel");
			if ((nkpg->flags & PG_ZERO) == 0)
				pmap_zero_page(nkpg);
			paddr = VM_PAGE_TO_PHYS(nkpg);
			*pdpe = (pdp_entry_t)(paddr | X86_PG_V | X86_PG_RW |
			    X86_PG_A | X86_PG_M);
			continue; /* try again */
		}
		pde = pmap_pdpe_to_pde(pdpe, kernel_vm_end);
		if ((*pde & X86_PG_V) != 0) {
			kernel_vm_end = (kernel_vm_end + NBPDR) & ~PDRMASK;
			if (kernel_vm_end - 1 >= vm_map_max(kernel_map)) {
				kernel_vm_end = vm_map_max(kernel_map);
				break;                       
			}
			continue;
		}

		nkpg = vm_page_alloc(NULL, pmap_pde_pindex(kernel_vm_end),
		    VM_ALLOC_INTERRUPT | VM_ALLOC_NOOBJ | VM_ALLOC_WIRED |
		    VM_ALLOC_ZERO);
		if (nkpg == NULL)
			panic("pmap_growkernel: no memory to grow kernel");
		if ((nkpg->flags & PG_ZERO) == 0)
			pmap_zero_page(nkpg);
		paddr = VM_PAGE_TO_PHYS(nkpg);
		newpdir = paddr | X86_PG_V | X86_PG_RW | X86_PG_A | X86_PG_M;
		pde_store(pde, newpdir);

		kernel_vm_end = (kernel_vm_end + NBPDR) & ~PDRMASK;
		if (kernel_vm_end - 1 >= vm_map_max(kernel_map)) {
			kernel_vm_end = vm_map_max(kernel_map);
			break;                       
		}
	}
}