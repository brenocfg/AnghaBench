#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_4__ {TYPE_1__* tables; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_ALREADY_EXISTS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_ds_initialize_objects (size_t,struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ex_enter_interpreter () ; 
 int /*<<< orphan*/  acpi_ex_exit_interpreter () ; 
 TYPE_2__ acpi_gbl_root_table_list ; 
 int /*<<< orphan*/  acpi_ns_delete_namespace_by_owner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ns_parse_table (size_t,struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_tb_allocate_owner_id (size_t) ; 
 scalar_t__ acpi_tb_is_table_loaded (size_t) ; 
 int /*<<< orphan*/  acpi_tb_release_owner_id (size_t) ; 
 int /*<<< orphan*/  acpi_tb_set_table_loaded_flag (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_load_table ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ns_load_table(u32 table_index, struct acpi_namespace_node *node)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(ns_load_table);

	/* If table already loaded into namespace, just return */

	if (acpi_tb_is_table_loaded(table_index)) {
		status = AE_ALREADY_EXISTS;
		goto unlock;
	}

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "**** Loading table into namespace ****\n"));

	status = acpi_tb_allocate_owner_id(table_index);
	if (ACPI_FAILURE(status)) {
		goto unlock;
	}

	/*
	 * Parse the table and load the namespace with all named
	 * objects found within. Control methods are NOT parsed
	 * at this time. In fact, the control methods cannot be
	 * parsed until the entire namespace is loaded, because
	 * if a control method makes a forward reference (call)
	 * to another control method, we can't continue parsing
	 * because we don't know how many arguments to parse next!
	 */
	status = acpi_ns_parse_table(table_index, node);
	if (ACPI_SUCCESS(status)) {
		acpi_tb_set_table_loaded_flag(table_index, TRUE);
	} else {
		/*
		 * On error, delete any namespace objects created by this table.
		 * We cannot initialize these objects, so delete them. There are
		 * a couple of especially bad cases:
		 * AE_ALREADY_EXISTS - namespace collision.
		 * AE_NOT_FOUND - the target of a Scope operator does not
		 * exist. This target of Scope must already exist in the
		 * namespace, as per the ACPI specification.
		 */
		acpi_ns_delete_namespace_by_owner(acpi_gbl_root_table_list.
						  tables[table_index].owner_id);

		acpi_tb_release_owner_id(table_index);
		return_ACPI_STATUS(status);
	}

unlock:
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/*
	 * Now we can parse the control methods. We always parse
	 * them here for a sanity check, and if configured for
	 * just-in-time parsing, we delete the control method
	 * parse trees.
	 */
	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "**** Begin Table Object Initialization\n"));

	acpi_ex_enter_interpreter();
	status = acpi_ds_initialize_objects(table_index, node);
	acpi_ex_exit_interpreter();

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "**** Completed Table Object Initialization\n"));

	return_ACPI_STATUS(status);
}