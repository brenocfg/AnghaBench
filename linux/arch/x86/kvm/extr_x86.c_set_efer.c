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
typedef  int u64 ;
struct msr_data {int data; int /*<<< orphan*/  host_initiated; } ;
struct TYPE_3__ {int efer; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_efer ) (struct kvm_vcpu*,int) ;} ;

/* Variables and functions */
 int EFER_LMA ; 
 int EFER_LME ; 
 int EFER_NX ; 
 int /*<<< orphan*/  __kvm_valid_efer (struct kvm_vcpu*,int) ; 
 int efer_reserved_bits ; 
 scalar_t__ is_paging (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_reset_context (struct kvm_vcpu*) ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int) ; 

__attribute__((used)) static int set_efer(struct kvm_vcpu *vcpu, struct msr_data *msr_info)
{
	u64 old_efer = vcpu->arch.efer;
	u64 efer = msr_info->data;

	if (efer & efer_reserved_bits)
		return 1;

	if (!msr_info->host_initiated) {
		if (!__kvm_valid_efer(vcpu, efer))
			return 1;

		if (is_paging(vcpu) &&
		    (vcpu->arch.efer & EFER_LME) != (efer & EFER_LME))
			return 1;
	}

	efer &= ~EFER_LMA;
	efer |= vcpu->arch.efer & EFER_LMA;

	kvm_x86_ops->set_efer(vcpu, efer);

	/* Update reserved bits */
	if ((efer ^ old_efer) & EFER_NX)
		kvm_mmu_reset_context(vcpu);

	return 0;
}