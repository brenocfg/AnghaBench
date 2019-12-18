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
struct kvm_userspace_memory_region {unsigned long memory_size; } ;
struct kvm_memory_slot {int flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmio_update; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  enum kvm_mr_change { ____Placeholder_kvm_mr_change } kvm_mr_change ;

/* Variables and functions */
 int KVM_MEM_LOG_DIRTY_PAGES ; 
 int KVM_MR_FLAGS_ONLY ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_is_radix (struct kvm*) ; 
 int /*<<< orphan*/  kvmppc_radix_flush_memslot (struct kvm*,struct kvm_memory_slot const*) ; 

__attribute__((used)) static void kvmppc_core_commit_memory_region_hv(struct kvm *kvm,
				const struct kvm_userspace_memory_region *mem,
				const struct kvm_memory_slot *old,
				const struct kvm_memory_slot *new,
				enum kvm_mr_change change)
{
	unsigned long npages = mem->memory_size >> PAGE_SHIFT;

	/*
	 * If we are making a new memslot, it might make
	 * some address that was previously cached as emulated
	 * MMIO be no longer emulated MMIO, so invalidate
	 * all the caches of emulated MMIO translations.
	 */
	if (npages)
		atomic64_inc(&kvm->arch.mmio_update);

	/*
	 * For change == KVM_MR_MOVE or KVM_MR_DELETE, higher levels
	 * have already called kvm_arch_flush_shadow_memslot() to
	 * flush shadow mappings.  For KVM_MR_CREATE we have no
	 * previous mappings.  So the only case to handle is
	 * KVM_MR_FLAGS_ONLY when the KVM_MEM_LOG_DIRTY_PAGES bit
	 * has been changed.
	 * For radix guests, we flush on setting KVM_MEM_LOG_DIRTY_PAGES
	 * to get rid of any THP PTEs in the partition-scoped page tables
	 * so we can track dirtiness at the page level; we flush when
	 * clearing KVM_MEM_LOG_DIRTY_PAGES so that we can go back to
	 * using THP PTEs.
	 */
	if (change == KVM_MR_FLAGS_ONLY && kvm_is_radix(kvm) &&
	    ((new->flags ^ old->flags) & KVM_MEM_LOG_DIRTY_PAGES))
		kvmppc_radix_flush_memslot(kvm, old);
}