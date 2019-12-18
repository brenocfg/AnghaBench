#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* mmu; } ;
struct kvm_vcpu {TYPE_3__* kvm; TYPE_2__ arch; } ;
struct kvm_mmu_page {int /*<<< orphan*/  unsync_children; int /*<<< orphan*/  unsync; } ;
typedef  int /*<<< orphan*/  hpa_t ;
struct TYPE_6__ {int /*<<< orphan*/  mmu_lock; } ;
struct TYPE_4__ {scalar_t__ root_level; int /*<<< orphan*/ * pae_root; int /*<<< orphan*/  root_hpa; scalar_t__ direct_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_POST_SYNC ; 
 int /*<<< orphan*/  AUDIT_PRE_SYNC ; 
 int /*<<< orphan*/  MMIO_GVA_ANY ; 
 int /*<<< orphan*/  PT64_BASE_ADDR_MASK ; 
 scalar_t__ PT64_ROOT_4LEVEL ; 
 scalar_t__ VALID_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_mmu_audit (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_sync_children (struct kvm_vcpu*,struct kvm_mmu_page*) ; 
 struct kvm_mmu_page* page_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_load_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcpu_clear_mmio_info (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

void kvm_mmu_sync_roots(struct kvm_vcpu *vcpu)
{
	int i;
	struct kvm_mmu_page *sp;

	if (vcpu->arch.mmu->direct_map)
		return;

	if (!VALID_PAGE(vcpu->arch.mmu->root_hpa))
		return;

	vcpu_clear_mmio_info(vcpu, MMIO_GVA_ANY);

	if (vcpu->arch.mmu->root_level >= PT64_ROOT_4LEVEL) {
		hpa_t root = vcpu->arch.mmu->root_hpa;
		sp = page_header(root);

		/*
		 * Even if another CPU was marking the SP as unsync-ed
		 * simultaneously, any guest page table changes are not
		 * guaranteed to be visible anyway until this VCPU issues a TLB
		 * flush strictly after those changes are made. We only need to
		 * ensure that the other CPU sets these flags before any actual
		 * changes to the page tables are made. The comments in
		 * mmu_need_write_protect() describe what could go wrong if this
		 * requirement isn't satisfied.
		 */
		if (!smp_load_acquire(&sp->unsync) &&
		    !smp_load_acquire(&sp->unsync_children))
			return;

		spin_lock(&vcpu->kvm->mmu_lock);
		kvm_mmu_audit(vcpu, AUDIT_PRE_SYNC);

		mmu_sync_children(vcpu, sp);

		kvm_mmu_audit(vcpu, AUDIT_POST_SYNC);
		spin_unlock(&vcpu->kvm->mmu_lock);
		return;
	}

	spin_lock(&vcpu->kvm->mmu_lock);
	kvm_mmu_audit(vcpu, AUDIT_PRE_SYNC);

	for (i = 0; i < 4; ++i) {
		hpa_t root = vcpu->arch.mmu->pae_root[i];

		if (root && VALID_PAGE(root)) {
			root &= PT64_BASE_ADDR_MASK;
			sp = page_header(root);
			mmu_sync_children(vcpu, sp);
		}
	}

	kvm_mmu_audit(vcpu, AUDIT_POST_SYNC);
	spin_unlock(&vcpu->kvm->mmu_lock);
}