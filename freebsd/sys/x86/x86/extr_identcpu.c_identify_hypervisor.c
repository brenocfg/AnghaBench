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
typedef  scalar_t__ u_int ;
struct TYPE_4__ {scalar_t__ vm_guest; int /*<<< orphan*/  vm_pname; int /*<<< orphan*/  vm_bname; } ;

/* Variables and functions */
 int CPUID2_HV ; 
 int /*<<< orphan*/  VMW_HVCMD_GETVERSION ; 
 scalar_t__ VMW_HVMAGIC ; 
 scalar_t__ VM_GUEST_VM ; 
 scalar_t__ VM_GUEST_VMWARE ; 
 int cpu_feature2 ; 
 int /*<<< orphan*/  freeenv (char*) ; 
 char* hv_vendor ; 
 int /*<<< orphan*/  identify_hypervisor_cpuid_base () ; 
 char* kern_getenv (char*) ; 
 int nitems (TYPE_1__*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 TYPE_1__* vm_bnames ; 
 scalar_t__ vm_guest ; 
 TYPE_1__* vm_pnames ; 
 int /*<<< orphan*/  vmware_hvcall (int /*<<< orphan*/ ,scalar_t__*) ; 

void
identify_hypervisor(void)
{
	u_int regs[4];
	char *p;
	int i;

	/*
	 * If CPUID2_HV is set, we are running in a hypervisor environment.
	 */
	if (cpu_feature2 & CPUID2_HV) {
		vm_guest = VM_GUEST_VM;
		identify_hypervisor_cpuid_base();

		/* If we have a definitive vendor, we can return now. */
		if (*hv_vendor != '\0')
			return;
	}

	/*
	 * Examine SMBIOS strings for older hypervisors.
	 */
	p = kern_getenv("smbios.system.serial");
	if (p != NULL) {
		if (strncmp(p, "VMware-", 7) == 0 || strncmp(p, "VMW", 3) == 0) {
			vmware_hvcall(VMW_HVCMD_GETVERSION, regs);
			if (regs[1] == VMW_HVMAGIC) {
				vm_guest = VM_GUEST_VMWARE;			
				freeenv(p);
				return;
			}
		}
		freeenv(p);
	}

	/*
	 * XXX: Some of these entries may not be needed since they were
	 * added to FreeBSD before the checks above.
	 */
	p = kern_getenv("smbios.bios.vendor");
	if (p != NULL) {
		for (i = 0; i < nitems(vm_bnames); i++)
			if (strcmp(p, vm_bnames[i].vm_bname) == 0) {
				vm_guest = vm_bnames[i].vm_guest;
				/* If we have a specific match, return */
				if (vm_guest != VM_GUEST_VM) {
					freeenv(p);
					return;
				}
				/*
				 * We are done with bnames, but there might be
				 * a more specific match in the pnames
				 */
				break;
			}
		freeenv(p);
	}
	p = kern_getenv("smbios.system.product");
	if (p != NULL) {
		for (i = 0; i < nitems(vm_pnames); i++)
			if (strcmp(p, vm_pnames[i].vm_pname) == 0) {
				vm_guest = vm_pnames[i].vm_guest;
				freeenv(p);
				return;
			}
		freeenv(p);
	}
}