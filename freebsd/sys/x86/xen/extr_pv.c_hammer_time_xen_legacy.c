#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ u_int64_t ;
struct TYPE_4__ {scalar_t__ shared_info; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ start_info_t ;
typedef  int /*<<< orphan*/  shared_info_t ;

/* Variables and functions */
 int /*<<< orphan*/ * HYPERVISOR_shared_info ; 
 int /*<<< orphan*/  HYPERVISOR_shutdown (int /*<<< orphan*/ ) ; 
 scalar_t__ KERNBASE ; 
 int PAGE_SIZE ; 
 scalar_t__ PG_PS ; 
 scalar_t__ PG_RW ; 
 scalar_t__ PG_U ; 
 scalar_t__ PG_V ; 
 int /*<<< orphan*/  SHUTDOWN_crash ; 
 int /*<<< orphan*/  VM_GUEST_XEN ; 
 int /*<<< orphan*/  XEN_PV_DOMAIN ; 
 int /*<<< orphan*/  apic_ops ; 
 int /*<<< orphan*/  bzero_early (char*,int) ; 
 scalar_t__ hammer_time (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hypervisor_info ; 
 int /*<<< orphan*/  init_ops ; 
 int /*<<< orphan*/  init_static_kenv (char*,int) ; 
 int /*<<< orphan*/  legacy_info ; 
 TYPE_1__* legacy_start_info ; 
 int /*<<< orphan*/  load_cr3 (scalar_t__) ; 
 int /*<<< orphan*/  vm_guest ; 
 int /*<<< orphan*/  xc_printf (char*,...) ; 
 int /*<<< orphan*/  xen_apic_ops ; 
 int /*<<< orphan*/  xen_domain_type ; 
 int /*<<< orphan*/  xen_legacy_init_ops ; 

uint64_t
hammer_time_xen_legacy(start_info_t *si, uint64_t xenstack)
{
	uint64_t physfree;
	uint64_t *PT4 = (u_int64_t *)xenstack;
	uint64_t *PT3 = (u_int64_t *)(xenstack + PAGE_SIZE);
	uint64_t *PT2 = (u_int64_t *)(xenstack + 2 * PAGE_SIZE);
	int i;
	char *kenv;

	xen_domain_type = XEN_PV_DOMAIN;
	vm_guest = VM_GUEST_XEN;

	if ((si == NULL) || (xenstack == 0)) {
		xc_printf("ERROR: invalid start_info or xen stack, halting\n");
		HYPERVISOR_shutdown(SHUTDOWN_crash);
	}

	xc_printf("FreeBSD PVH running on %s\n", si->magic);

	/* We use 3 pages of xen stack for the boot pagetables */
	physfree = xenstack + 3 * PAGE_SIZE - KERNBASE;

	/* Setup Xen global variables */
	legacy_start_info = si;
	HYPERVISOR_shared_info =
	    (shared_info_t *)(si->shared_info + KERNBASE);

	/*
	 * Use the stack Xen gives us to build the page tables
	 * as native FreeBSD expects to find them (created
	 * by the boot trampoline).
	 */
	for (i = 0; i < (PAGE_SIZE / sizeof(uint64_t)); i++) {
		/*
		 * Each slot of the level 4 pages points
		 * to the same level 3 page
		 */
		PT4[i] = ((uint64_t)&PT3[0]) - KERNBASE;
		PT4[i] |= PG_V | PG_RW | PG_U;

		/*
		 * Each slot of the level 3 pages points
		 * to the same level 2 page
		 */
		PT3[i] = ((uint64_t)&PT2[0]) - KERNBASE;
		PT3[i] |= PG_V | PG_RW | PG_U;

		/*
		 * The level 2 page slots are mapped with
		 * 2MB pages for 1GB.
		 */
		PT2[i] = i * (2 * 1024 * 1024);
		PT2[i] |= PG_V | PG_RW | PG_PS | PG_U;
	}
	load_cr3(((uint64_t)&PT4[0]) - KERNBASE);

	/*
	 * Init an empty static kenv using a free page. The contents will be
	 * filled from the parse_preload_data hook.
	 */
	kenv = (void *)(physfree + KERNBASE);
	physfree += PAGE_SIZE;
	bzero_early(kenv, PAGE_SIZE);
	init_static_kenv(kenv, PAGE_SIZE);

	/* Set the hooks for early functions that diverge from bare metal */
	init_ops = xen_legacy_init_ops;
	apic_ops = xen_apic_ops;
	hypervisor_info = legacy_info;

	/* Now we can jump into the native init function */
	return (hammer_time(0, physfree));
}