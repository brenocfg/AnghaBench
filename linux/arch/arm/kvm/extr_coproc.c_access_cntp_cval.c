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
typedef  int u64 ;
struct kvm_vcpu {int dummy; } ;
struct coproc_reg {int dummy; } ;
struct coproc_params {int /*<<< orphan*/  Rt2; int /*<<< orphan*/  Rt1; scalar_t__ is_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_PTIMER ; 
 int /*<<< orphan*/  TIMER_REG_CVAL ; 
 int kvm_arm_timer_read_sysreg (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_arm_timer_write_sysreg (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int* vcpu_reg (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool access_cntp_cval(struct kvm_vcpu *vcpu,
			     const struct coproc_params *p,
			     const struct coproc_reg *r)
{
	u64 val;

	if (p->is_write) {
		val = (u64)*vcpu_reg(vcpu, p->Rt2) << 32;
		val |= *vcpu_reg(vcpu, p->Rt1);
		kvm_arm_timer_write_sysreg(vcpu,
					   TIMER_PTIMER, TIMER_REG_CVAL, val);
	} else {
		val = kvm_arm_timer_read_sysreg(vcpu,
						TIMER_PTIMER, TIMER_REG_CVAL);
		*vcpu_reg(vcpu, p->Rt1) = val;
		*vcpu_reg(vcpu, p->Rt2) = val >> 32;
	}

	return true;
}