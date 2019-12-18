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
typedef  int /*<<< orphan*/  isc_task_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_7__ {int /*<<< orphan*/  events; } ;
typedef  TYPE_1__ isc_ondestroy_t ;
struct TYPE_8__ {int /*<<< orphan*/ * ev_sender; } ;
typedef  TYPE_2__ isc_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_LIST_APPEND (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_ONDESTROY (TYPE_1__*) ; 
 int /*<<< orphan*/  ev_link ; 
 int /*<<< orphan*/  isc_task_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

isc_result_t
isc_ondestroy_register(isc_ondestroy_t *ondest, isc_task_t *task,
		       isc_event_t **eventp)
{
	isc_event_t *theevent;
	isc_task_t *thetask = NULL;

	REQUIRE(VALID_ONDESTROY(ondest));
	REQUIRE(task != NULL);
	REQUIRE(eventp != NULL);

	theevent = *eventp;

	REQUIRE(theevent != NULL);

	isc_task_attach(task, &thetask);

	theevent->ev_sender = thetask;

	ISC_LIST_APPEND(ondest->events, theevent, ev_link);

	return (ISC_R_SUCCESS);
}