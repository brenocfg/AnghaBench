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
struct xen_add_to_physmap {int gpfn; int /*<<< orphan*/  space; scalar_t__ idx; int /*<<< orphan*/  domid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_SELF ; 
 scalar_t__ HYPERVISOR_memory_op (int /*<<< orphan*/ ,struct xen_add_to_physmap*) ; 
 int /*<<< orphan*/ * HYPERVISOR_shared_info ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_XENHVM ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  XENMAPSPACE_shared_info ; 
 int /*<<< orphan*/  XENMEM_add_to_physmap ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int vtophys (int /*<<< orphan*/ *) ; 
 scalar_t__ xen_pv_domain () ; 

__attribute__((used)) static void
xen_hvm_init_shared_info_page(void)
{
	struct xen_add_to_physmap xatp;

	if (xen_pv_domain()) {
		/*
		 * Already setup in the PV case, shared_info is passed inside
		 * of the start_info struct at start of day.
		 */
		return;
	}

	if (HYPERVISOR_shared_info == NULL) {
		HYPERVISOR_shared_info = malloc(PAGE_SIZE, M_XENHVM, M_NOWAIT);
		if (HYPERVISOR_shared_info == NULL)
			panic("Unable to allocate Xen shared info page");
	}

	xatp.domid = DOMID_SELF;
	xatp.idx = 0;
	xatp.space = XENMAPSPACE_shared_info;
	xatp.gpfn = vtophys(HYPERVISOR_shared_info) >> PAGE_SHIFT;
	if (HYPERVISOR_memory_op(XENMEM_add_to_physmap, &xatp))
		panic("HYPERVISOR_memory_op failed");
}