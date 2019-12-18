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
 int /*<<< orphan*/  arena_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arenas_tdata_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iarena_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_tdata_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcache_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_witness_tsdp_get_unsafe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  witnesses_cleanup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tsd_do_data_cleanup(tsd_t *tsd) {
	prof_tdata_cleanup(tsd);
	iarena_cleanup(tsd);
	arena_cleanup(tsd);
	arenas_tdata_cleanup(tsd);
	tcache_cleanup(tsd);
	witnesses_cleanup(tsd_witness_tsdp_get_unsafe(tsd));
}