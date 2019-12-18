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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_prof ; 
 int opt_lg_prof_interval ; 
 int opt_prof ; 
 int opt_prof_gdump ; 
 scalar_t__ opt_prof_leak ; 
 int prof_interval ; 

void
prof_boot1(void) {
	cassert(config_prof);

	/*
	 * opt_prof must be in its final state before any arenas are
	 * initialized, so this function must be executed early.
	 */

	if (opt_prof_leak && !opt_prof) {
		/*
		 * Enable opt_prof, but in such a way that profiles are never
		 * automatically dumped.
		 */
		opt_prof = true;
		opt_prof_gdump = false;
	} else if (opt_prof) {
		if (opt_lg_prof_interval >= 0) {
			prof_interval = (((uint64_t)1U) <<
			    opt_lg_prof_interval);
		}
	}
}