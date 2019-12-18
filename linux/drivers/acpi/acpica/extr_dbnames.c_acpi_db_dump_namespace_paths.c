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
 int /*<<< orphan*/  ACPI_DB_CONSOLE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_DB_DUPLICATE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_DB_REDIRECTABLE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_DISPLAY_SUMMARY ; 
 int /*<<< orphan*/  ACPI_OWNER_ID_MAX ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  acpi_db_set_output_destination (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_gbl_root_node ; 
 int /*<<< orphan*/  acpi_ns_dump_object_paths (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_printf (char*) ; 

void acpi_db_dump_namespace_paths(void)
{

	acpi_db_set_output_destination(ACPI_DB_DUPLICATE_OUTPUT);
	acpi_os_printf("ACPI Namespace (from root):\n");

	/* Display the entire namespace */

	acpi_db_set_output_destination(ACPI_DB_REDIRECTABLE_OUTPUT);
	acpi_ns_dump_object_paths(ACPI_TYPE_ANY, ACPI_DISPLAY_SUMMARY,
				  ACPI_UINT32_MAX, ACPI_OWNER_ID_MAX,
				  acpi_gbl_root_node);

	acpi_db_set_output_destination(ACPI_DB_CONSOLE_OUTPUT);
}