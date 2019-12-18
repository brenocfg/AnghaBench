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
struct acpi_db_method_info {char* name; int flags; scalar_t__* pathname; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_CONSOLE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_DB_DUPLICATE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_DB_REDIRECTABLE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int EX_SINGLE_STEP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_db_prep_namestring (scalar_t__*) ; 
 int /*<<< orphan*/  acpi_db_set_output_destination (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_gbl_cm_single_step ; 
 char* acpi_gbl_db_scope_buf ; 
 int /*<<< orphan*/  acpi_os_printf (char*,scalar_t__*) ; 
 scalar_t__ acpi_ut_safe_strcat (scalar_t__*,int,char*) ; 
 int /*<<< orphan*/  db_execute_setup ; 

__attribute__((used)) static acpi_status acpi_db_execute_setup(struct acpi_db_method_info *info)
{
	acpi_status status;

	ACPI_FUNCTION_NAME(db_execute_setup);

	/* Concatenate the current scope to the supplied name */

	info->pathname[0] = 0;
	if ((info->name[0] != '\\') && (info->name[0] != '/')) {
		if (acpi_ut_safe_strcat(info->pathname, sizeof(info->pathname),
					acpi_gbl_db_scope_buf)) {
			status = AE_BUFFER_OVERFLOW;
			goto error_exit;
		}
	}

	if (acpi_ut_safe_strcat(info->pathname, sizeof(info->pathname),
				info->name)) {
		status = AE_BUFFER_OVERFLOW;
		goto error_exit;
	}

	acpi_db_prep_namestring(info->pathname);

	acpi_db_set_output_destination(ACPI_DB_DUPLICATE_OUTPUT);
	acpi_os_printf("Evaluating %s\n", info->pathname);

	if (info->flags & EX_SINGLE_STEP) {
		acpi_gbl_cm_single_step = TRUE;
		acpi_db_set_output_destination(ACPI_DB_CONSOLE_OUTPUT);
	}

	else {
		/* No single step, allow redirection to a file */

		acpi_db_set_output_destination(ACPI_DB_REDIRECTABLE_OUTPUT);
	}

	return (AE_OK);

error_exit:

	ACPI_EXCEPTION((AE_INFO, status, "During setup for method execution"));
	return (status);
}