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
typedef  int vm_paddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PAGE_MASK ; 
 int VM_DMA32_BOUNDARY ; 
 int VM_LOWMEM_BOUNDARY ; 
 int /*<<< orphan*/  vm_phys_create_seg (int,int) ; 

void
vm_phys_add_seg(vm_paddr_t start, vm_paddr_t end)
{
	vm_paddr_t paddr;

	KASSERT((start & PAGE_MASK) == 0,
	    ("vm_phys_define_seg: start is not page aligned"));
	KASSERT((end & PAGE_MASK) == 0,
	    ("vm_phys_define_seg: end is not page aligned"));

	/*
	 * Split the physical memory segment if it spans two or more free
	 * list boundaries.
	 */
	paddr = start;
#ifdef	VM_FREELIST_LOWMEM
	if (paddr < VM_LOWMEM_BOUNDARY && end > VM_LOWMEM_BOUNDARY) {
		vm_phys_create_seg(paddr, VM_LOWMEM_BOUNDARY);
		paddr = VM_LOWMEM_BOUNDARY;
	}
#endif
#ifdef	VM_FREELIST_DMA32
	if (paddr < VM_DMA32_BOUNDARY && end > VM_DMA32_BOUNDARY) {
		vm_phys_create_seg(paddr, VM_DMA32_BOUNDARY);
		paddr = VM_DMA32_BOUNDARY;
	}
#endif
	vm_phys_create_seg(paddr, end);
}