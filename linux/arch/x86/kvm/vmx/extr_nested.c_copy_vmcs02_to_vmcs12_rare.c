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
struct vmcs12 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vmcs02; int /*<<< orphan*/  need_sync_vmcs02_to_vmcs12_rare; } ;
struct vcpu_vmx {int /*<<< orphan*/  vcpu; int /*<<< orphan*/  vmcs01; int /*<<< orphan*/ * loaded_vmcs; TYPE_1__ nested; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int get_cpu () ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  sync_vmcs02_to_vmcs12_rare (struct kvm_vcpu*,struct vmcs12*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_vcpu_load (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void copy_vmcs02_to_vmcs12_rare(struct kvm_vcpu *vcpu,
				       struct vmcs12 *vmcs12)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	int cpu;

	if (!vmx->nested.need_sync_vmcs02_to_vmcs12_rare)
		return;


	WARN_ON_ONCE(vmx->loaded_vmcs != &vmx->vmcs01);

	cpu = get_cpu();
	vmx->loaded_vmcs = &vmx->nested.vmcs02;
	vmx_vcpu_load(&vmx->vcpu, cpu);

	sync_vmcs02_to_vmcs12_rare(vcpu, vmcs12);

	vmx->loaded_vmcs = &vmx->vmcs01;
	vmx_vcpu_load(&vmx->vcpu, cpu);
	put_cpu();
}