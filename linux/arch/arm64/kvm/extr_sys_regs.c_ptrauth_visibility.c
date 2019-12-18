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
struct sys_reg_desc {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 unsigned int REG_HIDDEN_GUEST ; 
 unsigned int REG_HIDDEN_USER ; 
 scalar_t__ vcpu_has_ptrauth (struct kvm_vcpu const*) ; 

__attribute__((used)) static unsigned int ptrauth_visibility(const struct kvm_vcpu *vcpu,
			const struct sys_reg_desc *rd)
{
	return vcpu_has_ptrauth(vcpu) ? 0 : REG_HIDDEN_USER | REG_HIDDEN_GUEST;
}