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
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ uint64_t ;
struct xen_add_to_physmap {int /*<<< orphan*/  gpfn; int /*<<< orphan*/  space; scalar_t__ idx; int /*<<< orphan*/  domid; } ;
struct hvm_start_info {scalar_t__ modlist_paddr; scalar_t__ nr_modules; int /*<<< orphan*/  flags; int /*<<< orphan*/  magic; } ;
struct hvm_modlist_entry {scalar_t__ paddr; } ;
typedef  int /*<<< orphan*/  shared_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_SELF ; 
 scalar_t__ HYPERVISOR_memory_op (int /*<<< orphan*/ ,struct xen_add_to_physmap*) ; 
 int /*<<< orphan*/ * HYPERVISOR_shared_info ; 
 int /*<<< orphan*/  HYPERVISOR_shutdown (int /*<<< orphan*/ ) ; 
 scalar_t__ KERNBASE ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  SHUTDOWN_crash ; 
 int /*<<< orphan*/  VM_GUEST_XEN ; 
 int /*<<< orphan*/  XENMAPSPACE_shared_info ; 
 int /*<<< orphan*/  XENMEM_add_to_physmap ; 
 int /*<<< orphan*/  XEN_HVM_DOMAIN ; 
 int /*<<< orphan*/  XEN_HVM_INIT_EARLY ; 
 int /*<<< orphan*/  XEN_HVM_START_MAGIC_VALUE ; 
 int /*<<< orphan*/  atop (scalar_t__) ; 
 int /*<<< orphan*/  bzero_early (char*,scalar_t__) ; 
 scalar_t__ hammer_time (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hvm_start_flags ; 
 int /*<<< orphan*/  init_ops ; 
 int /*<<< orphan*/  init_static_kenv (char*,scalar_t__) ; 
 scalar_t__ roundup2 (scalar_t__,scalar_t__) ; 
 struct hvm_start_info* start_info ; 
 int /*<<< orphan*/  vm_guest ; 
 int /*<<< orphan*/  xc_printf (char*,...) ; 
 int /*<<< orphan*/  xen_domain_type ; 
 int xen_hvm_init_hypercall_stubs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_pvh_init_ops ; 

uint64_t
hammer_time_xen(vm_paddr_t start_info_paddr)
{
	struct hvm_modlist_entry *mod;
	struct xen_add_to_physmap xatp;
	uint64_t physfree;
	char *kenv;
	int rc;

	xen_domain_type = XEN_HVM_DOMAIN;
	vm_guest = VM_GUEST_XEN;

	rc = xen_hvm_init_hypercall_stubs(XEN_HVM_INIT_EARLY);
	if (rc) {
		xc_printf("ERROR: failed to initialize hypercall page: %d\n",
		    rc);
		HYPERVISOR_shutdown(SHUTDOWN_crash);
	}

	start_info = (struct hvm_start_info *)(start_info_paddr + KERNBASE);
	if (start_info->magic != XEN_HVM_START_MAGIC_VALUE) {
		xc_printf("Unknown magic value in start_info struct: %#x\n",
		    start_info->magic);
		HYPERVISOR_shutdown(SHUTDOWN_crash);
	}

	/*
	 * The hvm_start_into structure is always appended after loading
	 * the kernel and modules.
	 */
	physfree = roundup2(start_info_paddr + PAGE_SIZE, PAGE_SIZE);

	xatp.domid = DOMID_SELF;
	xatp.idx = 0;
	xatp.space = XENMAPSPACE_shared_info;
	xatp.gpfn = atop(physfree);
	if (HYPERVISOR_memory_op(XENMEM_add_to_physmap, &xatp)) {
		xc_printf("ERROR: failed to setup shared_info page\n");
		HYPERVISOR_shutdown(SHUTDOWN_crash);
	}
	HYPERVISOR_shared_info = (shared_info_t *)(physfree + KERNBASE);
	physfree += PAGE_SIZE;

	/*
	 * Init a static kenv using a free page. The contents will be filled
	 * from the parse_preload_data hook.
	 */
	kenv = (void *)(physfree + KERNBASE);
	physfree += PAGE_SIZE;
	bzero_early(kenv, PAGE_SIZE);
	init_static_kenv(kenv, PAGE_SIZE);

	if (start_info->modlist_paddr != 0) {
		if (start_info->modlist_paddr >= physfree) {
			xc_printf(
			    "ERROR: unexpected module list memory address\n");
			HYPERVISOR_shutdown(SHUTDOWN_crash);
		}
		if (start_info->nr_modules == 0) {
			xc_printf(
			    "ERROR: modlist_paddr != 0 but nr_modules == 0\n");
			HYPERVISOR_shutdown(SHUTDOWN_crash);
		}
		mod = (struct hvm_modlist_entry *)
		    (vm_paddr_t)start_info->modlist_paddr + KERNBASE;
		if (mod[0].paddr >= physfree) {
			xc_printf("ERROR: unexpected module memory address\n");
			HYPERVISOR_shutdown(SHUTDOWN_crash);
		}
	}

	/* Set the hooks for early functions that diverge from bare metal */
	init_ops = xen_pvh_init_ops;
	hvm_start_flags = start_info->flags;

	/* Now we can jump into the native init function */
	return (hammer_time(0, physfree));
}