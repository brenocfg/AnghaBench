#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  get_pdptr; int /*<<< orphan*/  inject_page_fault; int /*<<< orphan*/  (* get_cr3 ) (struct kvm_vcpu*) ;int /*<<< orphan*/  set_cr3; } ;
struct TYPE_9__ {int /*<<< orphan*/  nested_mmu; int /*<<< orphan*/ * walk_mmu; TYPE_3__* mmu; TYPE_3__ guest_mmu; } ;
struct kvm_vcpu {TYPE_4__ arch; } ;
struct TYPE_6__ {int ept_caps; } ;
struct TYPE_7__ {TYPE_1__ msrs; } ;
struct TYPE_10__ {TYPE_2__ nested; } ;

/* Variables and functions */
 int VMX_EPT_EXECUTE_ONLY_BIT ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_init_shadow_ept_mmu (struct kvm_vcpu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_pdptr_read ; 
 int /*<<< orphan*/  mmu_is_nested (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_ept_ad_enabled (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_ept_get_cr3 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_ept_inject_page_fault ; 
 TYPE_5__* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_set_cr3 ; 

__attribute__((used)) static void nested_ept_init_mmu_context(struct kvm_vcpu *vcpu)
{
	WARN_ON(mmu_is_nested(vcpu));

	vcpu->arch.mmu = &vcpu->arch.guest_mmu;
	kvm_init_shadow_ept_mmu(vcpu,
			to_vmx(vcpu)->nested.msrs.ept_caps &
			VMX_EPT_EXECUTE_ONLY_BIT,
			nested_ept_ad_enabled(vcpu),
			nested_ept_get_cr3(vcpu));
	vcpu->arch.mmu->set_cr3           = vmx_set_cr3;
	vcpu->arch.mmu->get_cr3           = nested_ept_get_cr3;
	vcpu->arch.mmu->inject_page_fault = nested_ept_inject_page_fault;
	vcpu->arch.mmu->get_pdptr         = kvm_pdptr_read;

	vcpu->arch.walk_mmu              = &vcpu->arch.nested_mmu;
}