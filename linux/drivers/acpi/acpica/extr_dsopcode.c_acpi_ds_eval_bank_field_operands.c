#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {union acpi_parse_object* arg; } ;
struct TYPE_8__ {scalar_t__ aml_opcode; union acpi_parse_object* next; struct acpi_namespace_node* node; TYPE_1__ value; } ;
union acpi_parse_object {TYPE_4__ common; } ;
struct TYPE_7__ {scalar_t__ value; } ;
struct TYPE_6__ {scalar_t__ value; } ;
union acpi_operand_object {TYPE_3__ integer; TYPE_2__ bank_field; } ;
typedef  scalar_t__ u32 ;
struct acpi_walk_state {union acpi_operand_object** operands; scalar_t__ operand_index; } ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DUMP_OPERANDS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_parse_object*) ; 
 int /*<<< orphan*/  ACPI_WALK_OPERANDS ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 scalar_t__ AML_INT_NAMEDFIELD_OP ; 
 int /*<<< orphan*/  acpi_ds_create_operand (struct acpi_walk_state*,union acpi_parse_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_resolve_to_value (union acpi_operand_object**,struct acpi_walk_state*) ; 
 union acpi_operand_object* acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 
 union acpi_parse_object* acpi_ps_get_arg (union acpi_parse_object*,int) ; 
 int /*<<< orphan*/  acpi_ps_get_opcode_name (scalar_t__) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ds_eval_bank_field_operands ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_eval_bank_field_operands(struct acpi_walk_state *walk_state,
				 union acpi_parse_object *op)
{
	acpi_status status;
	union acpi_operand_object *obj_desc;
	union acpi_operand_object *operand_desc;
	struct acpi_namespace_node *node;
	union acpi_parse_object *next_op;
	union acpi_parse_object *arg;

	ACPI_FUNCTION_TRACE_PTR(ds_eval_bank_field_operands, op);

	/*
	 * This is where we evaluate the bank_value field of the
	 * bank_field declaration
	 */

	/* next_op points to the op that holds the Region */

	next_op = op->common.value.arg;

	/* next_op points to the op that holds the Bank Register */

	next_op = next_op->common.next;

	/* next_op points to the op that holds the Bank Value */

	next_op = next_op->common.next;

	/*
	 * Set proper index into operand stack for acpi_ds_obj_stack_push
	 * invoked inside acpi_ds_create_operand.
	 *
	 * We use walk_state->Operands[0] to store the evaluated bank_value
	 */
	walk_state->operand_index = 0;

	status = acpi_ds_create_operand(walk_state, next_op, 0);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	status = acpi_ex_resolve_to_value(&walk_state->operands[0], walk_state);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	ACPI_DUMP_OPERANDS(ACPI_WALK_OPERANDS,
			   acpi_ps_get_opcode_name(op->common.aml_opcode), 1);
	/*
	 * Get the bank_value operand and save it
	 * (at Top of stack)
	 */
	operand_desc = walk_state->operands[0];

	/* Arg points to the start Bank Field */

	arg = acpi_ps_get_arg(op, 4);
	while (arg) {

		/* Ignore OFFSET and ACCESSAS terms here */

		if (arg->common.aml_opcode == AML_INT_NAMEDFIELD_OP) {
			node = arg->common.node;

			obj_desc = acpi_ns_get_attached_object(node);
			if (!obj_desc) {
				return_ACPI_STATUS(AE_NOT_EXIST);
			}

			obj_desc->bank_field.value =
			    (u32) operand_desc->integer.value;
		}

		/* Move to next field in the list */

		arg = arg->common.next;
	}

	acpi_ut_remove_reference(operand_desc);
	return_ACPI_STATUS(status);
}