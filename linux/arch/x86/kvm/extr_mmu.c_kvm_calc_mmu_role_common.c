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
struct TYPE_2__ {int nxe; int /*<<< orphan*/  guest_mode; int /*<<< orphan*/  smm; int /*<<< orphan*/  cr0_wp; int /*<<< orphan*/  access; } ;
union kvm_mmu_role {int /*<<< orphan*/  ext; TYPE_1__ base; int /*<<< orphan*/  member_0; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_ALL ; 
 int /*<<< orphan*/  is_guest_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_nx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_smm (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_write_protection (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_calc_mmu_role_ext (struct kvm_vcpu*) ; 

__attribute__((used)) static union kvm_mmu_role kvm_calc_mmu_role_common(struct kvm_vcpu *vcpu,
						   bool base_only)
{
	union kvm_mmu_role role = {0};

	role.base.access = ACC_ALL;
	role.base.nxe = !!is_nx(vcpu);
	role.base.cr0_wp = is_write_protection(vcpu);
	role.base.smm = is_smm(vcpu);
	role.base.guest_mode = is_guest_mode(vcpu);

	if (base_only)
		return role;

	role.ext = kvm_calc_mmu_role_ext(vcpu);

	return role;
}