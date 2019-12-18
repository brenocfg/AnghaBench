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
typedef  int uint32_t ;
typedef  enum xen_hvm_init_type { ____Placeholder_xen_hvm_init_type } xen_hvm_init_type ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ KERNBASE ; 
 int XEN_HVM_INIT_EARLY ; 
 int XEN_HVM_INIT_LATE ; 
 scalar_t__ cpuid_base ; 
 int /*<<< orphan*/  do_cpuid (scalar_t__,int*) ; 
 int /*<<< orphan*/  hypercall_page ; 
 int /*<<< orphan*/  hypervisor_version () ; 
 scalar_t__ vtophys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrmsr (int,scalar_t__) ; 
 scalar_t__ xen_domain () ; 
 scalar_t__ xen_hvm_cpuid_base () ; 

int
xen_hvm_init_hypercall_stubs(enum xen_hvm_init_type init_type)
{
	uint32_t regs[4];

	/* Legacy PVH will get here without the cpuid leaf being set. */
	if (cpuid_base == 0)
		cpuid_base = xen_hvm_cpuid_base();
	if (cpuid_base == 0)
		return (ENXIO);

	if (xen_domain() && init_type == XEN_HVM_INIT_LATE) {
		/*
		 * If the domain type is already set we can assume that the
		 * hypercall page has been populated too, so just print the
		 * version (and apply any quirks) and exit.
		 */
		hypervisor_version();
		return 0;
	}

	if (init_type == XEN_HVM_INIT_LATE)
		hypervisor_version();

	/*
	 * Find the hypercall pages.
	 */
	do_cpuid(cpuid_base + 2, regs);
	if (regs[0] != 1)
		return (EINVAL);

	wrmsr(regs[1], (init_type == XEN_HVM_INIT_EARLY)
	    ? ((vm_paddr_t)&hypercall_page - KERNBASE)
	    : vtophys(&hypercall_page));

	return (0);
}