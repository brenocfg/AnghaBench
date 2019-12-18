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
typedef  scalar_t__ isc_uint32_t ;
typedef  int /*<<< orphan*/  isc_task_t ;
typedef  scalar_t__ isc_result_t ;
struct TYPE_8__ {scalar_t__ pertic; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; int /*<<< orphan*/  timer; int /*<<< orphan*/  pending; } ;
typedef  TYPE_1__ isc_ratelimiter_t ;
struct TYPE_9__ {int /*<<< orphan*/ * ev_sender; scalar_t__ ev_arg; } ;
typedef  TYPE_2__ isc_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_FALSE ; 
 TYPE_2__* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_LIST_UNLINK (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RUNTIME_CHECK (int) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ev_link ; 
 int /*<<< orphan*/  isc_event_free (TYPE_2__**) ; 
 int /*<<< orphan*/  isc_ratelimiter_idle ; 
 int /*<<< orphan*/  isc_task_send (int /*<<< orphan*/ *,TYPE_2__**) ; 
 scalar_t__ isc_timer_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_timertype_inactive ; 

__attribute__((used)) static void
ratelimiter_tick(isc_task_t *task, isc_event_t *event) {
	isc_result_t result = ISC_R_SUCCESS;
	isc_ratelimiter_t *rl = (isc_ratelimiter_t *)event->ev_arg;
	isc_event_t *p;
	isc_uint32_t pertic;

	UNUSED(task);

	isc_event_free(&event);

	pertic = rl->pertic;
        while (pertic != 0) {
		pertic--;
		LOCK(&rl->lock);
		p = ISC_LIST_HEAD(rl->pending);
		if (p != NULL) {
			/*
			 * There is work to do.  Let's do it after unlocking.
			 */
			ISC_LIST_UNLINK(rl->pending, p, ev_link);
		} else {
			/*
			 * No work left to do.  Stop the timer so that we don't
			 * waste resources by having it fire periodically.
			 */
			result = isc_timer_reset(rl->timer,
						 isc_timertype_inactive,
						 NULL, NULL, ISC_FALSE);
			RUNTIME_CHECK(result == ISC_R_SUCCESS);
			rl->state = isc_ratelimiter_idle;
			pertic = 0;	/* Force the loop to exit. */
		}
		UNLOCK(&rl->lock);
		if (p != NULL) {
			isc_task_t *evtask = p->ev_sender;
			isc_task_send(evtask, &p);
		}
		INSIST(p == NULL);
	}
}