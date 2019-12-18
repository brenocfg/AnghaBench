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
struct acpi_namespace_node {int dummy; } ;
struct acpi_buffer {scalar_t__ pointer; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COPY_NAMESEG (scalar_t__,char const*) ; 
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ACPI_NAMESEG_SIZE ; 
 int /*<<< orphan*/  ACPI_PATH_SEGMENT_LENGTH ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 struct acpi_namespace_node* acpi_ns_validate_handle (int /*<<< orphan*/ ) ; 
 char* acpi_ut_get_node_name (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ut_initialize_buffer (struct acpi_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_handle_to_name ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ns_handle_to_name(acpi_handle target_handle, struct acpi_buffer *buffer)
{
	acpi_status status;
	struct acpi_namespace_node *node;
	const char *node_name;

	ACPI_FUNCTION_TRACE_PTR(ns_handle_to_name, target_handle);

	node = acpi_ns_validate_handle(target_handle);
	if (!node) {
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	/* Validate/Allocate/Clear caller buffer */

	status = acpi_ut_initialize_buffer(buffer, ACPI_PATH_SEGMENT_LENGTH);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Just copy the ACPI name from the Node and zero terminate it */

	node_name = acpi_ut_get_node_name(node);
	ACPI_COPY_NAMESEG(buffer->pointer, node_name);
	((char *)buffer->pointer)[ACPI_NAMESEG_SIZE] = 0;

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "%4.4s\n", (char *)buffer->pointer));
	return_ACPI_STATUS(AE_OK);
}