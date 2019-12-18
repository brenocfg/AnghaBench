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
struct TYPE_4__ {unsigned long long current_vmptr; int posted_intr_nv; int /*<<< orphan*/  cached_vmcs12; } ;
struct vcpu_vmx {TYPE_2__ nested; } ;
struct TYPE_3__ {int /*<<< orphan*/  guest_mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_MMU_ROOTS_ALL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  VMCS12_SIZE ; 
 int /*<<< orphan*/  copy_shadow_to_vmcs12 (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  copy_vmcs02_to_vmcs12_rare (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ enable_shadow_vmcs ; 
 int /*<<< orphan*/  get_vmcs12 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_free_roots (struct kvm_vcpu*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_write_guest_page (struct kvm_vcpu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_disable_shadow_vmcs (struct vcpu_vmx*) ; 

__attribute__((used)) static inline void nested_release_vmcs12(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	if (vmx->nested.current_vmptr == -1ull)
		return;

	copy_vmcs02_to_vmcs12_rare(vcpu, get_vmcs12(vcpu));

	if (enable_shadow_vmcs) {
		/* copy to memory all shadowed fields in case
		   they were modified */
		copy_shadow_to_vmcs12(vmx);
		vmx_disable_shadow_vmcs(vmx);
	}
	vmx->nested.posted_intr_nv = -1;

	/* Flush VMCS12 to guest memory */
	kvm_vcpu_write_guest_page(vcpu,
				  vmx->nested.current_vmptr >> PAGE_SHIFT,
				  vmx->nested.cached_vmcs12, 0, VMCS12_SIZE);

	kvm_mmu_free_roots(vcpu, &vcpu->arch.guest_mmu, KVM_MMU_ROOTS_ALL);

	vmx->nested.current_vmptr = -1ull;
}