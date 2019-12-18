#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int vmxon; } ;
struct TYPE_8__ {int vmxon; int posted_intr_nv; unsigned long long current_vmptr; int /*<<< orphan*/  vmcs02; int /*<<< orphan*/ * pi_desc; int /*<<< orphan*/  pi_desc_map; int /*<<< orphan*/  virtual_apic_map; int /*<<< orphan*/ * apic_access_page; int /*<<< orphan*/ * cached_shadow_vmcs12; int /*<<< orphan*/ * cached_vmcs12; int /*<<< orphan*/  vpid02; TYPE_1__ smm; } ;
struct TYPE_6__ {int /*<<< orphan*/ * shadow_vmcs; } ;
struct vcpu_vmx {TYPE_4__ nested; TYPE_2__ vmcs01; } ;
struct TYPE_7__ {int /*<<< orphan*/  guest_mmu; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_MMU_ROOTS_ALL ; 
 int /*<<< orphan*/  KVM_REQ_GET_VMCS12_PAGES ; 
 scalar_t__ enable_shadow_vmcs ; 
 int /*<<< orphan*/  free_loaded_vmcs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_vmcs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_vpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_clear_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_free_roots (struct kvm_vcpu*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_release_page_dirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_vcpu_unmap (struct kvm_vcpu*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nested_release_evmcs (struct kvm_vcpu*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmx_disable_shadow_vmcs (struct vcpu_vmx*) ; 

__attribute__((used)) static void free_nested(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	if (!vmx->nested.vmxon && !vmx->nested.smm.vmxon)
		return;

	kvm_clear_request(KVM_REQ_GET_VMCS12_PAGES, vcpu);

	vmx->nested.vmxon = false;
	vmx->nested.smm.vmxon = false;
	free_vpid(vmx->nested.vpid02);
	vmx->nested.posted_intr_nv = -1;
	vmx->nested.current_vmptr = -1ull;
	if (enable_shadow_vmcs) {
		vmx_disable_shadow_vmcs(vmx);
		vmcs_clear(vmx->vmcs01.shadow_vmcs);
		free_vmcs(vmx->vmcs01.shadow_vmcs);
		vmx->vmcs01.shadow_vmcs = NULL;
	}
	kfree(vmx->nested.cached_vmcs12);
	vmx->nested.cached_vmcs12 = NULL;
	kfree(vmx->nested.cached_shadow_vmcs12);
	vmx->nested.cached_shadow_vmcs12 = NULL;
	/* Unpin physical memory we referred to in the vmcs02 */
	if (vmx->nested.apic_access_page) {
		kvm_release_page_dirty(vmx->nested.apic_access_page);
		vmx->nested.apic_access_page = NULL;
	}
	kvm_vcpu_unmap(vcpu, &vmx->nested.virtual_apic_map, true);
	kvm_vcpu_unmap(vcpu, &vmx->nested.pi_desc_map, true);
	vmx->nested.pi_desc = NULL;

	kvm_mmu_free_roots(vcpu, &vcpu->arch.guest_mmu, KVM_MMU_ROOTS_ALL);

	nested_release_evmcs(vcpu);

	free_loaded_vmcs(&vmx->nested.vmcs02);
}