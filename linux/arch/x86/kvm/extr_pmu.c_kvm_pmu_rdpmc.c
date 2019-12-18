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
typedef  int u64 ;
struct kvm_vcpu {int dummy; } ;
struct kvm_pmu {int /*<<< orphan*/  version; } ;
struct kvm_pmc {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pmu_ops; } ;
struct TYPE_3__ {struct kvm_pmc* (* msr_idx_to_pmc ) (struct kvm_vcpu*,unsigned int,int*) ;} ;

/* Variables and functions */
 scalar_t__ is_vmware_backdoor_pmc (unsigned int) ; 
 int kvm_pmu_rdpmc_vmware (struct kvm_vcpu*,unsigned int,int*) ; 
 TYPE_2__* kvm_x86_ops ; 
 int pmc_read_counter (struct kvm_pmc*) ; 
 struct kvm_pmc* stub1 (struct kvm_vcpu*,unsigned int,int*) ; 
 struct kvm_pmu* vcpu_to_pmu (struct kvm_vcpu*) ; 

int kvm_pmu_rdpmc(struct kvm_vcpu *vcpu, unsigned idx, u64 *data)
{
	bool fast_mode = idx & (1u << 31);
	struct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	struct kvm_pmc *pmc;
	u64 mask = fast_mode ? ~0u : ~0ull;

	if (!pmu->version)
		return 1;

	if (is_vmware_backdoor_pmc(idx))
		return kvm_pmu_rdpmc_vmware(vcpu, idx, data);

	pmc = kvm_x86_ops->pmu_ops->msr_idx_to_pmc(vcpu, idx, &mask);
	if (!pmc)
		return 1;

	*data = pmc_read_counter(pmc) & mask;
	return 0;
}