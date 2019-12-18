#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_3__ {int active; } ;
typedef  TYPE_1__ prof_tdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* prof_tdata_get (int /*<<< orphan*/ *,int) ; 
 scalar_t__ tsd_reentrancy_level_get (int /*<<< orphan*/ *) ; 

bool
prof_thread_active_set(tsd_t *tsd, bool active) {
	assert(tsd_reentrancy_level_get(tsd) == 0);

	prof_tdata_t *tdata;

	tdata = prof_tdata_get(tsd, true);
	if (tdata == NULL) {
		return true;
	}
	tdata->active = active;
	return false;
}