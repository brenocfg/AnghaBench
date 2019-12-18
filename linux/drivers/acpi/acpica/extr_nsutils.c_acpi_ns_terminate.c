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
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MTX_NAMESPACE ; 
 int /*<<< orphan*/  acpi_gbl_root_node ; 
 int /*<<< orphan*/  acpi_ns_delete_namespace_subtree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ns_delete_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_acquire_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_terminate ; 
 int /*<<< orphan*/  return_VOID ; 

void acpi_ns_terminate(void)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(ns_terminate);

	/*
	 * Free the entire namespace -- all nodes and all objects
	 * attached to the nodes
	 */
	acpi_ns_delete_namespace_subtree(acpi_gbl_root_node);

	/* Delete any objects attached to the root node */

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAILURE(status)) {
		return_VOID;
	}

	acpi_ns_delete_node(acpi_gbl_root_node);
	(void)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);

	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Namespace freed\n"));
	return_VOID;
}