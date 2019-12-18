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
 int* tsd_arenas_tdata_bypassp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_boot1 () ; 
 int /*<<< orphan*/ * tsd_fetch () ; 
 int /*<<< orphan*/  tsd_slow_update (int /*<<< orphan*/ *) ; 

void
malloc_tsd_boot1(void) {
	tsd_boot1();
	tsd_t *tsd = tsd_fetch();
	/* malloc_slow has been set properly.  Update tsd_slow. */
	tsd_slow_update(tsd);
	*tsd_arenas_tdata_bypassp_get(tsd) = false;
}