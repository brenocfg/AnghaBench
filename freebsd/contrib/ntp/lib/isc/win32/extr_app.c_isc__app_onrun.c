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
typedef  int /*<<< orphan*/  isc_taskaction_t ;
typedef  int /*<<< orphan*/  isc_task_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;
typedef  int /*<<< orphan*/  isc_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_APPEVENT_SHUTDOWN ; 
 int /*<<< orphan*/  ISC_LIST_APPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_R_ALREADYRUNNING ; 
 int /*<<< orphan*/  ISC_R_NOMEMORY ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ev_link ; 
 int /*<<< orphan*/ * isc_event_allocate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  isc_task_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  on_run ; 
 scalar_t__ running ; 

isc_result_t
isc__app_onrun(isc_mem_t *mctx, isc_task_t *task, isc_taskaction_t action,
	      void *arg) {
	isc_event_t *event;
	isc_task_t *cloned_task = NULL;
	isc_result_t result;


	LOCK(&lock);
	if (running) {
		result = ISC_R_ALREADYRUNNING;
		goto unlock;
	}

	/*
	 * Note that we store the task to which we're going to send the event
	 * in the event's "sender" field.
	 */
	isc_task_attach(task, &cloned_task);
	event = isc_event_allocate(mctx, cloned_task, ISC_APPEVENT_SHUTDOWN,
				   action, arg, sizeof(*event));
	if (event == NULL) {
		result = ISC_R_NOMEMORY;
		goto unlock;
	}

	ISC_LIST_APPEND(on_run, event, ev_link);
	result = ISC_R_SUCCESS;

 unlock:
	UNLOCK(&lock);
	return (result);
}