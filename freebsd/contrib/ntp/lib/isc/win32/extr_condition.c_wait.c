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
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  isc_mutex_t ;
struct TYPE_6__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ isc_condition_thread_t ;
struct TYPE_7__ {int /*<<< orphan*/  waiters; } ;
typedef  TYPE_2__ isc_condition_t ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ISC_R_SUCCESS ; 
 scalar_t__ ISC_R_TIMEDOUT ; 
 scalar_t__ ISC_R_UNEXPECTED ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ WAIT_FAILED ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForMultipleObjects (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ find_thread_condition (int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__**) ; 
 int /*<<< orphan*/  isc_thread_self () ; 

__attribute__((used)) static isc_result_t
wait(isc_condition_t *cond, isc_mutex_t *mutex, DWORD milliseconds) {
	DWORD result;
	isc_result_t tresult;
	isc_condition_thread_t *threadcond = NULL;

	/*
	 * Get the thread events needed for the wait
	 */
	tresult = find_thread_condition(isc_thread_self(), cond, &threadcond);
	if (tresult !=  ISC_R_SUCCESS)
		return (tresult);

	cond->waiters++;
	LeaveCriticalSection(mutex);
	result = WaitForMultipleObjects(2, threadcond->handle, FALSE,
					milliseconds);
	EnterCriticalSection(mutex);
	cond->waiters--;
	if (result == WAIT_FAILED) {
		/* XXX */
		return (ISC_R_UNEXPECTED);
	}
	if (result == WAIT_TIMEOUT)
		return (ISC_R_TIMEDOUT);

	return (ISC_R_SUCCESS);
}