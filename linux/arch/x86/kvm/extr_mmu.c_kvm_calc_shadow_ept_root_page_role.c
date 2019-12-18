#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int execonly; } ;
struct TYPE_11__ {int gpte_is_8_bytes; int direct; int ad_disabled; int guest_mode; int cr0_wp; int smap_andnot_wp; int /*<<< orphan*/  access; int /*<<< orphan*/  level; int /*<<< orphan*/  smm; } ;
union kvm_mmu_role {TYPE_6__ ext; TYPE_5__ base; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int /*<<< orphan*/  smm; } ;
struct TYPE_8__ {TYPE_1__ base; } ;
struct TYPE_9__ {TYPE_2__ mmu_role; } ;
struct TYPE_10__ {TYPE_3__ root_mmu; } ;
struct kvm_vcpu {TYPE_4__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_ALL ; 
 int /*<<< orphan*/  PT64_ROOT_4LEVEL ; 
 TYPE_6__ kvm_calc_mmu_role_ext (struct kvm_vcpu*) ; 

__attribute__((used)) static union kvm_mmu_role
kvm_calc_shadow_ept_root_page_role(struct kvm_vcpu *vcpu, bool accessed_dirty,
				   bool execonly)
{
	union kvm_mmu_role role = {0};

	/* SMM flag is inherited from root_mmu */
	role.base.smm = vcpu->arch.root_mmu.mmu_role.base.smm;

	role.base.level = PT64_ROOT_4LEVEL;
	role.base.gpte_is_8_bytes = true;
	role.base.direct = false;
	role.base.ad_disabled = !accessed_dirty;
	role.base.guest_mode = true;
	role.base.access = ACC_ALL;

	/*
	 * WP=1 and NOT_WP=1 is an impossible combination, use WP and the
	 * SMAP variation to denote shadow EPT entries.
	 */
	role.base.cr0_wp = true;
	role.base.smap_andnot_wp = true;

	role.ext = kvm_calc_mmu_role_ext(vcpu);
	role.ext.execonly = execonly;

	return role;
}