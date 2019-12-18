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
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_CONSOLE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_DEBUG_BUFFER_SIZE ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/  (*) ()) ; 
 int ACPI_LV_TABLES ; 
 int /*<<< orphan*/  ACPI_LV_VERBOSITY2 ; 
 int ACPI_NORMAL_DEFAULT ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ AML_ROOT_PREFIX ; 
 int DEBUGGER_MULTI_THREADED ; 
 void* FALSE ; 
 int /*<<< orphan*/  OSL_DEBUGGER_MAIN_THREAD ; 
 void* TRUE ; 
 int /*<<< orphan*/  acpi_db_execute_thread ; 
 int /*<<< orphan*/ * acpi_gbl_db_buffer ; 
 int acpi_gbl_db_console_debug_level ; 
 int /*<<< orphan*/  acpi_gbl_db_debug_level ; 
 int /*<<< orphan*/ * acpi_gbl_db_filename ; 
 void* acpi_gbl_db_opt_no_ini_methods ; 
 int /*<<< orphan*/  acpi_gbl_db_output_flags ; 
 void* acpi_gbl_db_output_to_file ; 
 scalar_t__* acpi_gbl_db_scope_buf ; 
 int /*<<< orphan*/  acpi_gbl_db_scope_node ; 
 void* acpi_gbl_db_terminate_loop ; 
 int /*<<< orphan*/  acpi_gbl_db_thread_id ; 
 void* acpi_gbl_db_threads_terminated ; 
 int acpi_gbl_debugger_configuration ; 
 int /*<<< orphan*/  acpi_gbl_root_node ; 
 int /*<<< orphan*/ * acpi_os_allocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_execute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_os_get_thread_id () ; 
 int /*<<< orphan*/  acpi_os_initialize_debugger () ; 
 int /*<<< orphan*/  acpi_os_printf (char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_initialize_debugger(void)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_initialize_debugger);

	/* Init globals */

	acpi_gbl_db_buffer = NULL;
	acpi_gbl_db_filename = NULL;
	acpi_gbl_db_output_to_file = FALSE;

	acpi_gbl_db_debug_level = ACPI_LV_VERBOSITY2;
	acpi_gbl_db_console_debug_level = ACPI_NORMAL_DEFAULT | ACPI_LV_TABLES;
	acpi_gbl_db_output_flags = ACPI_DB_CONSOLE_OUTPUT;

	acpi_gbl_db_opt_no_ini_methods = FALSE;

	acpi_gbl_db_buffer = acpi_os_allocate(ACPI_DEBUG_BUFFER_SIZE);
	if (!acpi_gbl_db_buffer) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}
	memset(acpi_gbl_db_buffer, 0, ACPI_DEBUG_BUFFER_SIZE);

	/* Initial scope is the root */

	acpi_gbl_db_scope_buf[0] = AML_ROOT_PREFIX;
	acpi_gbl_db_scope_buf[1] = 0;
	acpi_gbl_db_scope_node = acpi_gbl_root_node;

	/* Initialize user commands loop */

	acpi_gbl_db_terminate_loop = FALSE;

	/*
	 * If configured for multi-thread support, the debug executor runs in
	 * a separate thread so that the front end can be in another address
	 * space, environment, or even another machine.
	 */
	if (acpi_gbl_debugger_configuration & DEBUGGER_MULTI_THREADED) {

		/* These were created with one unit, grab it */

		status = acpi_os_initialize_debugger();
		if (ACPI_FAILURE(status)) {
			acpi_os_printf("Could not get debugger mutex\n");
			return_ACPI_STATUS(status);
		}

		/* Create the debug execution thread to execute commands */

		acpi_gbl_db_threads_terminated = FALSE;
		status = acpi_os_execute(OSL_DEBUGGER_MAIN_THREAD,
					 acpi_db_execute_thread, NULL);
		if (ACPI_FAILURE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"Could not start debugger thread"));
			acpi_gbl_db_threads_terminated = TRUE;
			return_ACPI_STATUS(status);
		}
	} else {
		acpi_gbl_db_thread_id = acpi_os_get_thread_id();
	}

	return_ACPI_STATUS(AE_OK);
}