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
typedef  scalar_t__ isc_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCurrentThread () ; 
 int /*<<< orphan*/  ISC_LIST_INIT (int /*<<< orphan*/ ) ; 
 scalar_t__ ISC_R_SUCCESS ; 
 size_t RELOAD_EVENT ; 
 size_t SHUTDOWN_EVENT ; 
 int /*<<< orphan*/ * hEvents ; 
 scalar_t__ isc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  main_thread ; 
 int /*<<< orphan*/  on_run ; 

isc_result_t
isc__app_start(void) {
	isc_result_t result;

	/*
	 * Start an ISC library application.
	 */

	main_thread = GetCurrentThread();

	result = isc_mutex_init(&lock);
	if (result != ISC_R_SUCCESS)
		return (result);

	/* Create the reload event in a non-signaled state */
	hEvents[RELOAD_EVENT] = CreateEvent(NULL, FALSE, FALSE, NULL);

	/* Create the shutdown event in a non-signaled state */
	hEvents[SHUTDOWN_EVENT] = CreateEvent(NULL, FALSE, FALSE, NULL);

	ISC_LIST_INIT(on_run);
	return (ISC_R_SUCCESS);
}