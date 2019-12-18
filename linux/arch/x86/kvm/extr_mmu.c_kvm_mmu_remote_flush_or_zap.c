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
struct list_head {int dummy; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_flush_remote_tlbs (struct kvm*) ; 
 int /*<<< orphan*/  kvm_mmu_commit_zap_page (struct kvm*,struct list_head*) ; 
 scalar_t__ list_empty (struct list_head*) ; 

__attribute__((used)) static bool kvm_mmu_remote_flush_or_zap(struct kvm *kvm,
					struct list_head *invalid_list,
					bool remote_flush)
{
	if (!remote_flush && list_empty(invalid_list))
		return false;

	if (!list_empty(invalid_list))
		kvm_mmu_commit_zap_page(kvm, invalid_list);
	else
		kvm_flush_remote_tlbs(kvm);
	return true;
}