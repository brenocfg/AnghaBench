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
 int /*<<< orphan*/  ATOMIC_ACQUIRE ; 
 void* atomic_load_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 scalar_t__ dss_base ; 
 int /*<<< orphan*/  dss_max ; 
 scalar_t__ extent_in_dss_helper (void*,void*) ; 
 int /*<<< orphan*/  have_dss ; 

bool
extent_dss_mergeable(void *addr_a, void *addr_b) {
	void *max;

	cassert(have_dss);

	if ((uintptr_t)addr_a < (uintptr_t)dss_base && (uintptr_t)addr_b <
	    (uintptr_t)dss_base) {
		return true;
	}

	max = atomic_load_p(&dss_max, ATOMIC_ACQUIRE);
	return (extent_in_dss_helper(addr_a, max) ==
	    extent_in_dss_helper(addr_b, max));
}