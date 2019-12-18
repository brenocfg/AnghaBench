#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned long long intercept; int exit_required; } ;
struct vcpu_svm {TYPE_3__ nested; TYPE_2__* vmcb; int /*<<< orphan*/  vcpu; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  exit_code; } ;
struct TYPE_5__ {TYPE_1__ control; } ;

/* Variables and functions */
 unsigned long long INTERCEPT_SMI ; 
 int /*<<< orphan*/  SVM_EXIT_SMI ; 
 int /*<<< orphan*/  gif_set (struct vcpu_svm*) ; 
 scalar_t__ is_guest_mode (int /*<<< orphan*/ *) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static int svm_smi_allowed(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	/* Per APM Vol.2 15.22.2 "Response to SMI" */
	if (!gif_set(svm))
		return 0;

	if (is_guest_mode(&svm->vcpu) &&
	    svm->nested.intercept & (1ULL << INTERCEPT_SMI)) {
		/* TODO: Might need to set exit_info_1 and exit_info_2 here */
		svm->vmcb->control.exit_code = SVM_EXIT_SMI;
		svm->nested.exit_required = true;
		return 0;
	}

	return 1;
}