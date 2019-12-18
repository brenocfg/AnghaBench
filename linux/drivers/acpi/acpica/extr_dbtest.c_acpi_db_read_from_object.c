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
union acpi_object {int type; TYPE_1__ reference; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_namespace_node {int /*<<< orphan*/  type; } ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int acpi_object_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 int /*<<< orphan*/  ACPI_CAST_PTR (int /*<<< orphan*/ ,struct acpi_namespace_node*) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
#define  ACPI_TYPE_BUFFER 131 
#define  ACPI_TYPE_INTEGER 130 
 int ACPI_TYPE_LOCAL_REFERENCE ; 
#define  ACPI_TYPE_PACKAGE 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AE_TYPE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_object_list*,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_format_exception (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_gbl_method_executing ; 
 int /*<<< orphan*/  acpi_handle ; 
 int /*<<< orphan*/  acpi_os_free (scalar_t__) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (int) ; 
 int /*<<< orphan*/  read_handle ; 

__attribute__((used)) static acpi_status
acpi_db_read_from_object(struct acpi_namespace_node *node,
			 acpi_object_type expected_type,
			 union acpi_object **value)
{
	union acpi_object *ret_value;
	struct acpi_object_list param_objects;
	union acpi_object params[2];
	struct acpi_buffer return_obj;
	acpi_status status;

	params[0].type = ACPI_TYPE_LOCAL_REFERENCE;
	params[0].reference.actual_type = node->type;
	params[0].reference.handle = ACPI_CAST_PTR(acpi_handle, node);

	param_objects.count = 1;
	param_objects.pointer = params;

	return_obj.length = ACPI_ALLOCATE_BUFFER;

	acpi_gbl_method_executing = TRUE;
	status = acpi_evaluate_object(read_handle, NULL,
				      &param_objects, &return_obj);

	acpi_gbl_method_executing = FALSE;
	if (ACPI_FAILURE(status)) {
		acpi_os_printf("Could not read from object, %s",
			       acpi_format_exception(status));
		return (status);
	}

	ret_value = (union acpi_object *)return_obj.pointer;

	switch (ret_value->type) {
	case ACPI_TYPE_INTEGER:
	case ACPI_TYPE_BUFFER:
	case ACPI_TYPE_STRING:
	case ACPI_TYPE_PACKAGE:
		/*
		 * Did we receive the type we wanted? Most important for the
		 * Integer/Buffer case (when a field is larger than an Integer,
		 * it should return a Buffer).
		 */
		if (ret_value->type != expected_type) {
			acpi_os_printf
			    (" Type mismatch: Expected %s, Received %s",
			     acpi_ut_get_type_name(expected_type),
			     acpi_ut_get_type_name(ret_value->type));

			acpi_os_free(return_obj.pointer);
			return (AE_TYPE);
		}

		*value = ret_value;
		break;

	default:

		acpi_os_printf(" Unsupported return object type, %s",
			       acpi_ut_get_type_name(ret_value->type));

		acpi_os_free(return_obj.pointer);
		return (AE_TYPE);
	}

	return (status);
}