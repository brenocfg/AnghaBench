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
typedef  int /*<<< orphan*/  extent_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ extent_base_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_is_head_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_sn_comp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ maps_coalesce ; 
 int /*<<< orphan*/  opt_retain ; 

__attribute__((used)) static bool
extent_head_no_merge(extent_t *a, extent_t *b) {
	assert(extent_base_get(a) < extent_base_get(b));
	/*
	 * When coalesce is not always allowed (Windows), only merge extents
	 * from the same VirtualAlloc region under opt.retain (in which case
	 * MEM_DECOMMIT is utilized for purging).
	 */
	if (maps_coalesce) {
		return false;
	}
	if (!opt_retain) {
		return true;
	}
	/* If b is a head extent, disallow the cross-region merge. */
	if (extent_is_head_get(b)) {
		/*
		 * Additionally, sn should not overflow with retain; sanity
		 * check that different regions have unique sn.
		 */
		assert(extent_sn_comp(a, b) != 0);
		return true;
	}
	assert(extent_sn_comp(a, b) == 0);

	return false;
}