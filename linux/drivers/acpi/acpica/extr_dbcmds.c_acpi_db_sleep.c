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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/  (*) (char*)) ; 
 scalar_t__ ACPI_S_STATES_MAX ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_db_do_one_sleep_state (scalar_t__) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

acpi_status acpi_db_sleep(char *object_arg)
{
	u8 sleep_state;
	u32 i;

	ACPI_FUNCTION_TRACE(acpi_db_sleep);

	/* Null input (no arguments) means to invoke all sleep states */

	if (!object_arg) {
		acpi_os_printf("Invoking all possible sleep states, 0-%d\n",
			       ACPI_S_STATES_MAX);

		for (i = 0; i <= ACPI_S_STATES_MAX; i++) {
			acpi_db_do_one_sleep_state((u8)i);
		}

		return_ACPI_STATUS(AE_OK);
	}

	/* Convert argument to binary and invoke the sleep state */

	sleep_state = (u8)strtoul(object_arg, NULL, 0);
	acpi_db_do_one_sleep_state(sleep_state);
	return_ACPI_STATUS(AE_OK);
}