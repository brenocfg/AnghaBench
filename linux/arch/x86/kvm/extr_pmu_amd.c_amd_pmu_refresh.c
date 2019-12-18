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
struct kvm_pmu {int* counter_bitmask; int reserved_bits; int version; scalar_t__ global_status; scalar_t__ nr_arch_fixed_counters; int /*<<< orphan*/  nr_arch_gp_counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD64_NUM_COUNTERS ; 
 int /*<<< orphan*/  AMD64_NUM_COUNTERS_CORE ; 
 size_t KVM_PMC_FIXED ; 
 size_t KVM_PMC_GP ; 
 int /*<<< orphan*/  X86_FEATURE_PERFCTR_CORE ; 
 scalar_t__ guest_cpuid_has (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 struct kvm_pmu* vcpu_to_pmu (struct kvm_vcpu*) ; 

__attribute__((used)) static void amd_pmu_refresh(struct kvm_vcpu *vcpu)
{
	struct kvm_pmu *pmu = vcpu_to_pmu(vcpu);

	if (guest_cpuid_has(vcpu, X86_FEATURE_PERFCTR_CORE))
		pmu->nr_arch_gp_counters = AMD64_NUM_COUNTERS_CORE;
	else
		pmu->nr_arch_gp_counters = AMD64_NUM_COUNTERS;

	pmu->counter_bitmask[KVM_PMC_GP] = ((u64)1 << 48) - 1;
	pmu->reserved_bits = 0xffffffff00200000ull;
	pmu->version = 1;
	/* not applicable to AMD; but clean them to prevent any fall out */
	pmu->counter_bitmask[KVM_PMC_FIXED] = 0;
	pmu->nr_arch_fixed_counters = 0;
	pmu->global_status = 0;
}