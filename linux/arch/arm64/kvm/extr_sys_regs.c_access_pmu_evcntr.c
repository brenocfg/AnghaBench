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
struct sys_reg_params {int /*<<< orphan*/  regval; scalar_t__ is_write; } ;
struct sys_reg_desc {int CRn; int CRm; int Op2; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int ARMV8_PMU_COUNTER_MASK ; 
 int ARMV8_PMU_CYCLE_IDX ; 
 int /*<<< orphan*/  PMSELR_EL0 ; 
 int __vcpu_sys_reg (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_arm_pmu_v3_ready (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_pmu_get_counter_value (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_pmu_set_counter_value (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pmu_access_cycle_counter_el0_disabled (struct kvm_vcpu*) ; 
 scalar_t__ pmu_access_el0_disabled (struct kvm_vcpu*) ; 
 scalar_t__ pmu_access_event_counter_el0_disabled (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  pmu_counter_idx_valid (struct kvm_vcpu*,int) ; 
 int trap_raz_wi (struct kvm_vcpu*,struct sys_reg_params*,struct sys_reg_desc const*) ; 

__attribute__((used)) static bool access_pmu_evcntr(struct kvm_vcpu *vcpu,
			      struct sys_reg_params *p,
			      const struct sys_reg_desc *r)
{
	u64 idx;

	if (!kvm_arm_pmu_v3_ready(vcpu))
		return trap_raz_wi(vcpu, p, r);

	if (r->CRn == 9 && r->CRm == 13) {
		if (r->Op2 == 2) {
			/* PMXEVCNTR_EL0 */
			if (pmu_access_event_counter_el0_disabled(vcpu))
				return false;

			idx = __vcpu_sys_reg(vcpu, PMSELR_EL0)
			      & ARMV8_PMU_COUNTER_MASK;
		} else if (r->Op2 == 0) {
			/* PMCCNTR_EL0 */
			if (pmu_access_cycle_counter_el0_disabled(vcpu))
				return false;

			idx = ARMV8_PMU_CYCLE_IDX;
		} else {
			return false;
		}
	} else if (r->CRn == 0 && r->CRm == 9) {
		/* PMCCNTR */
		if (pmu_access_event_counter_el0_disabled(vcpu))
			return false;

		idx = ARMV8_PMU_CYCLE_IDX;
	} else if (r->CRn == 14 && (r->CRm & 12) == 8) {
		/* PMEVCNTRn_EL0 */
		if (pmu_access_event_counter_el0_disabled(vcpu))
			return false;

		idx = ((r->CRm & 3) << 3) | (r->Op2 & 7);
	} else {
		return false;
	}

	if (!pmu_counter_idx_valid(vcpu, idx))
		return false;

	if (p->is_write) {
		if (pmu_access_el0_disabled(vcpu))
			return false;

		kvm_pmu_set_counter_value(vcpu, idx, p->regval);
	} else {
		p->regval = kvm_pmu_get_counter_value(vcpu, idx);
	}

	return true;
}