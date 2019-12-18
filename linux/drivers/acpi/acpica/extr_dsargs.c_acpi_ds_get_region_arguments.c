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
struct TYPE_4__ {int flags; int /*<<< orphan*/  length; int /*<<< orphan*/  address; int /*<<< orphan*/  space_id; struct acpi_namespace_node* node; } ;
struct TYPE_3__ {int /*<<< orphan*/  aml_start; int /*<<< orphan*/  aml_length; int /*<<< orphan*/  scope_node; } ;
union acpi_operand_object {TYPE_2__ region; TYPE_1__ extra; } ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_EXEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 int /*<<< orphan*/  ACPI_TYPE_REGION ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  acpi_ds_execute_arguments (struct acpi_namespace_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 union acpi_operand_object* acpi_ns_get_secondary_object (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_add_address_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ut_display_init_pathname (int /*<<< orphan*/ ,struct acpi_namespace_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  ds_get_region_arguments ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ds_get_region_arguments(union acpi_operand_object *obj_desc)
{
	struct acpi_namespace_node *node;
	acpi_status status;
	union acpi_operand_object *extra_desc;

	ACPI_FUNCTION_TRACE_PTR(ds_get_region_arguments, obj_desc);

	if (obj_desc->region.flags & AOPOBJ_DATA_VALID) {
		return_ACPI_STATUS(AE_OK);
	}

	extra_desc = acpi_ns_get_secondary_object(obj_desc);
	if (!extra_desc) {
		return_ACPI_STATUS(AE_NOT_EXIST);
	}

	/* Get the Region node */

	node = obj_desc->region.node;

	ACPI_DEBUG_EXEC(acpi_ut_display_init_pathname
			(ACPI_TYPE_REGION, node, NULL));

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "[%4.4s] OpRegion Arg Init at AML %p\n",
			  acpi_ut_get_node_name(node),
			  extra_desc->extra.aml_start));

	/* Execute the argument AML */

	status = acpi_ds_execute_arguments(node, extra_desc->extra.scope_node,
					   extra_desc->extra.aml_length,
					   extra_desc->extra.aml_start);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	status = acpi_ut_add_address_range(obj_desc->region.space_id,
					   obj_desc->region.address,
					   obj_desc->region.length, node);
	return_ACPI_STATUS(status);
}