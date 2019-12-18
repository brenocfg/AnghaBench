#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int /*<<< orphan*/  string; } ;
struct TYPE_8__ {scalar_t__ aml_opcode; struct acpi_namespace_node* node; TYPE_1__ value; } ;
union acpi_parse_object {TYPE_5__ named; TYPE_2__ common; } ;
struct TYPE_12__ {struct acpi_namespace_node* node; } ;
struct TYPE_10__ {int /*<<< orphan*/  aml_length; int /*<<< orphan*/  aml_start; } ;
struct TYPE_9__ {union acpi_operand_object* next_object; } ;
union acpi_operand_object {TYPE_6__ buffer_field; TYPE_4__ extra; TYPE_3__ common; } ;
typedef  int u32 ;
struct acpi_walk_state {int parse_flags; int /*<<< orphan*/  scope_info; scalar_t__ method_node; struct acpi_namespace_node* deferred_node; } ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR_NAMESPACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_IMODE_LOAD_PASS1 ; 
 int ACPI_NS_DONT_OPEN_SCOPE ; 
 int ACPI_NS_ERROR_IF_FOUND ; 
 int ACPI_NS_NO_UPSEARCH ; 
 int ACPI_NS_TEMPORARY ; 
 int ACPI_PARSE_EXECUTE ; 
 int ACPI_PARSE_MODULE_LEVEL ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_TYPE_BUFFER_FIELD ; 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_AML_NO_OPERAND ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ AML_CREATE_FIELD_OP ; 
 int /*<<< orphan*/  acpi_ns_attach_object (struct acpi_namespace_node*,union acpi_operand_object*,int /*<<< orphan*/ ) ; 
 union acpi_operand_object* acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ns_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct acpi_walk_state*,struct acpi_namespace_node**) ; 
 union acpi_parse_object* acpi_ps_get_arg (union acpi_parse_object*,int) ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ds_create_buffer_field ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_create_buffer_field(union acpi_parse_object *op,
			    struct acpi_walk_state *walk_state)
{
	union acpi_parse_object *arg;
	struct acpi_namespace_node *node;
	acpi_status status;
	union acpi_operand_object *obj_desc;
	union acpi_operand_object *second_desc = NULL;
	u32 flags;

	ACPI_FUNCTION_TRACE(ds_create_buffer_field);

	/*
	 * Get the name_string argument (name of the new buffer_field)
	 */
	if (op->common.aml_opcode == AML_CREATE_FIELD_OP) {

		/* For create_field, name is the 4th argument */

		arg = acpi_ps_get_arg(op, 3);
	} else {
		/* For all other create_XXXField operators, name is the 3rd argument */

		arg = acpi_ps_get_arg(op, 2);
	}

	if (!arg) {
		return_ACPI_STATUS(AE_AML_NO_OPERAND);
	}

	if (walk_state->deferred_node) {
		node = walk_state->deferred_node;
		status = AE_OK;
	} else {
		/* Execute flag should always be set when this function is entered */

		if (!(walk_state->parse_flags & ACPI_PARSE_EXECUTE)) {
			ACPI_ERROR((AE_INFO, "Parse execute mode is not set"));
			return_ACPI_STATUS(AE_AML_INTERNAL);
		}

		/* Creating new namespace node, should not already exist */

		flags = ACPI_NS_NO_UPSEARCH | ACPI_NS_DONT_OPEN_SCOPE |
		    ACPI_NS_ERROR_IF_FOUND;

		/*
		 * Mark node temporary if we are executing a normal control
		 * method. (Don't mark if this is a module-level code method)
		 */
		if (walk_state->method_node &&
		    !(walk_state->parse_flags & ACPI_PARSE_MODULE_LEVEL)) {
			flags |= ACPI_NS_TEMPORARY;
		}

		/* Enter the name_string into the namespace */

		status = acpi_ns_lookup(walk_state->scope_info,
					arg->common.value.string, ACPI_TYPE_ANY,
					ACPI_IMODE_LOAD_PASS1, flags,
					walk_state, &node);
		if (ACPI_FAILURE(status)) {
			ACPI_ERROR_NAMESPACE(walk_state->scope_info,
					     arg->common.value.string, status);
			return_ACPI_STATUS(status);
		}
	}

	/*
	 * We could put the returned object (Node) on the object stack for later,
	 * but for now, we will put it in the "op" object that the parser uses,
	 * so we can get it again at the end of this scope.
	 */
	op->common.node = node;

	/*
	 * If there is no object attached to the node, this node was just created
	 * and we need to create the field object. Otherwise, this was a lookup
	 * of an existing node and we don't want to create the field object again.
	 */
	obj_desc = acpi_ns_get_attached_object(node);
	if (obj_desc) {
		return_ACPI_STATUS(AE_OK);
	}

	/*
	 * The Field definition is not fully parsed at this time.
	 * (We must save the address of the AML for the buffer and index operands)
	 */

	/* Create the buffer field object */

	obj_desc = acpi_ut_create_internal_object(ACPI_TYPE_BUFFER_FIELD);
	if (!obj_desc) {
		status = AE_NO_MEMORY;
		goto cleanup;
	}

	/*
	 * Remember location in AML stream of the field unit opcode and operands
	 * -- since the buffer and index operands must be evaluated.
	 */
	second_desc = obj_desc->common.next_object;
	second_desc->extra.aml_start = op->named.data;
	second_desc->extra.aml_length = op->named.length;
	obj_desc->buffer_field.node = node;

	/* Attach constructed field descriptors to parent node */

	status = acpi_ns_attach_object(node, obj_desc, ACPI_TYPE_BUFFER_FIELD);
	if (ACPI_FAILURE(status)) {
		goto cleanup;
	}

cleanup:

	/* Remove local reference to the object */

	acpi_ut_remove_reference(obj_desc);
	return_ACPI_STATUS(status);
}