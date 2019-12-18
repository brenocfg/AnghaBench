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
typedef  void* isc_time_t ;
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  isc_interval_t ;
typedef  scalar_t__ isc_boolean_t ;
struct TYPE_6__ {scalar_t__ nscheduled; void* due; int /*<<< orphan*/  wakeup; int /*<<< orphan*/  heap; } ;
typedef  TYPE_1__ isc__timermgr_t ;
struct TYPE_7__ {scalar_t__ type; void* expires; void* idle; int index; void* due; int /*<<< orphan*/  interval; TYPE_1__* manager; } ;
typedef  TYPE_2__ isc__timer_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 scalar_t__ ISC_FALSE ; 
 int /*<<< orphan*/  ISC_LOGCATEGORY_GENERAL ; 
 int /*<<< orphan*/  ISC_LOGMODULE_TIMER ; 
 int /*<<< orphan*/  ISC_LOG_WARNING ; 
 int /*<<< orphan*/  ISC_MSGSET_TIMER ; 
 int /*<<< orphan*/  ISC_MSG_SCHEDULE ; 
 int /*<<< orphan*/  ISC_MSG_SIGNALSCHED ; 
 scalar_t__ ISC_R_NOMEMORY ; 
 scalar_t__ ISC_R_SUCCESS ; 
 scalar_t__ ISC_TF (int) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  SIGNAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNUSED (scalar_t__) ; 
 int /*<<< orphan*/  XTRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XTRACETIMER (int /*<<< orphan*/ ,TYPE_2__*,void*) ; 
 int /*<<< orphan*/  isc_heap_decreased (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isc_heap_increased (int /*<<< orphan*/ ,int) ; 
 scalar_t__ isc_heap_insert (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  isc_interval_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_lctx ; 
 int /*<<< orphan*/  isc_log_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  isc_msgcat ; 
 int /*<<< orphan*/  isc_msgcat_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isc_time_add (void**,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ isc_time_compare (void**,void**) ; 
 scalar_t__ isc_time_isepoch (void**) ; 
 scalar_t__ isc_time_seconds (void**) ; 
 scalar_t__ isc_timertype_inactive ; 
 scalar_t__ isc_timertype_limited ; 
 scalar_t__ isc_timertype_once ; 

__attribute__((used)) static inline isc_result_t
schedule(isc__timer_t *timer, isc_time_t *now, isc_boolean_t signal_ok) {
	isc_result_t result;
	isc__timermgr_t *manager;
	isc_time_t due;
	int cmp;
#ifdef USE_TIMER_THREAD
	isc_boolean_t timedwait;
#endif

	/*!
	 * Note: the caller must ensure locking.
	 */

	REQUIRE(timer->type != isc_timertype_inactive);

#ifndef USE_TIMER_THREAD
	UNUSED(signal_ok);
#endif /* USE_TIMER_THREAD */

	manager = timer->manager;

#ifdef USE_TIMER_THREAD
	/*!
	 * If the manager was timed wait, we may need to signal the
	 * manager to force a wakeup.
	 */
	timedwait = ISC_TF(manager->nscheduled > 0 &&
			   isc_time_seconds(&manager->due) != 0);
#endif

	/*
	 * Compute the new due time.
	 */
	if (timer->type != isc_timertype_once) {
		result = isc_time_add(now, &timer->interval, &due);
		if (result != ISC_R_SUCCESS)
			return (result);
		if (timer->type == isc_timertype_limited &&
		    isc_time_compare(&timer->expires, &due) < 0)
			due = timer->expires;
	} else {
		if (isc_time_isepoch(&timer->idle))
			due = timer->expires;
		else if (isc_time_isepoch(&timer->expires))
			due = timer->idle;
		else if (isc_time_compare(&timer->idle, &timer->expires) < 0)
			due = timer->idle;
		else
			due = timer->expires;
	}

	/*
	 * Schedule the timer.
	 */

	if (timer->index > 0) {
		/*
		 * Already scheduled.
		 */
		cmp = isc_time_compare(&due, &timer->due);
		timer->due = due;
		switch (cmp) {
		case -1:
			isc_heap_increased(manager->heap, timer->index);
			break;
		case 1:
			isc_heap_decreased(manager->heap, timer->index);
			break;
		case 0:
			/* Nothing to do. */
			break;
		}
	} else {
		timer->due = due;
		result = isc_heap_insert(manager->heap, timer);
		if (result != ISC_R_SUCCESS) {
			INSIST(result == ISC_R_NOMEMORY);
			return (ISC_R_NOMEMORY);
		}
		manager->nscheduled++;
	}

	XTRACETIMER(isc_msgcat_get(isc_msgcat, ISC_MSGSET_TIMER,
				   ISC_MSG_SCHEDULE, "schedule"), timer, due);

	/*
	 * If this timer is at the head of the queue, we need to ensure
	 * that we won't miss it if it has a more recent due time than
	 * the current "next" timer.  We do this either by waking up the
	 * run thread, or explicitly setting the value in the manager.
	 */
#ifdef USE_TIMER_THREAD

	/*
	 * This is a temporary (probably) hack to fix a bug on tru64 5.1
	 * and 5.1a.  Sometimes, pthread_cond_timedwait() doesn't actually
	 * return when the time expires, so here, we check to see if
	 * we're 15 seconds or more behind, and if we are, we signal
	 * the dispatcher.  This isn't such a bad idea as a general purpose
	 * watchdog, so perhaps we should just leave it in here.
	 */
	if (signal_ok && timedwait) {
		isc_interval_t fifteen;
		isc_time_t then;

		isc_interval_set(&fifteen, 15, 0);
		result = isc_time_add(&manager->due, &fifteen, &then);

		if (result == ISC_R_SUCCESS &&
		    isc_time_compare(&then, now) < 0) {
			SIGNAL(&manager->wakeup);
			signal_ok = ISC_FALSE;
			isc_log_write(isc_lctx, ISC_LOGCATEGORY_GENERAL,
				      ISC_LOGMODULE_TIMER, ISC_LOG_WARNING,
				      "*** POKED TIMER ***");
		}
	}

	if (timer->index == 1 && signal_ok) {
		XTRACE(isc_msgcat_get(isc_msgcat, ISC_MSGSET_TIMER,
				      ISC_MSG_SIGNALSCHED,
				      "signal (schedule)"));
		SIGNAL(&manager->wakeup);
	}
#else /* USE_TIMER_THREAD */
	if (timer->index == 1 &&
	    isc_time_compare(&timer->due, &manager->due) < 0)
		manager->due = timer->due;
#endif /* USE_TIMER_THREAD */

	return (ISC_R_SUCCESS);
}