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
typedef  scalar_t__ vm_offset_t ;
struct xen_add_to_physmap {unsigned int idx; unsigned int gpfn; int /*<<< orphan*/  space; int /*<<< orphan*/  domid; } ;
typedef  int /*<<< orphan*/  grant_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_SELF ; 
 scalar_t__ HYPERVISOR_memory_op (int /*<<< orphan*/ ,struct xen_add_to_physmap*) ; 
 int /*<<< orphan*/  KASSERT (scalar_t__,char*) ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  XENMAPSPACE_grant_table ; 
 int /*<<< orphan*/  XENMEM_add_to_physmap ; 
 scalar_t__ kva_alloc (unsigned int) ; 
 unsigned int max_nr_grant_frames () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_kenter (scalar_t__,unsigned int) ; 
 unsigned int resume_frames ; 
 int /*<<< orphan*/ * shared ; 

__attribute__((used)) static int
gnttab_map(unsigned int start_idx, unsigned int end_idx)
{
	struct xen_add_to_physmap xatp;
	unsigned int i = end_idx;

	/*
	 * Loop backwards, so that the first hypercall has the largest index,
	 * ensuring that the table will grow only once.
	 */
	do {
		xatp.domid = DOMID_SELF;
		xatp.idx = i;
		xatp.space = XENMAPSPACE_grant_table;
		xatp.gpfn = (resume_frames >> PAGE_SHIFT) + i;
		if (HYPERVISOR_memory_op(XENMEM_add_to_physmap, &xatp))
			panic("HYPERVISOR_memory_op failed to map gnttab");
	} while (i-- > start_idx);

	if (shared == NULL) {
		vm_offset_t area;

		area = kva_alloc(PAGE_SIZE * max_nr_grant_frames());
		KASSERT(area, ("can't allocate VM space for grant table"));
		shared = (grant_entry_t *)area;
	}

	for (i = start_idx; i <= end_idx; i++) {
		pmap_kenter((vm_offset_t) shared + i * PAGE_SIZE,
		    resume_frames + i * PAGE_SIZE);
	}

	return (0);
}