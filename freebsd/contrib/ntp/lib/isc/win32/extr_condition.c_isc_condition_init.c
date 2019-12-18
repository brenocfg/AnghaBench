#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_3__ {int /*<<< orphan*/  threadlist; int /*<<< orphan*/ ** events; scalar_t__ waiters; } ;
typedef  TYPE_1__ isc_condition_t ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ISC_LIST_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  ISC_R_UNEXPECTED ; 
 size_t LSIGNAL ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 

isc_result_t
isc_condition_init(isc_condition_t *cond) {
	HANDLE h;

	REQUIRE(cond != NULL);

	cond->waiters = 0;
	/*
	 * This handle is shared across all threads
	 */
	h = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (h == NULL) {
		/* XXX */
		return (ISC_R_UNEXPECTED);
	}
	cond->events[LSIGNAL] = h;

	/*
	 * The threadlist will hold the actual events needed
	 * for the wait condition
	 */
	ISC_LIST_INIT(cond->threadlist);

	return (ISC_R_SUCCESS);
}