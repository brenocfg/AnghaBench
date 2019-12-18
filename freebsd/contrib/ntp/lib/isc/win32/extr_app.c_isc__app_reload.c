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
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  scalar_t__ isc_boolean_t ;

/* Variables and functions */
 scalar_t__ ISC_FALSE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 scalar_t__ ISC_TRUE ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 size_t RELOAD_EVENT ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hEvents ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  running ; 
 scalar_t__ shutdown_requested ; 

isc_result_t
isc__app_reload(void) {
	isc_boolean_t want_reload = ISC_TRUE;

	LOCK(&lock);
	REQUIRE(running);

	/*
	 * Don't send the reload signal if we're shutting down.
	 */
	if (shutdown_requested)
		want_reload = ISC_FALSE;

	UNLOCK(&lock);
	if (want_reload)
		SetEvent(hEvents[RELOAD_EVENT]);

	return (ISC_R_SUCCESS);
}