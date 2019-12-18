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
struct vcpu_svm {TYPE_2__* vmcb; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {int int_ctl; } ;
struct TYPE_4__ {TYPE_1__ control; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERCEPT_CR8_WRITE ; 
 int V_TPR_MASK ; 
 int /*<<< orphan*/  is_cr_intercept (struct vcpu_svm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_cr8 (struct kvm_vcpu*,int) ; 
 scalar_t__ svm_nested_virtualize_tpr (struct kvm_vcpu*) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static inline void sync_cr8_to_lapic(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	if (svm_nested_virtualize_tpr(vcpu))
		return;

	if (!is_cr_intercept(svm, INTERCEPT_CR8_WRITE)) {
		int cr8 = svm->vmcb->control.int_ctl & V_TPR_MASK;
		kvm_set_cr8(vcpu, cr8);
	}
}