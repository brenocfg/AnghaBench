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
struct TYPE_3__ {int ad_disabled; int direct; int gpte_is_8_bytes; int /*<<< orphan*/  level; } ;
union kvm_mmu_role {TYPE_1__ base; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_tdp_level ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 union kvm_mmu_role kvm_calc_mmu_role_common (struct kvm_vcpu*,int) ; 
 TYPE_2__* kvm_x86_ops ; 
 scalar_t__ shadow_accessed_mask ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 

__attribute__((used)) static union kvm_mmu_role
kvm_calc_tdp_mmu_root_page_role(struct kvm_vcpu *vcpu, bool base_only)
{
	union kvm_mmu_role role = kvm_calc_mmu_role_common(vcpu, base_only);

	role.base.ad_disabled = (shadow_accessed_mask == 0);
	role.base.level = kvm_x86_ops->get_tdp_level(vcpu);
	role.base.direct = true;
	role.base.gpte_is_8_bytes = true;

	return role;
}