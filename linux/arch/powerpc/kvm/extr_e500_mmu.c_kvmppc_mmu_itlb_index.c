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
struct TYPE_4__ {TYPE_1__* shared; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  gva_t ;
struct TYPE_3__ {int msr; } ;

/* Variables and functions */
 int MSR_IS ; 
 int /*<<< orphan*/  get_cur_pid (struct kvm_vcpu*) ; 
 int kvmppc_e500_tlb_search (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int kvmppc_mmu_itlb_index(struct kvm_vcpu *vcpu, gva_t eaddr)
{
	unsigned int as = !!(vcpu->arch.shared->msr & MSR_IS);

	return kvmppc_e500_tlb_search(vcpu, eaddr, get_cur_pid(vcpu), as);
}