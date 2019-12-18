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
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_7__ {int /*<<< orphan*/ * handle; } ;
typedef  TYPE_1__ isc_condition_thread_t ;
struct TYPE_8__ {int /*<<< orphan*/  threadlist; } ;
typedef  TYPE_2__ isc_condition_t ;
typedef  scalar_t__ isc_boolean_t ;

/* Variables and functions */
 scalar_t__ ISC_FALSE ; 
 TYPE_1__* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 TYPE_1__* ISC_LIST_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  ISC_R_UNEXPECTED ; 
 scalar_t__ ISC_TRUE ; 
 size_t LBROADCAST ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 

isc_result_t
isc_condition_broadcast(isc_condition_t *cond) {

	isc_condition_thread_t *threadcond;
	isc_boolean_t failed = ISC_FALSE;

	/*
	 * Unlike pthreads, the caller MUST hold the lock associated with
	 * the condition variable when calling us.
	 */
	REQUIRE(cond != NULL);

	/*
	 * Notify every thread registered for this
	 */
	for (threadcond = ISC_LIST_HEAD(cond->threadlist);
	     threadcond != NULL;
	     threadcond = ISC_LIST_NEXT(threadcond, link)) {

		if (!SetEvent(threadcond->handle[LBROADCAST]))
			failed = ISC_TRUE;
	}

	if (failed)
		return (ISC_R_UNEXPECTED);

	return (ISC_R_SUCCESS);
}