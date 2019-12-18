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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  tsd_t ;

/* Variables and functions */
 scalar_t__ config_debug ; 
 int /*<<< orphan*/  rtree_ctx_data_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tsd_prng_statep_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_rtree_ctxp_get_unsafe (int /*<<< orphan*/ *) ; 
 int tsd_tcache_enabled_data_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_thread_event_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
tsd_data_init(tsd_t *tsd) {
	/*
	 * We initialize the rtree context first (before the tcache), since the
	 * tcache initialization depends on it.
	 */
	rtree_ctx_data_init(tsd_rtree_ctxp_get_unsafe(tsd));

	/*
	 * A nondeterministic seed based on the address of tsd reduces
	 * the likelihood of lockstep non-uniform cache index
	 * utilization among identical concurrent processes, but at the
	 * cost of test repeatability.  For debug builds, instead use a
	 * deterministic seed.
	 */
	*tsd_prng_statep_get(tsd) = config_debug ? 0 :
	    (uint64_t)(uintptr_t)tsd;

	/* event_init may use the prng state above. */
	tsd_thread_event_init(tsd);

	return tsd_tcache_enabled_data_init(tsd);
}