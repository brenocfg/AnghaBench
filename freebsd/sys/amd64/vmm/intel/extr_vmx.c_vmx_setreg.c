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
typedef  int uint64_t ;
struct vmx {TYPE_1__* ctx; int /*<<< orphan*/ * vmcs; int /*<<< orphan*/  vm; } ;
typedef  int /*<<< orphan*/  pmap_t ;
struct TYPE_2__ {int /*<<< orphan*/  pmap; } ;

/* Variables and functions */
 int EFER_LMA ; 
 int VMCS_ENTRY_CTLS ; 
 int VMCS_IDENT (int) ; 
 int VM_ENTRY_GUEST_LMA ; 
 int VM_ENTRY_LOAD_EFER ; 
 int VM_REG_GUEST_CR3 ; 
 int VM_REG_GUEST_EFER ; 
 int VM_REG_GUEST_INTR_SHADOW ; 
 int curcpu ; 
 int entry_ctls ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int) ; 
 int vcpu_is_running (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  vm_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_getreg (int /*<<< orphan*/ *,int,int,int*) ; 
 int vmcs_setreg (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  vmx_invvpid (struct vmx*,int,int /*<<< orphan*/ ,int) ; 
 int vmx_modify_intr_shadow (struct vmx*,int,int,int) ; 
 int vmx_shadow_reg (int) ; 
 scalar_t__ vmxctx_setreg (TYPE_1__*,int,int) ; 

__attribute__((used)) static int
vmx_setreg(void *arg, int vcpu, int reg, uint64_t val)
{
	int error, hostcpu, running, shadow;
	uint64_t ctls;
	pmap_t pmap;
	struct vmx *vmx = arg;

	running = vcpu_is_running(vmx->vm, vcpu, &hostcpu);
	if (running && hostcpu != curcpu)
		panic("vmx_setreg: %s%d is running", vm_name(vmx->vm), vcpu);

	if (reg == VM_REG_GUEST_INTR_SHADOW)
		return (vmx_modify_intr_shadow(vmx, vcpu, running, val));

	if (vmxctx_setreg(&vmx->ctx[vcpu], reg, val) == 0)
		return (0);

	error = vmcs_setreg(&vmx->vmcs[vcpu], running, reg, val);

	if (error == 0) {
		/*
		 * If the "load EFER" VM-entry control is 1 then the
		 * value of EFER.LMA must be identical to "IA-32e mode guest"
		 * bit in the VM-entry control.
		 */
		if ((entry_ctls & VM_ENTRY_LOAD_EFER) != 0 &&
		    (reg == VM_REG_GUEST_EFER)) {
			vmcs_getreg(&vmx->vmcs[vcpu], running,
				    VMCS_IDENT(VMCS_ENTRY_CTLS), &ctls);
			if (val & EFER_LMA)
				ctls |= VM_ENTRY_GUEST_LMA;
			else
				ctls &= ~VM_ENTRY_GUEST_LMA;
			vmcs_setreg(&vmx->vmcs[vcpu], running,
				    VMCS_IDENT(VMCS_ENTRY_CTLS), ctls);
		}

		shadow = vmx_shadow_reg(reg);
		if (shadow > 0) {
			/*
			 * Store the unmodified value in the shadow
			 */
			error = vmcs_setreg(&vmx->vmcs[vcpu], running,
				    VMCS_IDENT(shadow), val);
		}

		if (reg == VM_REG_GUEST_CR3) {
			/*
			 * Invalidate the guest vcpu's TLB mappings to emulate
			 * the behavior of updating %cr3.
			 *
			 * XXX the processor retains global mappings when %cr3
			 * is updated but vmx_invvpid() does not.
			 */
			pmap = vmx->ctx[vcpu].pmap;
			vmx_invvpid(vmx, vcpu, pmap, running);
		}
	}

	return (error);
}