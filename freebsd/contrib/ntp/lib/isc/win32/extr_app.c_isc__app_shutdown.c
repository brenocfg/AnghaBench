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
typedef  void* isc_boolean_t ;

/* Variables and functions */
 void* ISC_FALSE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 void* ISC_TRUE ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 size_t SHUTDOWN_EVENT ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hEvents ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  running ; 
 void* shutdown_requested ; 

isc_result_t
isc__app_shutdown(void) {
	isc_boolean_t want_kill = ISC_TRUE;

	LOCK(&lock);
	REQUIRE(running);

	if (shutdown_requested)
		want_kill = ISC_FALSE;		/* We're only signaling once */
	else
		shutdown_requested = ISC_TRUE;

	UNLOCK(&lock);
	if (want_kill)
		SetEvent(hEvents[SHUTDOWN_EVENT]);

	return (ISC_R_SUCCESS);
}