#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vmem_release_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_1__* vm_map_t ;
struct vm_page {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/ * vmd_kernel_rwx_arena; int /*<<< orphan*/ * vmd_kernel_arena; } ;
struct TYPE_8__ {int system_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERNBASE ; 
 int /*<<< orphan*/  KVA_QUANTUM ; 
 int /*<<< orphan*/  MAP_NOFAULT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  VM_MIN_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  VM_PROT_ALL ; 
 int /*<<< orphan*/  VM_PROT_RW ; 
 int /*<<< orphan*/ * kernel_arena ; 
 TYPE_1__* kernel_map ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  kva_import ; 
 int /*<<< orphan*/  kva_import_domain ; 
 scalar_t__ round_2mpage (int) ; 
 TYPE_6__* vm_dom ; 
 TYPE_1__* vm_map_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_insert (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_1__*) ; 
 int vm_ndomains ; 
 scalar_t__ vm_page_array ; 
 int vm_page_array_size ; 
 void* vmem_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_set_import (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vmem_xfree ; 

void
kmem_init(vm_offset_t start, vm_offset_t end)
{
	vm_map_t m;
	int domain;

	m = vm_map_create(kernel_pmap, VM_MIN_KERNEL_ADDRESS, end);
	m->system_map = 1;
	vm_map_lock(m);
	/* N.B.: cannot use kgdb to debug, starting with this assignment ... */
	kernel_map = m;
	(void)vm_map_insert(m, NULL, 0,
#ifdef __amd64__
	    KERNBASE,
#else		     
	    VM_MIN_KERNEL_ADDRESS,
#endif
	    start, VM_PROT_ALL, VM_PROT_ALL, MAP_NOFAULT);
	/* ... and ending with the completion of the above `insert' */

#ifdef __amd64__
	/*
	 * Mark KVA used for the page array as allocated.  Other platforms
	 * that handle vm_page_array allocation can simply adjust virtual_avail
	 * instead.
	 */
	(void)vm_map_insert(m, NULL, 0, (vm_offset_t)vm_page_array,
	    (vm_offset_t)vm_page_array + round_2mpage(vm_page_array_size *
	    sizeof(struct vm_page)),
	    VM_PROT_RW, VM_PROT_RW, MAP_NOFAULT);
#endif
	vm_map_unlock(m);

	/*
	 * Initialize the kernel_arena.  This can grow on demand.
	 */
	vmem_init(kernel_arena, "kernel arena", 0, 0, PAGE_SIZE, 0, 0);
	vmem_set_import(kernel_arena, kva_import, NULL, NULL, KVA_QUANTUM);

	for (domain = 0; domain < vm_ndomains; domain++) {
		/*
		 * Initialize the per-domain arenas.  These are used to color
		 * the KVA space in a way that ensures that virtual large pages
		 * are backed by memory from the same physical domain,
		 * maximizing the potential for superpage promotion.
		 */
		vm_dom[domain].vmd_kernel_arena = vmem_create(
		    "kernel arena domain", 0, 0, PAGE_SIZE, 0, M_WAITOK);
		vmem_set_import(vm_dom[domain].vmd_kernel_arena,
		    kva_import_domain, NULL, kernel_arena, KVA_QUANTUM);

		/*
		 * In architectures with superpages, maintain separate arenas
		 * for allocations with permissions that differ from the
		 * "standard" read/write permissions used for kernel memory,
		 * so as not to inhibit superpage promotion.
		 */
#if VM_NRESERVLEVEL > 0
		vm_dom[domain].vmd_kernel_rwx_arena = vmem_create(
		    "kernel rwx arena domain", 0, 0, PAGE_SIZE, 0, M_WAITOK);
		vmem_set_import(vm_dom[domain].vmd_kernel_rwx_arena,
		    kva_import_domain, (vmem_release_t *)vmem_xfree,
		    kernel_arena, KVA_QUANTUM);
#endif
	}
}