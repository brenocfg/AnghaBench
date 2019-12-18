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
 scalar_t__ PAGE ; 
 scalar_t__ SC_LARGE_MAXCLASS ; 
 scalar_t__ SC_LARGE_MINCLASS ; 
 int /*<<< orphan*/  huge_arena_ind ; 
 int /*<<< orphan*/  narenas_total_get () ; 
 scalar_t__ opt_oversize_threshold ; 
 scalar_t__ oversize_threshold ; 

bool
arena_init_huge(void) {
	bool huge_enabled;

	/* The threshold should be large size class. */
	if (opt_oversize_threshold > SC_LARGE_MAXCLASS ||
	    opt_oversize_threshold < SC_LARGE_MINCLASS) {
		opt_oversize_threshold = 0;
		oversize_threshold = SC_LARGE_MAXCLASS + PAGE;
		huge_enabled = false;
	} else {
		/* Reserve the index for the huge arena. */
		huge_arena_ind = narenas_total_get();
		oversize_threshold = opt_oversize_threshold;
		huge_enabled = true;
	}

	return huge_enabled;
}