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

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_TLB_FLUSH ; 
 scalar_t__ kvm_check_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_mmu_pte_flush (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvmppc_core_check_requests_pr(struct kvm_vcpu *vcpu)
{
	int r = 1; /* Indicate we want to get back into the guest */

	/* We misuse TLB_FLUSH to indicate that we want to clear
	   all shadow cache entries */
	if (kvm_check_request(KVM_REQ_TLB_FLUSH, vcpu))
		kvmppc_mmu_pte_flush(vcpu, 0, 0);

	return r;
}