#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  nip; } ;
struct TYPE_6__ {TYPE_2__ regs; TYPE_1__* shared; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_4__ {int msr; } ;

/* Variables and functions */
 int MSR_IS ; 
 int /*<<< orphan*/  kvmppc_e500_deliver_tlb_miss (struct kvm_vcpu*,int /*<<< orphan*/ ,unsigned int) ; 

void kvmppc_mmu_itlb_miss(struct kvm_vcpu *vcpu)
{
	unsigned int as = !!(vcpu->arch.shared->msr & MSR_IS);

	kvmppc_e500_deliver_tlb_miss(vcpu, vcpu->arch.regs.nip, as);
}