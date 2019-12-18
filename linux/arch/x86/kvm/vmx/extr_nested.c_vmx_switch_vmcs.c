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
struct vcpu_vmx {struct loaded_vmcs* loaded_vmcs; } ;
struct loaded_vmcs {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int get_cpu () ; 
 int /*<<< orphan*/  put_cpu () ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_segment_cache_clear (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  vmx_sync_vmcs_host_state (struct vcpu_vmx*,struct loaded_vmcs*) ; 
 int /*<<< orphan*/  vmx_vcpu_load_vmcs (struct kvm_vcpu*,int) ; 

__attribute__((used)) static void vmx_switch_vmcs(struct kvm_vcpu *vcpu, struct loaded_vmcs *vmcs)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	struct loaded_vmcs *prev;
	int cpu;

	if (vmx->loaded_vmcs == vmcs)
		return;

	cpu = get_cpu();
	prev = vmx->loaded_vmcs;
	vmx->loaded_vmcs = vmcs;
	vmx_vcpu_load_vmcs(vcpu, cpu);
	vmx_sync_vmcs_host_state(vmx, prev);
	put_cpu();

	vmx_segment_cache_clear(vmx);
}