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
struct kvm_memory_slot {int dummy; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  gfn_t ;
typedef  enum kvm_page_track_mode { ____Placeholder_kvm_page_track_mode } kvm_page_track_mode ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kvm_mmu_gfn_allow_lpage (struct kvm_memory_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_track_mode_is_valid (int) ; 
 int /*<<< orphan*/  update_gfn_track (struct kvm_memory_slot*,int /*<<< orphan*/ ,int,int) ; 

void kvm_slot_page_track_remove_page(struct kvm *kvm,
				     struct kvm_memory_slot *slot, gfn_t gfn,
				     enum kvm_page_track_mode mode)
{
	if (WARN_ON(!page_track_mode_is_valid(mode)))
		return;

	update_gfn_track(slot, gfn, mode, -1);

	/*
	 * allow large page mapping for the tracked page
	 * after the tracker is gone.
	 */
	kvm_mmu_gfn_allow_lpage(slot, gfn);
}