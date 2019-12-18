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
struct TYPE_2__ {scalar_t__ revision_id; scalar_t__ shadow_vmcs; } ;
struct vmcs12 {unsigned long long vmcs_link_pointer; TYPE_1__ hdr; } ;
struct kvm_vcpu {int dummy; } ;
struct kvm_host_map {struct vmcs12* hva; } ;

/* Variables and functions */
 scalar_t__ CC (int) ; 
 int EINVAL ; 
 scalar_t__ VMCS12_REVISION ; 
 int /*<<< orphan*/  gpa_to_gfn (unsigned long long) ; 
 int kvm_vcpu_map (struct kvm_vcpu*,int /*<<< orphan*/ ,struct kvm_host_map*) ; 
 int /*<<< orphan*/  kvm_vcpu_unmap (struct kvm_vcpu*,struct kvm_host_map*,int) ; 
 scalar_t__ nested_cpu_has_shadow_vmcs (struct vmcs12*) ; 
 int /*<<< orphan*/  page_address_valid (struct kvm_vcpu*,unsigned long long) ; 

__attribute__((used)) static int nested_vmx_check_vmcs_link_ptr(struct kvm_vcpu *vcpu,
					  struct vmcs12 *vmcs12)
{
	int r = 0;
	struct vmcs12 *shadow;
	struct kvm_host_map map;

	if (vmcs12->vmcs_link_pointer == -1ull)
		return 0;

	if (CC(!page_address_valid(vcpu, vmcs12->vmcs_link_pointer)))
		return -EINVAL;

	if (CC(kvm_vcpu_map(vcpu, gpa_to_gfn(vmcs12->vmcs_link_pointer), &map)))
		return -EINVAL;

	shadow = map.hva;

	if (CC(shadow->hdr.revision_id != VMCS12_REVISION) ||
	    CC(shadow->hdr.shadow_vmcs != nested_cpu_has_shadow_vmcs(vmcs12)))
		r = -EINVAL;

	kvm_vcpu_unmap(vcpu, &map, false);
	return r;
}