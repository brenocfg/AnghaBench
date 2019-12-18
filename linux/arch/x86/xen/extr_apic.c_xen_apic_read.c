#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int apic_id; int /*<<< orphan*/  xen_cpuid; } ;
struct TYPE_3__ {TYPE_2__ pcpu_info; } ;
struct xen_platform_op {TYPE_1__ u; int /*<<< orphan*/  interface_version; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 scalar_t__ APIC_ID ; 
 scalar_t__ APIC_LDR ; 
 scalar_t__ APIC_LVR ; 
 int BAD_APICID ; 
 int HYPERVISOR_platform_op (struct xen_platform_op*) ; 
 scalar_t__ SET_APIC_LOGICAL_ID (unsigned long) ; 
 int /*<<< orphan*/  XENPF_INTERFACE_VERSION ; 
 int /*<<< orphan*/  XENPF_get_cpuinfo ; 
 unsigned long smp_processor_id () ; 
 int /*<<< orphan*/  xen_initial_domain () ; 

__attribute__((used)) static u32 xen_apic_read(u32 reg)
{
	struct xen_platform_op op = {
		.cmd = XENPF_get_cpuinfo,
		.interface_version = XENPF_INTERFACE_VERSION,
		.u.pcpu_info.xen_cpuid = 0,
	};
	int ret = 0;

	/* Shouldn't need this as APIC is turned off for PV, and we only
	 * get called on the bootup processor. But just in case. */
	if (!xen_initial_domain() || smp_processor_id())
		return 0;

	if (reg == APIC_LVR)
		return 0x14;
#ifdef CONFIG_X86_32
	if (reg == APIC_LDR)
		return SET_APIC_LOGICAL_ID(1UL << smp_processor_id());
#endif
	if (reg != APIC_ID)
		return 0;

	ret = HYPERVISOR_platform_op(&op);
	if (ret)
		op.u.pcpu_info.apic_id = BAD_APICID;

	return op.u.pcpu_info.apic_id << 24;
}