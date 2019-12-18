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
 int /*<<< orphan*/  INTERCEPT_STGI ; 
 int /*<<< orphan*/  gif_set (struct vcpu_svm*) ; 
 int /*<<< orphan*/  set_intercept (struct vcpu_svm*,int /*<<< orphan*/ ) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 
 scalar_t__ vgif_enabled (struct vcpu_svm*) ; 

__attribute__((used)) static int enable_smi_window(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	if (!gif_set(svm)) {
		if (vgif_enabled(svm))
			set_intercept(svm, INTERCEPT_STGI);
		/* STGI will cause a vm exit */
		return 1;
	}
	return 0;
}