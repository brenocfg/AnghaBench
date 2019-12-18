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
struct sys_reg_params {int dummy; } ;
struct sys_reg_desc {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_arm_vcpu_ptrauth_trap (struct kvm_vcpu*) ; 

__attribute__((used)) static bool trap_ptrauth(struct kvm_vcpu *vcpu,
			 struct sys_reg_params *p,
			 const struct sys_reg_desc *rd)
{
	kvm_arm_vcpu_ptrauth_trap(vcpu);

	/*
	 * Return false for both cases as we never skip the trapped
	 * instruction:
	 *
	 * - Either we re-execute the same key register access instruction
	 *   after enabling ptrauth.
	 * - Or an UNDEF is injected as ptrauth is not supported/enabled.
	 */
	return false;
}