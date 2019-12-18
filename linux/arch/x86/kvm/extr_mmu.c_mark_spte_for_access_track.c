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
typedef  int u64 ;

/* Variables and functions */
 int PT_WRITABLE_MASK ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 scalar_t__ is_access_track_spte (int) ; 
 int shadow_acc_track_mask ; 
 int shadow_acc_track_saved_bits_mask ; 
 int shadow_acc_track_saved_bits_shift ; 
 int shadow_accessed_mask ; 
 scalar_t__ spte_ad_enabled (int) ; 
 int /*<<< orphan*/  spte_can_locklessly_be_made_writable (int) ; 

__attribute__((used)) static u64 mark_spte_for_access_track(u64 spte)
{
	if (spte_ad_enabled(spte))
		return spte & ~shadow_accessed_mask;

	if (is_access_track_spte(spte))
		return spte;

	/*
	 * Making an Access Tracking PTE will result in removal of write access
	 * from the PTE. So, verify that we will be able to restore the write
	 * access in the fast page fault path later on.
	 */
	WARN_ONCE((spte & PT_WRITABLE_MASK) &&
		  !spte_can_locklessly_be_made_writable(spte),
		  "kvm: Writable SPTE is not locklessly dirty-trackable\n");

	WARN_ONCE(spte & (shadow_acc_track_saved_bits_mask <<
			  shadow_acc_track_saved_bits_shift),
		  "kvm: Access Tracking saved bit locations are not zero\n");

	spte |= (spte & shadow_acc_track_saved_bits_mask) <<
		shadow_acc_track_saved_bits_shift;
	spte &= ~shadow_acc_track_mask;

	return spte;
}