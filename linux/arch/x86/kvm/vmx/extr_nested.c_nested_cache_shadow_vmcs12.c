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
struct vmcs12 {unsigned long long vmcs_link_pointer; } ;
struct kvm_vcpu {int dummy; } ;
struct kvm_host_map {int /*<<< orphan*/  hva; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCS12_SIZE ; 
 struct vmcs12* get_shadow_vmcs12 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  gpa_to_gfn (unsigned long long) ; 
 scalar_t__ kvm_vcpu_map (struct kvm_vcpu*,int /*<<< orphan*/ ,struct kvm_host_map*) ; 
 int /*<<< orphan*/  kvm_vcpu_unmap (struct kvm_vcpu*,struct kvm_host_map*,int) ; 
 int /*<<< orphan*/  memcpy (struct vmcs12*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_cpu_has_shadow_vmcs (struct vmcs12*) ; 

__attribute__((used)) static void nested_cache_shadow_vmcs12(struct kvm_vcpu *vcpu,
				       struct vmcs12 *vmcs12)
{
	struct kvm_host_map map;
	struct vmcs12 *shadow;

	if (!nested_cpu_has_shadow_vmcs(vmcs12) ||
	    vmcs12->vmcs_link_pointer == -1ull)
		return;

	shadow = get_shadow_vmcs12(vcpu);

	if (kvm_vcpu_map(vcpu, gpa_to_gfn(vmcs12->vmcs_link_pointer), &map))
		return;

	memcpy(shadow, map.hva, VMCS12_SIZE);
	kvm_vcpu_unmap(vcpu, &map, false);
}