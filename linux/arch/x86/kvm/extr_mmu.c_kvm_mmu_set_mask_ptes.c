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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SPTE_SPECIAL_MASK ; 
 int shadow_acc_track_mask ; 
 int shadow_accessed_mask ; 
 int shadow_dirty_mask ; 
 int shadow_me_mask ; 
 int shadow_nx_mask ; 
 int shadow_present_mask ; 
 int shadow_user_mask ; 
 int shadow_x_mask ; 

void kvm_mmu_set_mask_ptes(u64 user_mask, u64 accessed_mask,
		u64 dirty_mask, u64 nx_mask, u64 x_mask, u64 p_mask,
		u64 acc_track_mask, u64 me_mask)
{
	BUG_ON(!dirty_mask != !accessed_mask);
	BUG_ON(!accessed_mask && !acc_track_mask);
	BUG_ON(acc_track_mask & SPTE_SPECIAL_MASK);

	shadow_user_mask = user_mask;
	shadow_accessed_mask = accessed_mask;
	shadow_dirty_mask = dirty_mask;
	shadow_nx_mask = nx_mask;
	shadow_x_mask = x_mask;
	shadow_present_mask = p_mask;
	shadow_acc_track_mask = acc_track_mask;
	shadow_me_mask = me_mask;
}