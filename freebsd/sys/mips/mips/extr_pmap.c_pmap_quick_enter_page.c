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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  void* vm_offset_t ;
typedef  int pt_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ MIPS_DIRECT_MAPPABLE (int /*<<< orphan*/ ) ; 
 void* MIPS_PHYS_TO_DIRECT (int /*<<< orphan*/ ) ; 
 void* MIPS_PHYS_TO_DIRECT_UNCACHED (int /*<<< orphan*/ ) ; 
 void* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_PTE_SET_CACHE_BITS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTE_D ; 
 int PTE_G ; 
 int PTE_V ; 
 int TLBLO_PA_TO_PFN (int /*<<< orphan*/ ) ; 
 scalar_t__ VM_MEMATTR_WRITE_BACK ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  critical_enter () ; 
 scalar_t__ pmap_page_get_memattr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qmap_addr ; 
 int /*<<< orphan*/  qmap_ptep ; 

vm_offset_t
pmap_quick_enter_page(vm_page_t m)
{
#if defined(__mips_n64)
	return MIPS_PHYS_TO_DIRECT(VM_PAGE_TO_PHYS(m));
#else
	vm_offset_t qaddr;
	vm_paddr_t pa;
	pt_entry_t *pte, npte;

	pa = VM_PAGE_TO_PHYS(m);

	if (MIPS_DIRECT_MAPPABLE(pa)) {
		if (pmap_page_get_memattr(m) != VM_MEMATTR_WRITE_BACK)
			return (MIPS_PHYS_TO_DIRECT_UNCACHED(pa));
		else
			return (MIPS_PHYS_TO_DIRECT(pa));
	}
	critical_enter();
	qaddr = PCPU_GET(qmap_addr);
	pte = PCPU_GET(qmap_ptep);

	KASSERT(*pte == PTE_G, ("pmap_quick_enter_page: PTE busy"));

	npte = TLBLO_PA_TO_PFN(pa) | PTE_D | PTE_V | PTE_G;
	PMAP_PTE_SET_CACHE_BITS(npte, pa, m);
	*pte = npte;

	return (qaddr);
#endif
}