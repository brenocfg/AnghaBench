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
struct TYPE_2__ {int /*<<< orphan*/  int_ctl; } ;
struct vmcb {TYPE_1__ control; } ;
struct vcpu_svm {struct vmcb* vmcb; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVIC_ENABLE_MASK ; 
 int /*<<< orphan*/  VMCB_AVIC ; 
 scalar_t__ kvm_vcpu_apicv_active (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  mark_dirty (struct vmcb*,int /*<<< orphan*/ ) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void svm_refresh_apicv_exec_ctrl(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);
	struct vmcb *vmcb = svm->vmcb;

	if (kvm_vcpu_apicv_active(vcpu))
		vmcb->control.int_ctl |= AVIC_ENABLE_MASK;
	else
		vmcb->control.int_ctl &= ~AVIC_ENABLE_MASK;
	mark_dirty(vmcb, VMCB_AVIC);
}