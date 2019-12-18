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
typedef  int /*<<< orphan*/  uint64_t ;
struct vmx {int /*<<< orphan*/  vm; TYPE_1__* cap; } ;
struct TYPE_2__ {int proc_ctls; } ;

/* Variables and functions */
 int PROCBASED_TSC_OFFSET ; 
 int /*<<< orphan*/  VCPU_CTR0 (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  VMCS_PRI_PROC_BASED_CTLS ; 
 int /*<<< orphan*/  VMCS_TSC_OFFSET ; 
 int /*<<< orphan*/  vmcs_write (int /*<<< orphan*/ ,int) ; 
 int vmwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
vmx_set_tsc_offset(struct vmx *vmx, int vcpu, uint64_t offset)
{
	int error;

	if ((vmx->cap[vcpu].proc_ctls & PROCBASED_TSC_OFFSET) == 0) {
		vmx->cap[vcpu].proc_ctls |= PROCBASED_TSC_OFFSET;
		vmcs_write(VMCS_PRI_PROC_BASED_CTLS, vmx->cap[vcpu].proc_ctls);
		VCPU_CTR0(vmx->vm, vcpu, "Enabling TSC offsetting");
	}

	error = vmwrite(VMCS_TSC_OFFSET, offset);

	return (error);
}