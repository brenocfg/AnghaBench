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
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_PARSE ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_GET_FUNCTION_NAME ; 
 int /*<<< orphan*/  acpi_ns_execute_table (int /*<<< orphan*/ ,struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  ns_parse_table ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ns_parse_table(u32 table_index, struct acpi_namespace_node *start_node)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(ns_parse_table);

	/*
	 * Executes the AML table as one large control method.
	 * The point of this is to execute any module-level code in-place
	 * as the table is parsed. Some AML code depends on this behavior.
	 *
	 * Note: This causes the table to only have a single-pass parse.
	 * However, this is compatible with other ACPI implementations.
	 */
	ACPI_DEBUG_PRINT_RAW((ACPI_DB_PARSE,
			      "%s: **** Start table execution pass\n",
			      ACPI_GET_FUNCTION_NAME));

	status = acpi_ns_execute_table(table_index, start_node);

	return_ACPI_STATUS(status);
}