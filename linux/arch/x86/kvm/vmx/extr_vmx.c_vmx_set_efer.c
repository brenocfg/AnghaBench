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
typedef  int u64 ;
struct vcpu_vmx {int dummy; } ;
struct shared_msr_entry {int data; } ;
struct TYPE_2__ {int efer; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int EFER_LMA ; 
 int EFER_LME ; 
 int /*<<< orphan*/  MSR_EFER ; 
 int /*<<< orphan*/  VM_ENTRY_IA32E_MODE ; 
 struct shared_msr_entry* find_msr_entry (struct vcpu_vmx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_msrs (struct vcpu_vmx*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vm_entry_controls_clearbit (struct vcpu_vmx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_entry_controls_setbit (struct vcpu_vmx*,int /*<<< orphan*/ ) ; 

void vmx_set_efer(struct kvm_vcpu *vcpu, u64 efer)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	struct shared_msr_entry *msr = find_msr_entry(vmx, MSR_EFER);

	if (!msr)
		return;

	vcpu->arch.efer = efer;
	if (efer & EFER_LMA) {
		vm_entry_controls_setbit(to_vmx(vcpu), VM_ENTRY_IA32E_MODE);
		msr->data = efer;
	} else {
		vm_entry_controls_clearbit(to_vmx(vcpu), VM_ENTRY_IA32E_MODE);

		msr->data = efer & ~EFER_LME;
	}
	setup_msrs(vmx);
}