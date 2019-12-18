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
typedef  scalar_t__ vm_size_t ;
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
struct vm_domain {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  v_page_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PROT_RW ; 
 int /*<<< orphan*/  kernel_arena ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  pmap_change_prot (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_kextract (scalar_t__) ; 
 int /*<<< orphan*/  pmap_remove (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ round_page (scalar_t__) ; 
 scalar_t__ trunc_page (scalar_t__) ; 
 TYPE_1__ vm_cnt ; 
 int /*<<< orphan*/  vm_domain_free_lock (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_domain_free_unlock (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_domain_freecnt_inc (struct vm_domain*,int) ; 
 struct vm_domain* vm_pagequeue_domain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_phys_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_add (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

void
kmem_bootstrap_free(vm_offset_t start, vm_size_t size)
{
#if defined(__i386__) || defined(__amd64__)
	struct vm_domain *vmd;
	vm_offset_t end, va;
	vm_paddr_t pa;
	vm_page_t m;

	end = trunc_page(start + size);
	start = round_page(start);

#ifdef __amd64__
	/*
	 * Preloaded files do not have execute permissions by default on amd64.
	 * Restore the default permissions to ensure that the direct map alias
	 * is updated.
	 */
	pmap_change_prot(start, end - start, VM_PROT_RW);
#endif
	for (va = start; va < end; va += PAGE_SIZE) {
		pa = pmap_kextract(va);
		m = PHYS_TO_VM_PAGE(pa);

		vmd = vm_pagequeue_domain(m);
		vm_domain_free_lock(vmd);
		vm_phys_free_pages(m, 0);
		vm_domain_free_unlock(vmd);

		vm_domain_freecnt_inc(vmd, 1);
		vm_cnt.v_page_count++;
	}
	pmap_remove(kernel_pmap, start, end);
	(void)vmem_add(kernel_arena, start, end - start, M_WAITOK);
#endif
}