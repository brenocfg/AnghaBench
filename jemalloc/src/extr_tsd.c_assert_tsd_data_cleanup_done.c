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
typedef  int /*<<< orphan*/  tsd_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ ** tsd_arenap_get_unsafe (int /*<<< orphan*/ *) ; 
 int* tsd_arenas_tdata_bypassp_get_unsafe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** tsd_arenas_tdatap_get_unsafe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** tsd_iarenap_get_unsafe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_in_nominal_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_nominal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** tsd_prof_tdatap_get_unsafe (int /*<<< orphan*/ *) ; 
 int* tsd_tcache_enabledp_get_unsafe (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
assert_tsd_data_cleanup_done(tsd_t *tsd) {
	assert(!tsd_nominal(tsd));
	assert(!tsd_in_nominal_list(tsd));
	assert(*tsd_arenap_get_unsafe(tsd) == NULL);
	assert(*tsd_iarenap_get_unsafe(tsd) == NULL);
	assert(*tsd_arenas_tdata_bypassp_get_unsafe(tsd) == true);
	assert(*tsd_arenas_tdatap_get_unsafe(tsd) == NULL);
	assert(*tsd_tcache_enabledp_get_unsafe(tsd) == false);
	assert(*tsd_prof_tdatap_get_unsafe(tsd) == NULL);
}