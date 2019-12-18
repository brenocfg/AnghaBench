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
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  acpi_ev_terminate () ; 
 scalar_t__ acpi_gbl_shutdown ; 
 scalar_t__ acpi_gbl_startup_flags ; 
 int /*<<< orphan*/  acpi_ns_terminate () ; 
 int /*<<< orphan*/  acpi_tb_terminate () ; 
 int /*<<< orphan*/  acpi_ut_delete_caches () ; 
 int /*<<< orphan*/  acpi_ut_interface_terminate () ; 
 int /*<<< orphan*/  acpi_ut_terminate () ; 
 int /*<<< orphan*/  return_VOID ; 
 int /*<<< orphan*/  ut_subsystem_shutdown ; 

void acpi_ut_subsystem_shutdown(void)
{
	ACPI_FUNCTION_TRACE(ut_subsystem_shutdown);

	/* Just exit if subsystem is already shutdown */

	if (acpi_gbl_shutdown) {
		ACPI_ERROR((AE_INFO, "ACPI Subsystem is already terminated"));
		return_VOID;
	}

	/* Subsystem appears active, go ahead and shut it down */

	acpi_gbl_shutdown = TRUE;
	acpi_gbl_startup_flags = 0;
	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Shutting down ACPI Subsystem\n"));

#ifndef ACPI_ASL_COMPILER

	/* Close the acpi_event Handling */

	acpi_ev_terminate();

	/* Delete any dynamic _OSI interfaces */

	acpi_ut_interface_terminate();
#endif

	/* Close the Namespace */

	acpi_ns_terminate();

	/* Delete the ACPI tables */

	acpi_tb_terminate();

	/* Close the globals */

	acpi_ut_terminate();

	/* Purge the local caches */

	(void)acpi_ut_delete_caches();
	return_VOID;
}