#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union kvm_mmu_page_role {int dummy; } kvm_mmu_page_role ;
struct TYPE_2__ {int /*<<< orphan*/  mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_MMU_ROOT_CURRENT ; 
 int /*<<< orphan*/  fast_cr3_switch (struct kvm_vcpu*,int /*<<< orphan*/ ,union kvm_mmu_page_role,int) ; 
 int /*<<< orphan*/  kvm_mmu_free_roots (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __kvm_mmu_new_cr3(struct kvm_vcpu *vcpu, gpa_t new_cr3,
			      union kvm_mmu_page_role new_role,
			      bool skip_tlb_flush)
{
	if (!fast_cr3_switch(vcpu, new_cr3, new_role, skip_tlb_flush))
		kvm_mmu_free_roots(vcpu, vcpu->arch.mmu,
				   KVM_MMU_ROOT_CURRENT);
}