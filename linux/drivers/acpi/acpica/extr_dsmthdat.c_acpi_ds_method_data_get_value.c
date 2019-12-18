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
typedef  union acpi_operand_object {int dummy; } acpi_operand_object ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_walk_state {int dummy; } ;
struct acpi_namespace_node {union acpi_operand_object* object; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
#define  ACPI_REFCLASS_ARG 129 
#define  ACPI_REFCLASS_LOCAL 128 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_AML_UNINITIALIZED_ARG ; 
 int /*<<< orphan*/  AE_AML_UNINITIALIZED_LOCAL ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ds_method_data_get_node (int,int /*<<< orphan*/ ,struct acpi_walk_state*,struct acpi_namespace_node**) ; 
 scalar_t__ acpi_gbl_enable_interpreter_slack ; 
 int /*<<< orphan*/  acpi_ut_add_reference (union acpi_operand_object*) ; 
 union acpi_operand_object* acpi_ut_create_integer_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds_method_data_get_value ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_method_data_get_value(u8 type,
			      u32 index,
			      struct acpi_walk_state *walk_state,
			      union acpi_operand_object **dest_desc)
{
	acpi_status status;
	struct acpi_namespace_node *node;
	union acpi_operand_object *object;

	ACPI_FUNCTION_TRACE(ds_method_data_get_value);

	/* Validate the object descriptor */

	if (!dest_desc) {
		ACPI_ERROR((AE_INFO, "Null object descriptor pointer"));
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	/* Get the namespace node for the arg/local */

	status = acpi_ds_method_data_get_node(type, index, walk_state, &node);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Get the object from the node */

	object = node->object;

	/* Examine the returned object, it must be valid. */

	if (!object) {
		/*
		 * Index points to uninitialized object.
		 * This means that either 1) The expected argument was
		 * not passed to the method, or 2) A local variable
		 * was referenced by the method (via the ASL)
		 * before it was initialized. Either case is an error.
		 */

		/* If slack enabled, init the local_x/arg_x to an Integer of value zero */

		if (acpi_gbl_enable_interpreter_slack) {
			object = acpi_ut_create_integer_object((u64) 0);
			if (!object) {
				return_ACPI_STATUS(AE_NO_MEMORY);
			}

			node->object = object;
		}

		/* Otherwise, return the error */

		else
			switch (type) {
			case ACPI_REFCLASS_ARG:

				ACPI_ERROR((AE_INFO,
					    "Uninitialized Arg[%u] at node %p",
					    index, node));

				return_ACPI_STATUS(AE_AML_UNINITIALIZED_ARG);

			case ACPI_REFCLASS_LOCAL:
				/*
				 * No error message for this case, will be trapped again later to
				 * detect and ignore cases of Store(local_x,local_x)
				 */
				return_ACPI_STATUS(AE_AML_UNINITIALIZED_LOCAL);

			default:

				ACPI_ERROR((AE_INFO,
					    "Not a Arg/Local opcode: 0x%X",
					    type));
				return_ACPI_STATUS(AE_AML_INTERNAL);
			}
	}

	/*
	 * The Index points to an initialized and valid object.
	 * Return an additional reference to the object
	 */
	*dest_desc = object;
	acpi_ut_add_reference(object);

	return_ACPI_STATUS(AE_OK);
}