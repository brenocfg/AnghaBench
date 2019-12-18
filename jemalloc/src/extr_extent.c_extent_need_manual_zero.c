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
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  arena_has_default_hooks (int /*<<< orphan*/ *) ; 
 scalar_t__ opt_thp ; 
 scalar_t__ thp_mode_always ; 

__attribute__((used)) static bool
extent_need_manual_zero(arena_t *arena) {
	/*
	 * Need to manually zero the extent on repopulating if either; 1) non
	 * default extent hooks installed (in which case the purge semantics may
	 * change); or 2) transparent huge pages enabled.
	 */
	return (!arena_has_default_hooks(arena) ||
		(opt_thp == thp_mode_always));
}