#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_9__ {int /*<<< orphan*/ * handle; } ;
typedef  TYPE_1__ isc_condition_thread_t ;
struct TYPE_10__ {scalar_t__ waiters; int /*<<< orphan*/  threadlist; int /*<<< orphan*/ * events; } ;
typedef  TYPE_2__ isc_condition_t ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEQUEUE (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 TYPE_1__* ISC_LIST_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 size_t LBROADCAST ; 
 size_t LSIGNAL ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  link ; 

isc_result_t
isc_condition_destroy(isc_condition_t *cond) {

	isc_condition_thread_t *next, *threadcond;

	REQUIRE(cond != NULL);
	REQUIRE(cond->waiters == 0);

	(void)CloseHandle(cond->events[LSIGNAL]);

	/*
	 * Delete the threadlist
	 */
	threadcond = ISC_LIST_HEAD(cond->threadlist);

	while (threadcond != NULL) {
		next = ISC_LIST_NEXT(threadcond, link);
		DEQUEUE(cond->threadlist, threadcond, link);
		(void) CloseHandle(threadcond->handle[LBROADCAST]);
		free(threadcond);
		threadcond = next;
	}

	return (ISC_R_SUCCESS);
}