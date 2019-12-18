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
typedef  int /*<<< orphan*/  tsd_t ;

/* Variables and functions */
 int THREAD_EVENT_MIN_START_WAIT ; 
 int /*<<< orphan*/  config_prof ; 
 int lg_prof_sample ; 
 int log (double) ; 
 int prng_lg_range_u64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  thread_prof_sample_event_update (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tsd_prng_statep_get (int /*<<< orphan*/ *) ; 

void
prof_sample_threshold_update(tsd_t *tsd) {
#ifdef JEMALLOC_PROF
	if (!config_prof) {
		return;
	}

	if (lg_prof_sample == 0) {
		thread_prof_sample_event_update(tsd,
		    THREAD_EVENT_MIN_START_WAIT);
		return;
	}

	/*
	 * Compute sample interval as a geometrically distributed random
	 * variable with mean (2^lg_prof_sample).
	 *
	 *                      __        __
	 *                      |  log(u)  |                     1
	 * bytes_until_sample = | -------- |, where p = ---------------
	 *                      | log(1-p) |             lg_prof_sample
	 *                                              2
	 *
	 * For more information on the math, see:
	 *
	 *   Non-Uniform Random Variate Generation
	 *   Luc Devroye
	 *   Springer-Verlag, New York, 1986
	 *   pp 500
	 *   (http://luc.devroye.org/rnbookindex.html)
	 */
	uint64_t r = prng_lg_range_u64(tsd_prng_statep_get(tsd), 53);
	double u = (double)r * (1.0/9007199254740992.0L);
	uint64_t bytes_until_sample = (uint64_t)(log(u) /
	    log(1.0 - (1.0 / (double)((uint64_t)1U << lg_prof_sample))))
	    + (uint64_t)1U;
	thread_prof_sample_event_update(tsd, bytes_until_sample);
#endif
}