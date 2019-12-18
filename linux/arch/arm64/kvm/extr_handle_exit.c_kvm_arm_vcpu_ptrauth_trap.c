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
struct TYPE_2__ {struct kvm_cpu_context* host_cpu_context; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_cpu_context {int /*<<< orphan*/  sys_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  APDA ; 
 int /*<<< orphan*/  APDB ; 
 int /*<<< orphan*/  APGA ; 
 int /*<<< orphan*/  APIA ; 
 int /*<<< orphan*/  APIB ; 
 int /*<<< orphan*/  __ptrauth_save_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_inject_undefined (struct kvm_vcpu*) ; 
 scalar_t__ vcpu_has_ptrauth (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_ptrauth_enable (struct kvm_vcpu*) ; 

void kvm_arm_vcpu_ptrauth_trap(struct kvm_vcpu *vcpu)
{
	struct kvm_cpu_context *ctxt;

	if (vcpu_has_ptrauth(vcpu)) {
		vcpu_ptrauth_enable(vcpu);
		ctxt = vcpu->arch.host_cpu_context;
		__ptrauth_save_key(ctxt->sys_regs, APIA);
		__ptrauth_save_key(ctxt->sys_regs, APIB);
		__ptrauth_save_key(ctxt->sys_regs, APDA);
		__ptrauth_save_key(ctxt->sys_regs, APDB);
		__ptrauth_save_key(ctxt->sys_regs, APGA);
	} else {
		kvm_inject_undefined(vcpu);
	}
}