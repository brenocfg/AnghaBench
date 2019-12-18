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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_walk_state {int dummy; } ;
struct acpi_namespace_node {int /*<<< orphan*/ * object; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_DESC_TYPE_OPERAND ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ds_method_data_get_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_walk_state*,struct acpi_namespace_node**) ; 
 union acpi_operand_object* acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ds_method_data_delete_value ; 
 int /*<<< orphan*/  return_VOID ; 

__attribute__((used)) static void
acpi_ds_method_data_delete_value(u8 type,
				 u32 index, struct acpi_walk_state *walk_state)
{
	acpi_status status;
	struct acpi_namespace_node *node;
	union acpi_operand_object *object;

	ACPI_FUNCTION_TRACE(ds_method_data_delete_value);

	/* Get the namespace node for the arg/local */

	status = acpi_ds_method_data_get_node(type, index, walk_state, &node);
	if (ACPI_FAILURE(status)) {
		return_VOID;
	}

	/* Get the associated object */

	object = acpi_ns_get_attached_object(node);

	/*
	 * Undefine the Arg or Local by setting its descriptor
	 * pointer to NULL. Locals/Args can contain both
	 * ACPI_OPERAND_OBJECTS and ACPI_NAMESPACE_NODEs
	 */
	node->object = NULL;

	if ((object) &&
	    (ACPI_GET_DESCRIPTOR_TYPE(object) == ACPI_DESC_TYPE_OPERAND)) {
		/*
		 * There is a valid object.
		 * Decrement the reference count by one to balance the
		 * increment when the object was stored.
		 */
		acpi_ut_remove_reference(object);
	}

	return_VOID;
}