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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct kvm_pmu {int nr_arch_fixed_counters; int /*<<< orphan*/  fixed_ctr_ctrl; } ;
struct kvm_pmc {int dummy; } ;

/* Variables and functions */
 scalar_t__ MSR_CORE_PERF_FIXED_CTR0 ; 
 scalar_t__ fixed_ctrl_field (int /*<<< orphan*/ ,int) ; 
 struct kvm_pmc* get_fixed_pmc (struct kvm_pmu*,scalar_t__) ; 
 int /*<<< orphan*/  reprogram_fixed_counter (struct kvm_pmc*,scalar_t__,int) ; 

__attribute__((used)) static void reprogram_fixed_counters(struct kvm_pmu *pmu, u64 data)
{
	int i;

	for (i = 0; i < pmu->nr_arch_fixed_counters; i++) {
		u8 new_ctrl = fixed_ctrl_field(data, i);
		u8 old_ctrl = fixed_ctrl_field(pmu->fixed_ctr_ctrl, i);
		struct kvm_pmc *pmc;

		pmc = get_fixed_pmc(pmu, MSR_CORE_PERF_FIXED_CTR0 + i);

		if (old_ctrl == new_ctrl)
			continue;

		reprogram_fixed_counter(pmc, new_ctrl, i);
	}

	pmu->fixed_ctr_ctrl = data;
}