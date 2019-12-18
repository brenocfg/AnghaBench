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
typedef  int /*<<< orphan*/  u32 ;
struct msr_data {int data; int /*<<< orphan*/  index; } ;
struct kvm_vcpu {int dummy; } ;
struct kvm_pmu {int reserved_bits; } ;
struct kvm_pmc {int eventsel; int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMU_TYPE_COUNTER ; 
 int /*<<< orphan*/  PMU_TYPE_EVNTSEL ; 
 struct kvm_pmc* get_gp_pmc_amd (struct kvm_pmu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pmc_read_counter (struct kvm_pmc*) ; 
 int /*<<< orphan*/  reprogram_gp_counter (struct kvm_pmc*,int) ; 
 struct kvm_pmu* vcpu_to_pmu (struct kvm_vcpu*) ; 

__attribute__((used)) static int amd_pmu_set_msr(struct kvm_vcpu *vcpu, struct msr_data *msr_info)
{
	struct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	struct kvm_pmc *pmc;
	u32 msr = msr_info->index;
	u64 data = msr_info->data;

	/* MSR_PERFCTRn */
	pmc = get_gp_pmc_amd(pmu, msr, PMU_TYPE_COUNTER);
	if (pmc) {
		pmc->counter += data - pmc_read_counter(pmc);
		return 0;
	}
	/* MSR_EVNTSELn */
	pmc = get_gp_pmc_amd(pmu, msr, PMU_TYPE_EVNTSEL);
	if (pmc) {
		if (data == pmc->eventsel)
			return 0;
		if (!(data & pmu->reserved_bits)) {
			reprogram_gp_counter(pmc, data);
			return 0;
		}
	}

	return 1;
}