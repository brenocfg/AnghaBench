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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct TYPE_2__ {int /*<<< orphan*/  level; } ;
struct kvm_mmu_page {TYPE_1__ role; int /*<<< orphan*/  gfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_PAGES_PER_HPAGE (int /*<<< orphan*/ ) ; 
 scalar_t__ __drop_large_spte (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_flush_remote_tlbs_with_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kvm_mmu_page* page_header (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drop_large_spte(struct kvm_vcpu *vcpu, u64 *sptep)
{
	if (__drop_large_spte(vcpu->kvm, sptep)) {
		struct kvm_mmu_page *sp = page_header(__pa(sptep));

		kvm_flush_remote_tlbs_with_address(vcpu->kvm, sp->gfn,
			KVM_PAGES_PER_HPAGE(sp->role.level));
	}
}