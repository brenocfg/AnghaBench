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
typedef  int /*<<< orphan*/  isc_timermgr_t ;
typedef  int /*<<< orphan*/  isc_time_t ;
typedef  int /*<<< orphan*/  isc__timermgr_t ;

/* Variables and functions */
 int /*<<< orphan*/  TIME_NOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * timermgr ; 

void
isc__timermgr_dispatch(isc_timermgr_t *manager0) {
	isc__timermgr_t *manager = (isc__timermgr_t *)manager0;
	isc_time_t now;

#ifdef USE_SHARED_MANAGER
	if (manager == NULL)
		manager = timermgr;
#endif
	if (manager == NULL)
		return;
	TIME_NOW(&now);
	dispatch(manager, &now);
}