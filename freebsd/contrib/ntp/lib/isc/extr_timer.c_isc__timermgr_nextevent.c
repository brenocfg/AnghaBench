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
typedef  int /*<<< orphan*/  isc_timermgr_t ;
typedef  int /*<<< orphan*/  isc_time_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_3__ {scalar_t__ nscheduled; int /*<<< orphan*/  due; } ;
typedef  TYPE_1__ isc__timermgr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_NOTFOUND ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 TYPE_1__* timermgr ; 

isc_result_t
isc__timermgr_nextevent(isc_timermgr_t *manager0, isc_time_t *when) {
	isc__timermgr_t *manager = (isc__timermgr_t *)manager0;

#ifdef USE_SHARED_MANAGER
	if (manager == NULL)
		manager = timermgr;
#endif
	if (manager == NULL || manager->nscheduled == 0)
		return (ISC_R_NOTFOUND);
	*when = manager->due;
	return (ISC_R_SUCCESS);
}