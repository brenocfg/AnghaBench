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
struct sys_reg_desc {int (* visibility ) (struct kvm_vcpu const*,struct sys_reg_desc const*) ;} ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int REG_HIDDEN_USER ; 
 scalar_t__ likely (int) ; 
 int stub1 (struct kvm_vcpu const*,struct sys_reg_desc const*) ; 

__attribute__((used)) static inline bool sysreg_hidden_from_user(const struct kvm_vcpu *vcpu,
					   const struct sys_reg_desc *r)
{
	if (likely(!r->visibility))
		return false;

	return r->visibility(vcpu, r) & REG_HIDDEN_USER;
}