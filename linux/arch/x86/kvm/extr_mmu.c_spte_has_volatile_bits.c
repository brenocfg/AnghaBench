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
 scalar_t__ is_access_track_spte (int) ; 
 int /*<<< orphan*/  is_shadow_present_pte (int) ; 
 scalar_t__ is_writable_pte (int) ; 
 int shadow_accessed_mask ; 
 int shadow_dirty_mask ; 
 scalar_t__ spte_ad_enabled (int) ; 
 scalar_t__ spte_can_locklessly_be_made_writable (int) ; 

__attribute__((used)) static bool spte_has_volatile_bits(u64 spte)
{
	if (!is_shadow_present_pte(spte))
		return false;

	/*
	 * Always atomically update spte if it can be updated
	 * out of mmu-lock, it can ensure dirty bit is not lost,
	 * also, it can help us to get a stable is_writable_pte()
	 * to ensure tlb flush is not missed.
	 */
	if (spte_can_locklessly_be_made_writable(spte) ||
	    is_access_track_spte(spte))
		return true;

	if (spte_ad_enabled(spte)) {
		if ((spte & shadow_accessed_mask) == 0 ||
	    	    (is_writable_pte(spte) && (spte & shadow_dirty_mask) == 0))
			return true;
	}

	return false;
}