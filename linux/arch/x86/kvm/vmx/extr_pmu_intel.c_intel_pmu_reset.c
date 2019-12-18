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
struct kvm_vcpu {int dummy; } ;
struct kvm_pmu {scalar_t__ global_ovf_ctrl; scalar_t__ global_status; scalar_t__ global_ctrl; scalar_t__ fixed_ctr_ctrl; struct kvm_pmc* fixed_counters; struct kvm_pmc* gp_counters; } ;
struct kvm_pmc {scalar_t__ counter; scalar_t__ eventsel; } ;

/* Variables and functions */
 int INTEL_PMC_MAX_FIXED ; 
 int INTEL_PMC_MAX_GENERIC ; 
 int /*<<< orphan*/  pmc_stop_counter (struct kvm_pmc*) ; 
 struct kvm_pmu* vcpu_to_pmu (struct kvm_vcpu*) ; 

__attribute__((used)) static void intel_pmu_reset(struct kvm_vcpu *vcpu)
{
	struct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	struct kvm_pmc *pmc = NULL;
	int i;

	for (i = 0; i < INTEL_PMC_MAX_GENERIC; i++) {
		pmc = &pmu->gp_counters[i];

		pmc_stop_counter(pmc);
		pmc->counter = pmc->eventsel = 0;
	}

	for (i = 0; i < INTEL_PMC_MAX_FIXED; i++) {
		pmc = &pmu->fixed_counters[i];

		pmc_stop_counter(pmc);
		pmc->counter = 0;
	}

	pmu->fixed_ctr_ctrl = pmu->global_ctrl = pmu->global_status =
		pmu->global_ovf_ctrl = 0;
}