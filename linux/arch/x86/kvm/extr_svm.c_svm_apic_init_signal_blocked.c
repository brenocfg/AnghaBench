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
struct TYPE_3__ {unsigned long long intercept; } ;
struct TYPE_4__ {TYPE_1__ control; } ;

/* Variables and functions */
 unsigned long long INTERCEPT_INIT ; 
 int /*<<< orphan*/  gif_set (struct vcpu_svm*) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static bool svm_apic_init_signal_blocked(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	/*
	 * TODO: Last condition latch INIT signals on vCPU when
	 * vCPU is in guest-mode and vmcb12 defines intercept on INIT.
	 * To properly emulate the INIT intercept, SVM should implement
	 * kvm_x86_ops->check_nested_events() and call nested_svm_vmexit()
	 * there if an INIT signal is pending.
	 */
	return !gif_set(svm) ||
		   (svm->vmcb->control.intercept & (1ULL << INTERCEPT_INIT));
}