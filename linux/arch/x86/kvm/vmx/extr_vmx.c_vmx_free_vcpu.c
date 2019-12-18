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
struct TYPE_4__ {struct vcpu_vmx* guest_fpu; struct vcpu_vmx* user_fpu; } ;
struct TYPE_3__ {TYPE_2__ arch; } ;
struct vcpu_vmx {TYPE_1__ vcpu; int /*<<< orphan*/  guest_msrs; int /*<<< orphan*/  loaded_vmcs; int /*<<< orphan*/  vpid; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ enable_pml ; 
 int /*<<< orphan*/  free_loaded_vmcs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_vpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct vcpu_vmx*) ; 
 int /*<<< orphan*/  kvm_vcpu_cache ; 
 int /*<<< orphan*/  kvm_vcpu_uninit (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_vmx_free_vcpu (struct kvm_vcpu*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_destroy_pml_buffer (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  x86_fpu_cache ; 

__attribute__((used)) static void vmx_free_vcpu(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	if (enable_pml)
		vmx_destroy_pml_buffer(vmx);
	free_vpid(vmx->vpid);
	nested_vmx_free_vcpu(vcpu);
	free_loaded_vmcs(vmx->loaded_vmcs);
	kfree(vmx->guest_msrs);
	kvm_vcpu_uninit(vcpu);
	kmem_cache_free(x86_fpu_cache, vmx->vcpu.arch.user_fpu);
	kmem_cache_free(x86_fpu_cache, vmx->vcpu.arch.guest_fpu);
	kmem_cache_free(kvm_vcpu_cache, vmx);
}