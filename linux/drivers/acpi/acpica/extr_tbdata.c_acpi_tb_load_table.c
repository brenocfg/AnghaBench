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
struct acpi_table_header {int dummy; } ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_owner_id ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TABLE_EVENT_LOAD ; 
 int /*<<< orphan*/  acpi_ev_update_gpes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_table_by_index (int /*<<< orphan*/ ,struct acpi_table_header**) ; 
 int /*<<< orphan*/  acpi_ns_load_table (int /*<<< orphan*/ ,struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_tb_get_owner_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_tb_notify_table (int /*<<< orphan*/ ,struct acpi_table_header*) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_load_table ; 

acpi_status
acpi_tb_load_table(u32 table_index, struct acpi_namespace_node *parent_node)
{
	struct acpi_table_header *table;
	acpi_status status;
	acpi_owner_id owner_id;

	ACPI_FUNCTION_TRACE(tb_load_table);

	/*
	 * Note: Now table is "INSTALLED", it must be validated before
	 * using.
	 */
	status = acpi_get_table_by_index(table_index, &table);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	status = acpi_ns_load_table(table_index, parent_node);

	/*
	 * Update GPEs for any new _Lxx/_Exx methods. Ignore errors. The host is
	 * responsible for discovering any new wake GPEs by running _PRW methods
	 * that may have been loaded by this table.
	 */
	status = acpi_tb_get_owner_id(table_index, &owner_id);
	if (ACPI_SUCCESS(status)) {
		acpi_ev_update_gpes(owner_id);
	}

	/* Invoke table handler */

	acpi_tb_notify_table(ACPI_TABLE_EVENT_LOAD, table);
	return_ACPI_STATUS(status);
}