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

/* Variables and functions */
 int /*<<< orphan*/  extent_dss_mergeable (void*,void*) ; 
 scalar_t__ have_dss ; 
 int /*<<< orphan*/  maps_coalesce ; 
 int /*<<< orphan*/  opt_retain ; 

__attribute__((used)) static bool
extent_merge_default_impl(void *addr_a, void *addr_b) {
	if (!maps_coalesce && !opt_retain) {
		return true;
	}
	if (have_dss && !extent_dss_mergeable(addr_a, addr_b)) {
		return true;
	}

	return false;
}