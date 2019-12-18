#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  actual_type; } ;
union acpi_object {TYPE_1__ reference; int /*<<< orphan*/  type; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_namespace_node {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CAST_PTR (int /*<<< orphan*/ ,struct acpi_namespace_node*) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_REFERENCE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_object_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_format_exception (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_gbl_method_executing ; 
 int /*<<< orphan*/  acpi_handle ; 
 int /*<<< orphan*/  acpi_os_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (union acpi_object*,union acpi_object*,int) ; 
 int /*<<< orphan*/  write_handle ; 

__attribute__((used)) static acpi_status
acpi_db_write_to_object(struct acpi_namespace_node *node,
			union acpi_object *value)
{
	struct acpi_object_list param_objects;
	union acpi_object params[2];
	acpi_status status;

	params[0].type = ACPI_TYPE_LOCAL_REFERENCE;
	params[0].reference.actual_type = node->type;
	params[0].reference.handle = ACPI_CAST_PTR(acpi_handle, node);

	/* Copy the incoming user parameter */

	memcpy(&params[1], value, sizeof(union acpi_object));

	param_objects.count = 2;
	param_objects.pointer = params;

	acpi_gbl_method_executing = TRUE;
	status = acpi_evaluate_object(write_handle, NULL, &param_objects, NULL);
	acpi_gbl_method_executing = FALSE;

	if (ACPI_FAILURE(status)) {
		acpi_os_printf("Could not write to object, %s",
			       acpi_format_exception(status));
	}

	return (status);
}