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
struct x86_exception {int nested_page_fault; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* inject_page_fault ) (struct kvm_vcpu*,struct x86_exception*) ;} ;
struct TYPE_6__ {TYPE_2__* mmu; TYPE_1__ nested_mmu; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* inject_page_fault ) (struct kvm_vcpu*,struct x86_exception*) ;} ;

/* Variables and functions */
 scalar_t__ mmu_is_nested (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,struct x86_exception*) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*,struct x86_exception*) ; 

__attribute__((used)) static bool kvm_propagate_fault(struct kvm_vcpu *vcpu, struct x86_exception *fault)
{
	if (mmu_is_nested(vcpu) && !fault->nested_page_fault)
		vcpu->arch.nested_mmu.inject_page_fault(vcpu, fault);
	else
		vcpu->arch.mmu->inject_page_fault(vcpu, fault);

	return fault->nested_page_fault;
}