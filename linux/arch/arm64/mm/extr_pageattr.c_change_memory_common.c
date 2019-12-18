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
typedef  unsigned long u64 ;
struct vm_struct {unsigned long size; int flags; int nr_pages; int /*<<< orphan*/ * pages; scalar_t__ addr; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_ALIGNED (unsigned long) ; 
 unsigned long PAGE_MASK ; 
 int PAGE_SIZE ; 
 scalar_t__ PTE_RDONLY ; 
 int VM_ALLOC ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __change_memory_common (unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vm_struct* find_vm_area (void*) ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 
 scalar_t__ pgprot_val (int /*<<< orphan*/ ) ; 
 scalar_t__ rodata_full ; 
 int /*<<< orphan*/  vm_unmap_aliases () ; 

__attribute__((used)) static int change_memory_common(unsigned long addr, int numpages,
				pgprot_t set_mask, pgprot_t clear_mask)
{
	unsigned long start = addr;
	unsigned long size = PAGE_SIZE*numpages;
	unsigned long end = start + size;
	struct vm_struct *area;
	int i;

	if (!PAGE_ALIGNED(addr)) {
		start &= PAGE_MASK;
		end = start + size;
		WARN_ON_ONCE(1);
	}

	/*
	 * Kernel VA mappings are always live, and splitting live section
	 * mappings into page mappings may cause TLB conflicts. This means
	 * we have to ensure that changing the permission bits of the range
	 * we are operating on does not result in such splitting.
	 *
	 * Let's restrict ourselves to mappings created by vmalloc (or vmap).
	 * Those are guaranteed to consist entirely of page mappings, and
	 * splitting is never needed.
	 *
	 * So check whether the [addr, addr + size) interval is entirely
	 * covered by precisely one VM area that has the VM_ALLOC flag set.
	 */
	area = find_vm_area((void *)addr);
	if (!area ||
	    end > (unsigned long)area->addr + area->size ||
	    !(area->flags & VM_ALLOC))
		return -EINVAL;

	if (!numpages)
		return 0;

	/*
	 * If we are manipulating read-only permissions, apply the same
	 * change to the linear mapping of the pages that back this VM area.
	 */
	if (rodata_full && (pgprot_val(set_mask) == PTE_RDONLY ||
			    pgprot_val(clear_mask) == PTE_RDONLY)) {
		for (i = 0; i < area->nr_pages; i++) {
			__change_memory_common((u64)page_address(area->pages[i]),
					       PAGE_SIZE, set_mask, clear_mask);
		}
	}

	/*
	 * Get rid of potentially aliasing lazily unmapped vm areas that may
	 * have permissions set that deviate from the ones we are setting here.
	 */
	vm_unmap_aliases();

	return __change_memory_common(start, size, set_mask, clear_mask);
}