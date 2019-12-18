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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;
struct kvm_pmu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMU_TYPE_COUNTER ; 
 int /*<<< orphan*/  PMU_TYPE_EVNTSEL ; 
 scalar_t__ get_gp_pmc_amd (struct kvm_pmu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kvm_pmu* vcpu_to_pmu (struct kvm_vcpu*) ; 

__attribute__((used)) static bool amd_is_valid_msr(struct kvm_vcpu *vcpu, u32 msr)
{
	struct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	int ret = false;

	ret = get_gp_pmc_amd(pmu, msr, PMU_TYPE_COUNTER) ||
		get_gp_pmc_amd(pmu, msr, PMU_TYPE_EVNTSEL);

	return ret;
}