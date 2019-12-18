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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/ * ACPI_ALLOCATE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_EXECUTER ; 
 int /*<<< orphan*/  ACPI_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACPI_LV_TRACE_POINT ; 
 int /*<<< orphan*/  ACPI_TRACE_ENABLED ; 
 int /*<<< orphan*/  ACPI_TRACE_ONESHOT ; 
 int /*<<< orphan*/  ACPI_TRACE_OPCODE ; 
 int /*<<< orphan*/ * acpi_db_trace_method_name ; 
 int /*<<< orphan*/  acpi_dbg_layer ; 
 int /*<<< orphan*/  acpi_debug_trace (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_gbl_db_console_debug_level ; 
 int /*<<< orphan*/  acpi_os_printf (char*,char*) ; 
 int /*<<< orphan*/  acpi_ut_strupr (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strlen (char*) ; 

void acpi_db_trace(char *enable_arg, char *method_arg, char *once_arg)
{
	u32 debug_level = 0;
	u32 debug_layer = 0;
	u32 flags = 0;

	acpi_ut_strupr(enable_arg);
	acpi_ut_strupr(once_arg);

	if (method_arg) {
		if (acpi_db_trace_method_name) {
			ACPI_FREE(acpi_db_trace_method_name);
			acpi_db_trace_method_name = NULL;
		}

		acpi_db_trace_method_name =
		    ACPI_ALLOCATE(strlen(method_arg) + 1);
		if (!acpi_db_trace_method_name) {
			acpi_os_printf("Failed to allocate method name (%s)\n",
				       method_arg);
			return;
		}

		strcpy(acpi_db_trace_method_name, method_arg);
	}

	if (!strcmp(enable_arg, "ENABLE") ||
	    !strcmp(enable_arg, "METHOD") || !strcmp(enable_arg, "OPCODE")) {
		if (!strcmp(enable_arg, "ENABLE")) {

			/* Inherit current console settings */

			debug_level = acpi_gbl_db_console_debug_level;
			debug_layer = acpi_dbg_layer;
		} else {
			/* Restrict console output to trace points only */

			debug_level = ACPI_LV_TRACE_POINT;
			debug_layer = ACPI_EXECUTER;
		}

		flags = ACPI_TRACE_ENABLED;

		if (!strcmp(enable_arg, "OPCODE")) {
			flags |= ACPI_TRACE_OPCODE;
		}

		if (once_arg && !strcmp(once_arg, "ONCE")) {
			flags |= ACPI_TRACE_ONESHOT;
		}
	}

	(void)acpi_debug_trace(acpi_db_trace_method_name,
			       debug_level, debug_layer, flags);
}