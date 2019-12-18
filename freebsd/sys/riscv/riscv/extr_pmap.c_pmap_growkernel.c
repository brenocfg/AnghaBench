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
typedef  int pt_entry_t ;
typedef  int pn_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;
struct TYPE_8__ {int /*<<< orphan*/  system_mtx; } ;
struct TYPE_7__ {int flags; } ;

/* Variables and functions */
 int L1_SHIFT ; 
 int L2_OFFSET ; 
 int L2_SHIFT ; 
 int L2_SIZE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int PAGE_SIZE ; 
 int PG_ZERO ; 
 int PTE_PPN0_S ; 
 int PTE_RWX ; 
 int PTE_V ; 
 int VM_ALLOC_INTERRUPT ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_WIRED ; 
 int VM_ALLOC_ZERO ; 
 int VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 TYPE_3__* kernel_map ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int kernel_vm_end ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_distribute_l1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_invalidate_page (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pmap_l1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_l1_index (int) ; 
 int /*<<< orphan*/ * pmap_l1_to_l2 (int /*<<< orphan*/ *,int) ; 
 int pmap_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pmap_zero_page (TYPE_1__*) ; 
 int roundup2 (int,int) ; 
 int vm_map_max (TYPE_3__*) ; 
 TYPE_1__* vm_page_alloc (int /*<<< orphan*/ *,int,int) ; 

void
pmap_growkernel(vm_offset_t addr)
{
	vm_paddr_t paddr;
	vm_page_t nkpg;
	pd_entry_t *l1, *l2;
	pt_entry_t entry;
	pn_t pn;

	mtx_assert(&kernel_map->system_mtx, MA_OWNED);

	addr = roundup2(addr, L2_SIZE);
	if (addr - 1 >= vm_map_max(kernel_map))
		addr = vm_map_max(kernel_map);
	while (kernel_vm_end < addr) {
		l1 = pmap_l1(kernel_pmap, kernel_vm_end);
		if (pmap_load(l1) == 0) {
			/* We need a new PDP entry */
			nkpg = vm_page_alloc(NULL, kernel_vm_end >> L1_SHIFT,
			    VM_ALLOC_INTERRUPT | VM_ALLOC_NOOBJ |
			    VM_ALLOC_WIRED | VM_ALLOC_ZERO);
			if (nkpg == NULL)
				panic("pmap_growkernel: no memory to grow kernel");
			if ((nkpg->flags & PG_ZERO) == 0)
				pmap_zero_page(nkpg);
			paddr = VM_PAGE_TO_PHYS(nkpg);

			pn = (paddr / PAGE_SIZE);
			entry = (PTE_V);
			entry |= (pn << PTE_PPN0_S);
			pmap_store(l1, entry);
			pmap_distribute_l1(kernel_pmap,
			    pmap_l1_index(kernel_vm_end), entry);
			continue; /* try again */
		}
		l2 = pmap_l1_to_l2(l1, kernel_vm_end);
		if ((pmap_load(l2) & PTE_V) != 0 &&
		    (pmap_load(l2) & PTE_RWX) == 0) {
			kernel_vm_end = (kernel_vm_end + L2_SIZE) & ~L2_OFFSET;
			if (kernel_vm_end - 1 >= vm_map_max(kernel_map)) {
				kernel_vm_end = vm_map_max(kernel_map);
				break;
			}
			continue;
		}

		nkpg = vm_page_alloc(NULL, kernel_vm_end >> L2_SHIFT,
		    VM_ALLOC_INTERRUPT | VM_ALLOC_NOOBJ | VM_ALLOC_WIRED |
		    VM_ALLOC_ZERO);
		if (nkpg == NULL)
			panic("pmap_growkernel: no memory to grow kernel");
		if ((nkpg->flags & PG_ZERO) == 0) {
			pmap_zero_page(nkpg);
		}
		paddr = VM_PAGE_TO_PHYS(nkpg);

		pn = (paddr / PAGE_SIZE);
		entry = (PTE_V);
		entry |= (pn << PTE_PPN0_S);
		pmap_store(l2, entry);

		pmap_invalidate_page(kernel_pmap, kernel_vm_end);

		kernel_vm_end = (kernel_vm_end + L2_SIZE) & ~L2_OFFSET;
		if (kernel_vm_end - 1 >= vm_map_max(kernel_map)) {
			kernel_vm_end = vm_map_max(kernel_map);
			break;                       
		}
	}
}