#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_task_t ;
typedef  int /*<<< orphan*/  isc_sockfdwatch_t ;
struct TYPE_7__ {TYPE_1__* methods; } ;
typedef  TYPE_2__ isc_socketmgr_t ;
typedef  int /*<<< orphan*/  isc_socket_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* fdwatchcreate ) (TYPE_2__*,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ISCAPI_SOCKETMGR_VALID (TYPE_2__*) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

isc_result_t
isc_socket_fdwatchcreate(isc_socketmgr_t *manager, int fd, int flags,
			 isc_sockfdwatch_t callback, void *cbarg,
			 isc_task_t *task, isc_socket_t **socketp)
{
	REQUIRE(ISCAPI_SOCKETMGR_VALID(manager));

	return (manager->methods->fdwatchcreate(manager, fd, flags,
						callback, cbarg, task,
						socketp));
}