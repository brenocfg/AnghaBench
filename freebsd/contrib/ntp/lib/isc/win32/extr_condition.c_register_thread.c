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
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_8__ {unsigned long th; int /*<<< orphan*/ ** handle; } ;
typedef  TYPE_1__ isc_condition_thread_t ;
struct TYPE_9__ {int /*<<< orphan*/  threadlist; int /*<<< orphan*/ ** events; } ;
typedef  TYPE_2__ isc_condition_t ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ISC_LIST_APPEND (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_R_NOMEMORY ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  ISC_R_UNEXPECTED ; 
 size_t LBROADCAST ; 
 size_t LSIGNAL ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  link ; 
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static isc_result_t
register_thread(unsigned long thrd, isc_condition_t *gblcond,
		isc_condition_thread_t **localcond)
{
	HANDLE hc;
	isc_condition_thread_t *newthread;

	REQUIRE(localcond != NULL && *localcond == NULL);

	newthread = malloc(sizeof(isc_condition_thread_t));
	if (newthread == NULL)
		return (ISC_R_NOMEMORY);

	/*
	 * Create the thread-specific handle
	 */
	hc = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hc == NULL) {
		free(newthread);
		return (ISC_R_UNEXPECTED);
	}

	/*
	 * Add the thread ID and handles to list of threads for broadcast
	 */
	newthread->handle[LSIGNAL] = gblcond->events[LSIGNAL];
	newthread->handle[LBROADCAST] = hc;
	newthread->th = thrd;

	/*
	 * The thread is holding the manager lock so this is safe
	 */
	ISC_LIST_APPEND(gblcond->threadlist, newthread, link);
	*localcond = newthread;
	return (ISC_R_SUCCESS);
}