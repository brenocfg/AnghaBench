#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_10__ {unsigned long th; } ;
typedef  TYPE_1__ isc_condition_thread_t ;
struct TYPE_11__ {int /*<<< orphan*/  threadlist; } ;
typedef  TYPE_2__ isc_condition_t ;

/* Variables and functions */
 TYPE_1__* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 TYPE_1__* ISC_LIST_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  register_thread (unsigned long,TYPE_2__*,TYPE_1__**) ; 

__attribute__((used)) static isc_result_t
find_thread_condition(unsigned long thrd, isc_condition_t *cond,
		      isc_condition_thread_t **threadcondp)
{
	isc_condition_thread_t *threadcond;

	REQUIRE(threadcondp != NULL && *threadcondp == NULL);

	/*
	 * Look for the thread ID.
	 */
	for (threadcond = ISC_LIST_HEAD(cond->threadlist);
	     threadcond != NULL;
	     threadcond = ISC_LIST_NEXT(threadcond, link)) {

		if (threadcond->th == thrd) {
			*threadcondp = threadcond;
			return (ISC_R_SUCCESS);
		}
	}

	/*
	 * Not found, so add it.
	 */
	return (register_thread(thrd, cond, threadcondp));
}