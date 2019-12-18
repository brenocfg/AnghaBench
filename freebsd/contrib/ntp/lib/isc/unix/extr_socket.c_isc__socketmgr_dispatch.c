#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  writeset; int /*<<< orphan*/  readset; int /*<<< orphan*/  maxfd; int /*<<< orphan*/  nevents; } ;
typedef  TYPE_1__ isc_socketwait_t ;
typedef  int /*<<< orphan*/  isc_socketmgr_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_8__ {int /*<<< orphan*/  events; } ;
typedef  TYPE_2__ isc__socketmgr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_NOTFOUND ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  process_fds (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 TYPE_2__* socketmgr ; 
 TYPE_1__ swait_private ; 

isc_result_t
isc__socketmgr_dispatch(isc_socketmgr_t *manager0, isc_socketwait_t *swait) {
	isc__socketmgr_t *manager = (isc__socketmgr_t *)manager0;

	REQUIRE(swait == &swait_private);

#ifdef USE_SHARED_MANAGER
	if (manager == NULL)
		manager = socketmgr;
#endif
	if (manager == NULL)
		return (ISC_R_NOTFOUND);

#if defined(USE_KQUEUE) || defined(USE_EPOLL) || defined(USE_DEVPOLL)
	(void)process_fds(manager, manager->events, swait->nevents);
	return (ISC_R_SUCCESS);
#elif defined(USE_SELECT)
	process_fds(manager, swait->maxfd, swait->readset, swait->writeset);
	return (ISC_R_SUCCESS);
#endif
}