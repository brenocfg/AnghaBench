#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_event_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  events; int /*<<< orphan*/  on_shutdown; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ isc__task_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_MSGSET_GENERAL ; 
 int /*<<< orphan*/  ISC_MSG_SHUTTINGDOWN ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/ * PREV (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_F_SHUTTINGDOWN ; 
 int /*<<< orphan*/  TASK_SHUTTINGDOWN (TYPE_1__*) ; 
 int /*<<< orphan*/  XTRACE (char*) ; 
 int /*<<< orphan*/  ev_link ; 
 int /*<<< orphan*/  isc_msgcat ; 
 char* isc_msgcat_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ task_state_idle ; 
 scalar_t__ task_state_ready ; 
 scalar_t__ task_state_running ; 

__attribute__((used)) static inline isc_boolean_t
task_shutdown(isc__task_t *task) {
	isc_boolean_t was_idle = ISC_FALSE;
	isc_event_t *event, *prev;

	/*
	 * Caller must be holding the task's lock.
	 */

	XTRACE("task_shutdown");

	if (! TASK_SHUTTINGDOWN(task)) {
		XTRACE(isc_msgcat_get(isc_msgcat, ISC_MSGSET_GENERAL,
				      ISC_MSG_SHUTTINGDOWN, "shutting down"));
		task->flags |= TASK_F_SHUTTINGDOWN;
		if (task->state == task_state_idle) {
			INSIST(EMPTY(task->events));
			task->state = task_state_ready;
			was_idle = ISC_TRUE;
		}
		INSIST(task->state == task_state_ready ||
		       task->state == task_state_running);

		/*
		 * Note that we post shutdown events LIFO.
		 */
		for (event = TAIL(task->on_shutdown);
		     event != NULL;
		     event = prev) {
			prev = PREV(event, ev_link);
			DEQUEUE(task->on_shutdown, event, ev_link);
			ENQUEUE(task->events, event, ev_link);
		}
	}

	return (was_idle);
}