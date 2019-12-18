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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int M_BESTFIT ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PHYS_IN_DMAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHYS_TO_DMAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  kernel_arena ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  sched_pin () ; 
 int vmem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

boolean_t
pmap_map_io_transient(vm_page_t page[], vm_offset_t vaddr[], int count,
    boolean_t can_fault)
{
	vm_paddr_t paddr;
	boolean_t needs_mapping;
	int error, i;

	/*
	 * Allocate any KVA space that we need, this is done in a separate
	 * loop to prevent calling vmem_alloc while pinned.
	 */
	needs_mapping = FALSE;
	for (i = 0; i < count; i++) {
		paddr = VM_PAGE_TO_PHYS(page[i]);
		if (__predict_false(!PHYS_IN_DMAP(paddr))) {
			error = vmem_alloc(kernel_arena, PAGE_SIZE,
			    M_BESTFIT | M_WAITOK, &vaddr[i]);
			KASSERT(error == 0, ("vmem_alloc failed: %d", error));
			needs_mapping = TRUE;
		} else {
			vaddr[i] = PHYS_TO_DMAP(paddr);
		}
	}

	/* Exit early if everything is covered by the DMAP */
	if (!needs_mapping)
		return (FALSE);

	if (!can_fault)
		sched_pin();
	for (i = 0; i < count; i++) {
		paddr = VM_PAGE_TO_PHYS(page[i]);
		if (!PHYS_IN_DMAP(paddr)) {
			panic(
			   "pmap_map_io_transient: TODO: Map out of DMAP data");
		}
	}

	return (needs_mapping);
}