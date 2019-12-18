#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kvm_vcpu {int dummy; } ;
struct kvm_pmu {TYPE_2__* fixed_counters; TYPE_1__* gp_counters; } ;
struct TYPE_4__ {scalar_t__ idx; struct kvm_vcpu* vcpu; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int idx; struct kvm_vcpu* vcpu; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ INTEL_PMC_IDX_FIXED ; 
 int INTEL_PMC_MAX_FIXED ; 
 int INTEL_PMC_MAX_GENERIC ; 
 int /*<<< orphan*/  KVM_PMC_FIXED ; 
 int /*<<< orphan*/  KVM_PMC_GP ; 
 struct kvm_pmu* vcpu_to_pmu (struct kvm_vcpu*) ; 

__attribute__((used)) static void intel_pmu_init(struct kvm_vcpu *vcpu)
{
	int i;
	struct kvm_pmu *pmu = vcpu_to_pmu(vcpu);

	for (i = 0; i < INTEL_PMC_MAX_GENERIC; i++) {
		pmu->gp_counters[i].type = KVM_PMC_GP;
		pmu->gp_counters[i].vcpu = vcpu;
		pmu->gp_counters[i].idx = i;
	}

	for (i = 0; i < INTEL_PMC_MAX_FIXED; i++) {
		pmu->fixed_counters[i].type = KVM_PMC_FIXED;
		pmu->fixed_counters[i].vcpu = vcpu;
		pmu->fixed_counters[i].idx = i + INTEL_PMC_IDX_FIXED;
	}
}