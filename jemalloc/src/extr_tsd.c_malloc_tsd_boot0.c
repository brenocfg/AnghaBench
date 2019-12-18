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
 int /*<<< orphan*/  WITNESS_RANK_OMIT ; 
 scalar_t__ malloc_mutex_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_rank_exclusive ; 
 scalar_t__ ncleanups ; 
 int* tsd_arenas_tdata_bypassp_get (int /*<<< orphan*/ *) ; 
 scalar_t__ tsd_boot0 () ; 
 int /*<<< orphan*/ * tsd_fetch () ; 
 int /*<<< orphan*/  tsd_nominal_tsds_lock ; 

tsd_t *
malloc_tsd_boot0(void) {
	tsd_t *tsd;

	ncleanups = 0;
	if (malloc_mutex_init(&tsd_nominal_tsds_lock, "tsd_nominal_tsds_lock",
	    WITNESS_RANK_OMIT, malloc_mutex_rank_exclusive)) {
		return NULL;
	}
	if (tsd_boot0()) {
		return NULL;
	}
	tsd = tsd_fetch();
	*tsd_arenas_tdata_bypassp_get(tsd) = true;
	return tsd;
}