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
struct TYPE_2__ {unsigned long n_used_mmu_pages; unsigned long n_max_mmu_pages; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalid_list ; 
 int /*<<< orphan*/  kvm_mmu_commit_zap_page (struct kvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_zap_oldest_mmu_page (struct kvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void kvm_mmu_change_mmu_pages(struct kvm *kvm, unsigned long goal_nr_mmu_pages)
{
	LIST_HEAD(invalid_list);

	spin_lock(&kvm->mmu_lock);

	if (kvm->arch.n_used_mmu_pages > goal_nr_mmu_pages) {
		/* Need to free some mmu pages to achieve the goal. */
		while (kvm->arch.n_used_mmu_pages > goal_nr_mmu_pages)
			if (!prepare_zap_oldest_mmu_page(kvm, &invalid_list))
				break;

		kvm_mmu_commit_zap_page(kvm, &invalid_list);
		goal_nr_mmu_pages = kvm->arch.n_used_mmu_pages;
	}

	kvm->arch.n_max_mmu_pages = goal_nr_mmu_pages;

	spin_unlock(&kvm->mmu_lock);
}