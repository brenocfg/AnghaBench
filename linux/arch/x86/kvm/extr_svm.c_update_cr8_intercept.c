#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vcpu_svm {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERCEPT_CR8_WRITE ; 
 int /*<<< orphan*/  clr_cr_intercept (struct vcpu_svm*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_vcpu_apicv_active (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  set_cr_intercept (struct vcpu_svm*,int /*<<< orphan*/ ) ; 
 scalar_t__ svm_nested_virtualize_tpr (struct kvm_vcpu*) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void update_cr8_intercept(struct kvm_vcpu *vcpu, int tpr, int irr)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	if (svm_nested_virtualize_tpr(vcpu) ||
	    kvm_vcpu_apicv_active(vcpu))
		return;

	clr_cr_intercept(svm, INTERCEPT_CR8_WRITE);

	if (irr == -1)
		return;

	if (tpr >= irr)
		set_cr_intercept(svm, INTERCEPT_CR8_WRITE);
}