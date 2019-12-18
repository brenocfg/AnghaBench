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
 scalar_t__ ACPI_NAMESEG_SIZE ; 
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_db_set_output_destination (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_db_walk_and_match_name ; 
 int /*<<< orphan*/  acpi_os_printf (char*) ; 
 int /*<<< orphan*/  acpi_ut_strupr (char*) ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 

acpi_status acpi_db_find_name_in_namespace(char *name_arg)
{
	char acpi_name[5] = "____";
	char *acpi_name_ptr = acpi_name;

	if (strlen(name_arg) > ACPI_NAMESEG_SIZE) {
		acpi_os_printf("Name must be no longer than 4 characters\n");
		return (AE_OK);
	}

	/* Pad out name with underscores as necessary to create a 4-char name */

	acpi_ut_strupr(name_arg);
	while (*name_arg) {
		*acpi_name_ptr = *name_arg;
		acpi_name_ptr++;
		name_arg++;
	}

	/* Walk the namespace from the root */

	(void)acpi_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
				  ACPI_UINT32_MAX, acpi_db_walk_and_match_name,
				  NULL, acpi_name, NULL);

	acpi_db_set_output_destination(ACPI_DB_CONSOLE_OUTPUT);
	return (AE_OK);
}