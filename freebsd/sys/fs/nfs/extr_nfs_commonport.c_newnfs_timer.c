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
typedef  scalar_t__ time_t ;

/* Variables and functions */
 scalar_t__ NFSD_MONOSEC ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  newnfsd_callout ; 
 int /*<<< orphan*/  nfscl_ticks ; 
 int /*<<< orphan*/  nfsd_call_servertimer () ; 
 int /*<<< orphan*/  stub1 () ; 

void
newnfs_timer(void *arg)
{
	static time_t lasttime = 0;
	/*
	 * Call the server timer, if set up.
	 * The argument indicates if it is the next second and therefore
	 * leases should be checked.
	 */
	if (lasttime != NFSD_MONOSEC) {
		lasttime = NFSD_MONOSEC;
		if (nfsd_call_servertimer != NULL)
			(*nfsd_call_servertimer)();
	}
	callout_reset(&newnfsd_callout, nfscl_ticks, newnfs_timer, NULL);
}