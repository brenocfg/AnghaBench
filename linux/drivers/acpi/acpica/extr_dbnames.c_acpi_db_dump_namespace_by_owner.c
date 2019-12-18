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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ acpi_owner_id ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_CONSOLE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_DB_DUPLICATE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_DB_REDIRECTABLE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_DISPLAY_SUMMARY ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 scalar_t__ ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  acpi_db_set_output_destination (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_gbl_root_node ; 
 int /*<<< orphan*/  acpi_ns_dump_objects (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,scalar_t__) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void acpi_db_dump_namespace_by_owner(char *owner_arg, char *depth_arg)
{
	acpi_handle subtree_entry = acpi_gbl_root_node;
	u32 max_depth = ACPI_UINT32_MAX;
	acpi_owner_id owner_id;

	owner_id = (acpi_owner_id)strtoul(owner_arg, NULL, 0);

	/* Now we can check for the depth argument */

	if (depth_arg) {
		max_depth = strtoul(depth_arg, NULL, 0);
	}

	acpi_db_set_output_destination(ACPI_DB_DUPLICATE_OUTPUT);
	acpi_os_printf("ACPI Namespace by owner %X:\n", owner_id);

	/* Display the subtree */

	acpi_db_set_output_destination(ACPI_DB_REDIRECTABLE_OUTPUT);
	acpi_ns_dump_objects(ACPI_TYPE_ANY, ACPI_DISPLAY_SUMMARY, max_depth,
			     owner_id, subtree_entry);
	acpi_db_set_output_destination(ACPI_DB_CONSOLE_OUTPUT);
}