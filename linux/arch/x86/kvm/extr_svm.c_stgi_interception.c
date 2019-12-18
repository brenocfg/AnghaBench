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
struct vcpu_svm {int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERCEPT_STGI ; 
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int /*<<< orphan*/  clr_intercept (struct vcpu_svm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_gif (struct vcpu_svm*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kvm_skip_emulated_instruction (int /*<<< orphan*/ *) ; 
 scalar_t__ nested_svm_check_permissions (struct vcpu_svm*) ; 
 scalar_t__ vgif_enabled (struct vcpu_svm*) ; 

__attribute__((used)) static int stgi_interception(struct vcpu_svm *svm)
{
	int ret;

	if (nested_svm_check_permissions(svm))
		return 1;

	/*
	 * If VGIF is enabled, the STGI intercept is only added to
	 * detect the opening of the SMI/NMI window; remove it now.
	 */
	if (vgif_enabled(svm))
		clr_intercept(svm, INTERCEPT_STGI);

	ret = kvm_skip_emulated_instruction(&svm->vcpu);
	kvm_make_request(KVM_REQ_EVENT, &svm->vcpu);

	enable_gif(svm);

	return ret;
}