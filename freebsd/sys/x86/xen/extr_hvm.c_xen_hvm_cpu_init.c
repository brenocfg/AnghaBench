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
typedef  int uint32_t ;
struct vcpu_register_vcpu_info {int mfn; scalar_t__ offset; } ;
struct vcpu_info {int dummy; } ;
struct TYPE_2__ {struct vcpu_info* vcpu_info; } ;

/* Variables and functions */
 int /*<<< orphan*/ * DPCPU_GET (struct vcpu_info*) ; 
 struct vcpu_info* DPCPU_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPCPU_SET (struct vcpu_info*,struct vcpu_info*) ; 
 TYPE_1__* HYPERVISOR_shared_info ; 
 int HYPERVISOR_vcpu_op (int /*<<< orphan*/ ,int,struct vcpu_register_vcpu_info*) ; 
 int /*<<< orphan*/  IS_BSP () ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PAGE_SHIFT ; 
 int PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VCPUOP_register_vcpu_info ; 
 int XEN_HVM_CPUID_VCPU_ID_PRESENT ; 
 int /*<<< orphan*/  acpi_id ; 
 scalar_t__ cpuid_base ; 
 int /*<<< orphan*/  cpuid_count (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int set_percpu_callback (int) ; 
 scalar_t__ trunc_page (int) ; 
 int /*<<< orphan*/  vcpu_id ; 
 int /*<<< orphan*/  vcpu_local_info ; 
 int vtophys (struct vcpu_info*) ; 
 int /*<<< orphan*/  xen_domain () ; 
 scalar_t__ xen_evtchn_needs_ack ; 
 int /*<<< orphan*/  xen_pv_domain () ; 

__attribute__((used)) static void
xen_hvm_cpu_init(void)
{
	struct vcpu_register_vcpu_info info;
	struct vcpu_info *vcpu_info;
	uint32_t regs[4];
	int cpu, rc;

	if (!xen_domain())
		return;

	if (DPCPU_GET(vcpu_info) != NULL) {
		/*
		 * vcpu_info is already set.  We're resuming
		 * from a failed migration and our pre-suspend
		 * configuration is still valid.
		 */
		return;
	}

	/*
	 * Set vCPU ID. If available fetch the ID from CPUID, if not just use
	 * the ACPI ID.
	 */
	KASSERT(cpuid_base != 0, ("Invalid base Xen CPUID leaf"));
	cpuid_count(cpuid_base + 4, 0, regs);
	KASSERT((regs[0] & XEN_HVM_CPUID_VCPU_ID_PRESENT) ||
	    !xen_pv_domain(),
	    ("Xen PV domain without vcpu_id in cpuid"));
	PCPU_SET(vcpu_id, (regs[0] & XEN_HVM_CPUID_VCPU_ID_PRESENT) ?
	    regs[1] : PCPU_GET(acpi_id));

	if (xen_evtchn_needs_ack && !IS_BSP()) {
		/*
		 * Setup the per-vpcu event channel upcall vector. This is only
		 * required when using the new HVMOP_set_evtchn_upcall_vector
		 * hypercall, which allows using a different vector for each
		 * vCPU. Note that FreeBSD uses the same vector for all vCPUs
		 * because it's not dynamically allocated.
		 */
		rc = set_percpu_callback(PCPU_GET(vcpu_id));
		if (rc != 0)
			panic("Event channel upcall vector setup failed: %d",
			    rc);
	}

	/*
	 * Set the vCPU info.
	 *
	 * NB: the vCPU info for vCPUs < 32 can be fetched from the shared info
	 * page, but in order to make sure the mapping code is correct always
	 * attempt to map the vCPU info at a custom place.
	 */
	vcpu_info = DPCPU_PTR(vcpu_local_info);
	cpu = PCPU_GET(vcpu_id);
	info.mfn = vtophys(vcpu_info) >> PAGE_SHIFT;
	info.offset = vtophys(vcpu_info) - trunc_page(vtophys(vcpu_info));

	rc = HYPERVISOR_vcpu_op(VCPUOP_register_vcpu_info, cpu, &info);
	if (rc != 0)
		DPCPU_SET(vcpu_info, &HYPERVISOR_shared_info->vcpu_info[cpu]);
	else
		DPCPU_SET(vcpu_info, vcpu_info);
}