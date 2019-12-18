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
struct kvm_rmap_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  level; } ;
struct kvm_mmu_page {TYPE_1__ role; int /*<<< orphan*/  gfn; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_PAGES_PER_HPAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ *) ; 
 struct kvm_rmap_head* gfn_to_rmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kvm_mmu_page*) ; 
 int /*<<< orphan*/  kvm_flush_remote_tlbs_with_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_unmap_rmapp (int /*<<< orphan*/ ,struct kvm_rmap_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kvm_mmu_page* page_header (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rmap_recycle(struct kvm_vcpu *vcpu, u64 *spte, gfn_t gfn)
{
	struct kvm_rmap_head *rmap_head;
	struct kvm_mmu_page *sp;

	sp = page_header(__pa(spte));

	rmap_head = gfn_to_rmap(vcpu->kvm, gfn, sp);

	kvm_unmap_rmapp(vcpu->kvm, rmap_head, NULL, gfn, sp->role.level, 0);
	kvm_flush_remote_tlbs_with_address(vcpu->kvm, sp->gfn,
			KVM_PAGES_PER_HPAGE(sp->role.level));
}