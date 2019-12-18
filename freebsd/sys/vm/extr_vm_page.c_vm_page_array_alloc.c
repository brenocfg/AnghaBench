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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct vm_page {int dummy; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 scalar_t__ pmap_map (int /*<<< orphan*/ *,int,int,int) ; 
 int trunc_page (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_array ; 
 int vm_page_array_size ; 

__attribute__((used)) static vm_paddr_t
vm_page_array_alloc(vm_offset_t *vaddr, vm_paddr_t end, vm_paddr_t page_range)
{
	vm_paddr_t new_end;

	/*
	 * Reserve an unmapped guard page to trap access to vm_page_array[-1].
	 * However, because this page is allocated from KVM, out-of-bounds
	 * accesses using the direct map will not be trapped.
	 */
	*vaddr += PAGE_SIZE;

	/*
	 * Allocate physical memory for the page structures, and map it.
	 */
	new_end = trunc_page(end - page_range * sizeof(struct vm_page));
	vm_page_array = (vm_page_t)pmap_map(vaddr, new_end, end,
	    VM_PROT_READ | VM_PROT_WRITE);
	vm_page_array_size = page_range;

	return (new_end);
}