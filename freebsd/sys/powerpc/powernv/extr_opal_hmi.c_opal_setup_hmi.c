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

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPAL_CHECK_TOKEN ; 
 int /*<<< orphan*/  OPAL_HANDLE_HMI ; 
 int /*<<< orphan*/  OPAL_HANDLE_HMI2 ; 
 int /*<<< orphan*/  OPAL_HMI_EVT ; 
 scalar_t__ OPAL_TOKEN_PRESENT ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  hmi_handler ; 
 scalar_t__ opal_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ opal_check () ; 
 int /*<<< orphan*/  opal_hmi_event_handler ; 
 int /*<<< orphan*/  opal_hmi_handler ; 
 int /*<<< orphan*/  opal_hmi_handler2 ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
opal_setup_hmi(void *data)
{
	/* This only works for OPAL, so first make sure we have it. */
	if (opal_check() != 0)
		return;

	if (opal_call(OPAL_CHECK_TOKEN, OPAL_HANDLE_HMI2) == OPAL_TOKEN_PRESENT)
		hmi_handler = opal_hmi_handler2;
	else if (opal_call(OPAL_CHECK_TOKEN, OPAL_HANDLE_HMI) == OPAL_TOKEN_PRESENT)
		hmi_handler = opal_hmi_handler;
	else {
		printf("Warning: No OPAL HMI handler found.\n");
		return;
	}

	EVENTHANDLER_REGISTER(OPAL_HMI_EVT, opal_hmi_event_handler, NULL,
	    EVENTHANDLER_PRI_ANY);

	if (bootverbose)
		printf("Installed OPAL HMI handler.\n");
}