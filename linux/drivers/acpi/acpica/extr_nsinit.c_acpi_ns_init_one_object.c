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
struct TYPE_2__ {int flags; } ;
union acpi_operand_object {TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_namespace_node {int dummy; } ;
struct acpi_init_walk_info {int /*<<< orphan*/  package_init; int /*<<< orphan*/  field_init; int /*<<< orphan*/  package_count; int /*<<< orphan*/  buffer_count; int /*<<< orphan*/  field_count; int /*<<< orphan*/  op_region_count; int /*<<< orphan*/  object_count; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int acpi_object_type ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
#define  ACPI_TYPE_BUFFER 132 
#define  ACPI_TYPE_BUFFER_FIELD 131 
#define  ACPI_TYPE_LOCAL_BANK_FIELD 130 
#define  ACPI_TYPE_PACKAGE 129 
#define  ACPI_TYPE_REGION 128 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_TYPE ; 
 int AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  acpi_ds_get_bank_field_arguments (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ex_enter_interpreter () ; 
 int /*<<< orphan*/  acpi_ex_exit_interpreter () ; 
 union acpi_operand_object* acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 
 int acpi_ns_get_type (scalar_t__) ; 
 int /*<<< orphan*/  acpi_ns_init_one_package (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (int) ; 
 int /*<<< orphan*/  ns_init_one_object ; 

__attribute__((used)) static acpi_status
acpi_ns_init_one_object(acpi_handle obj_handle,
			u32 level, void *context, void **return_value)
{
	acpi_object_type type;
	acpi_status status = AE_OK;
	struct acpi_init_walk_info *info =
	    (struct acpi_init_walk_info *)context;
	struct acpi_namespace_node *node =
	    (struct acpi_namespace_node *)obj_handle;
	union acpi_operand_object *obj_desc;

	ACPI_FUNCTION_NAME(ns_init_one_object);

	info->object_count++;

	/* And even then, we are only interested in a few object types */

	type = acpi_ns_get_type(obj_handle);
	obj_desc = acpi_ns_get_attached_object(node);
	if (!obj_desc) {
		return (AE_OK);
	}

	/* Increment counters for object types we are looking for */

	switch (type) {
	case ACPI_TYPE_REGION:

		info->op_region_count++;
		break;

	case ACPI_TYPE_BUFFER_FIELD:

		info->field_count++;
		break;

	case ACPI_TYPE_LOCAL_BANK_FIELD:

		info->field_count++;
		break;

	case ACPI_TYPE_BUFFER:

		info->buffer_count++;
		break;

	case ACPI_TYPE_PACKAGE:

		info->package_count++;
		break;

	default:

		/* No init required, just exit now */

		return (AE_OK);
	}

	/* If the object is already initialized, nothing else to do */

	if (obj_desc->common.flags & AOPOBJ_DATA_VALID) {
		return (AE_OK);
	}

	/* Must lock the interpreter before executing AML code */

	acpi_ex_enter_interpreter();

	/*
	 * Only initialization of Package objects can be deferred, in order
	 * to support forward references.
	 */
	switch (type) {
	case ACPI_TYPE_LOCAL_BANK_FIELD:

		/* TBD: bank_fields do not require deferred init, remove this code */

		info->field_init++;
		status = acpi_ds_get_bank_field_arguments(obj_desc);
		break;

	case ACPI_TYPE_PACKAGE:

		/* Complete the initialization/resolution of the package object */

		info->package_init++;
		status =
		    acpi_ns_init_one_package(obj_handle, level, NULL, NULL);
		break;

	default:

		/* No other types should get here */

		status = AE_TYPE;
		ACPI_EXCEPTION((AE_INFO, status,
				"Opcode is not deferred [%4.4s] (%s)",
				acpi_ut_get_node_name(node),
				acpi_ut_get_type_name(type)));
		break;
	}

	if (ACPI_FAILURE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Could not execute arguments for [%4.4s] (%s)",
				acpi_ut_get_node_name(node),
				acpi_ut_get_type_name(type)));
	}

	/*
	 * We ignore errors from above, and always return OK, since we don't want
	 * to abort the walk on any single error.
	 */
	acpi_ex_exit_interpreter();
	return (AE_OK);
}