#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_3__ {scalar_t__ vm_guest; int /*<<< orphan*/  vm_cpuid; } ;

/* Variables and functions */
 scalar_t__ VM_GUEST_VM ; 
 int /*<<< orphan*/  do_cpuid (int,int*) ; 
 int hv_base ; 
 int hv_high ; 
 char* hv_vendor ; 
 int nitems (TYPE_1__*) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* vm_cpuids ; 
 scalar_t__ vm_guest ; 

__attribute__((used)) static void
identify_hypervisor_cpuid_base(void)
{
	u_int leaf, regs[4];
	int i;

	/*
	 * [RFC] CPUID usage for interaction between Hypervisors and Linux.
	 * http://lkml.org/lkml/2008/10/1/246
	 *
	 * KB1009458: Mechanisms to determine if software is running in
	 * a VMware virtual machine
	 * http://kb.vmware.com/kb/1009458
	 *
	 * Search for a hypervisor that we recognize. If we cannot find
	 * a specific hypervisor, return the first information about the
	 * hypervisor that we found, as others may be able to use.
	 */
	for (leaf = 0x40000000; leaf < 0x40010000; leaf += 0x100) {
		do_cpuid(leaf, regs);

		/*
		 * KVM from Linux kernels prior to commit
		 * 57c22e5f35aa4b9b2fe11f73f3e62bbf9ef36190 set %eax
		 * to 0 rather than a valid hv_high value.  Check for
		 * the KVM signature bytes and fixup %eax to the
		 * highest supported leaf in that case.
		 */
		if (regs[0] == 0 && regs[1] == 0x4b4d564b &&
		    regs[2] == 0x564b4d56 && regs[3] == 0x0000004d)
			regs[0] = leaf + 1;
			
		if (regs[0] >= leaf) {
			for (i = 0; i < nitems(vm_cpuids); i++)
				if (strncmp((const char *)&regs[1],
				    vm_cpuids[i].vm_cpuid, 12) == 0) {
					vm_guest = vm_cpuids[i].vm_guest;
					break;
				}

			/*
			 * If this is the first entry or we found a
			 * specific hypervisor, record the base, high value,
			 * and vendor identifier.
			 */
			if (vm_guest != VM_GUEST_VM || leaf == 0x40000000) {
				hv_base = leaf;
				hv_high = regs[0];
				((u_int *)&hv_vendor)[0] = regs[1];
				((u_int *)&hv_vendor)[1] = regs[2];
				((u_int *)&hv_vendor)[2] = regs[3];
				hv_vendor[12] = '\0';

				/*
				 * If we found a specific hypervisor, then
				 * we are finished.
				 */
				if (vm_guest != VM_GUEST_VM)
					return;
			}
		}
	}
}