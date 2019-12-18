#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_task_t ;
struct TYPE_8__ {int /*<<< orphan*/  events; } ;
typedef  TYPE_1__ isc_ondestroy_t ;
struct TYPE_9__ {int /*<<< orphan*/ * ev_sender; } ;
typedef  TYPE_2__ isc_event_t ;

/* Variables and functions */
 TYPE_2__* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_LIST_UNLINK (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_ONDESTROY (TYPE_1__*) ; 
 int /*<<< orphan*/  ev_link ; 
 int /*<<< orphan*/  isc_task_sendanddetach (int /*<<< orphan*/ **,TYPE_2__**) ; 

void
isc_ondestroy_notify(isc_ondestroy_t *ondest, void *sender) {
	isc_event_t *eventp;
	isc_task_t *task;

	REQUIRE(VALID_ONDESTROY(ondest));

	eventp = ISC_LIST_HEAD(ondest->events);
	while (eventp != NULL) {
		ISC_LIST_UNLINK(ondest->events, eventp, ev_link);

		task = eventp->ev_sender;
		eventp->ev_sender = sender;

		isc_task_sendanddetach(&task, &eventp);

		eventp = ISC_LIST_HEAD(ondest->events);
	}
}