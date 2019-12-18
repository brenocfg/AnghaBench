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

/* Variables and functions */
 int /*<<< orphan*/  domainset_init () ; 
 int /*<<< orphan*/  domainset_zero () ; 
 int /*<<< orphan*/  kmem_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_init_zero_region () ; 
 int /*<<< orphan*/  pmap_init () ; 
 int /*<<< orphan*/  uma_startup1 () ; 
 int /*<<< orphan*/  uma_startup2 () ; 
 int /*<<< orphan*/  virtual_avail ; 
 int /*<<< orphan*/  virtual_end ; 
 int /*<<< orphan*/  vm_map_startup () ; 
 int /*<<< orphan*/  vm_object_init () ; 
 int /*<<< orphan*/  vm_page_startup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_pager_init () ; 
 int /*<<< orphan*/  vm_radix_reserve_kva () ; 
 int /*<<< orphan*/  vm_set_page_size () ; 
 int /*<<< orphan*/  vmem_startup () ; 

__attribute__((used)) static void
vm_mem_init(void *dummy)
{

	/*
	 * Initialize static domainsets, used by various allocators.
	 */
	domainset_init();

	/*
	 * Initialize resident memory structures.  From here on, all physical
	 * memory is accounted for, and we use only virtual addresses.
	 */
	vm_set_page_size();
	virtual_avail = vm_page_startup(virtual_avail);

	/*
	 * Set an initial domain policy for thread0 so that allocations
	 * can work.
	 */
	domainset_zero();

#ifdef	UMA_MD_SMALL_ALLOC
	/* Announce page availability to UMA. */
	uma_startup1();
#endif
	/*
	 * Initialize other VM packages
	 */
	vmem_startup();
	vm_object_init();
	vm_map_startup();
	kmem_init(virtual_avail, virtual_end);

#ifndef	UMA_MD_SMALL_ALLOC
	/* Set up radix zone to use noobj_alloc. */
	vm_radix_reserve_kva();
#endif
	/* Announce full page availability to UMA. */
	uma_startup2();
	kmem_init_zero_region();
	pmap_init();
	vm_pager_init();
}