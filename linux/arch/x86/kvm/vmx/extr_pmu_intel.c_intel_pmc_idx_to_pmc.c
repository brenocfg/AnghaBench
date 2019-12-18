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
typedef  int u32 ;
struct kvm_pmu {int dummy; } ;
struct kvm_pmc {int dummy; } ;

/* Variables and functions */
 int INTEL_PMC_IDX_FIXED ; 
 int MSR_CORE_PERF_FIXED_CTR0 ; 
 scalar_t__ MSR_P6_EVNTSEL0 ; 
 struct kvm_pmc* get_fixed_pmc (struct kvm_pmu*,int) ; 
 struct kvm_pmc* get_gp_pmc (struct kvm_pmu*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct kvm_pmc *intel_pmc_idx_to_pmc(struct kvm_pmu *pmu, int pmc_idx)
{
	if (pmc_idx < INTEL_PMC_IDX_FIXED)
		return get_gp_pmc(pmu, MSR_P6_EVNTSEL0 + pmc_idx,
				  MSR_P6_EVNTSEL0);
	else {
		u32 idx = pmc_idx - INTEL_PMC_IDX_FIXED;

		return get_fixed_pmc(pmu, idx + MSR_CORE_PERF_FIXED_CTR0);
	}
}