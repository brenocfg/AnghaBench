#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_7__* node; } ;
struct TYPE_11__ {scalar_t__ aml_opcode; } ;
union acpi_parse_object {TYPE_5__ named; TYPE_4__ common; } ;
typedef  int u32 ;
struct acpi_walk_state {scalar_t__ opcode; int walk_type; TYPE_6__* op_info; TYPE_3__* control_state; union acpi_parse_object* origin; union acpi_parse_object* op; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_14__ {int /*<<< orphan*/  type; } ;
struct TYPE_13__ {int class; int /*<<< orphan*/  object_type; } ;
struct TYPE_9__ {union acpi_parse_object* predicate_op; } ;
struct TYPE_8__ {scalar_t__ state; } ;
struct TYPE_10__ {TYPE_2__ control; TYPE_1__ common; } ;

/* Variables and functions */
 scalar_t__ ACPI_CONTROL_CONDITIONAL_EXECUTING ; 
 scalar_t__ ACPI_CONTROL_PREDICATE_EXECUTING ; 
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 int ACPI_WALK_METHOD ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_CLASS_CONTROL 131 
#define  AML_CLASS_CREATE 130 
#define  AML_CLASS_EXECUTE 129 
#define  AML_CLASS_NAMED_OBJECT 128 
 scalar_t__ AML_INT_NAMEPATH_OP ; 
 scalar_t__ AML_SCOPE_OP ; 
 int /*<<< orphan*/  acpi_ds_exec_begin_control_op (struct acpi_walk_state*,union acpi_parse_object*) ; 
 int /*<<< orphan*/  acpi_ds_load2_begin_op (struct acpi_walk_state*,union acpi_parse_object**) ; 
 int /*<<< orphan*/  acpi_ds_method_error (int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ds_scope_stack_pop (struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ds_scope_stack_push (TYPE_7__*,int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 scalar_t__ acpi_ns_opens_scope (int /*<<< orphan*/ ) ; 
 TYPE_6__* acpi_ps_get_opcode_info (scalar_t__) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds_exec_begin_op ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_exec_begin_op(struct acpi_walk_state *walk_state,
		      union acpi_parse_object **out_op)
{
	union acpi_parse_object *op;
	acpi_status status = AE_OK;
	u32 opcode_class;

	ACPI_FUNCTION_TRACE_PTR(ds_exec_begin_op, walk_state);

	op = walk_state->op;
	if (!op) {
		status = acpi_ds_load2_begin_op(walk_state, out_op);
		if (ACPI_FAILURE(status)) {
			goto error_exit;
		}

		op = *out_op;
		walk_state->op = op;
		walk_state->opcode = op->common.aml_opcode;
		walk_state->op_info =
		    acpi_ps_get_opcode_info(op->common.aml_opcode);

		if (acpi_ns_opens_scope(walk_state->op_info->object_type)) {
			ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
					  "(%s) Popping scope for Op %p\n",
					  acpi_ut_get_type_name(walk_state->
								op_info->
								object_type),
					  op));

			status = acpi_ds_scope_stack_pop(walk_state);
			if (ACPI_FAILURE(status)) {
				goto error_exit;
			}
		}
	}

	if (op == walk_state->origin) {
		if (out_op) {
			*out_op = op;
		}

		return_ACPI_STATUS(AE_OK);
	}

	/*
	 * If the previous opcode was a conditional, this opcode
	 * must be the beginning of the associated predicate.
	 * Save this knowledge in the current scope descriptor
	 */
	if ((walk_state->control_state) &&
	    (walk_state->control_state->common.state ==
	     ACPI_CONTROL_CONDITIONAL_EXECUTING)) {
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Exec predicate Op=%p State=%p\n",
				  op, walk_state));

		walk_state->control_state->common.state =
		    ACPI_CONTROL_PREDICATE_EXECUTING;

		/* Save start of predicate */

		walk_state->control_state->control.predicate_op = op;
	}

	opcode_class = walk_state->op_info->class;

	/* We want to send namepaths to the load code */

	if (op->common.aml_opcode == AML_INT_NAMEPATH_OP) {
		opcode_class = AML_CLASS_NAMED_OBJECT;
	}

	/*
	 * Handle the opcode based upon the opcode type
	 */
	switch (opcode_class) {
	case AML_CLASS_CONTROL:

		status = acpi_ds_exec_begin_control_op(walk_state, op);
		break;

	case AML_CLASS_NAMED_OBJECT:

		if (walk_state->walk_type & ACPI_WALK_METHOD) {
			/*
			 * Found a named object declaration during method execution;
			 * we must enter this object into the namespace. The created
			 * object is temporary and will be deleted upon completion of
			 * the execution of this method.
			 *
			 * Note 10/2010: Except for the Scope() op. This opcode does
			 * not actually create a new object, it refers to an existing
			 * object. However, for Scope(), we want to indeed open a
			 * new scope.
			 */
			if (op->common.aml_opcode != AML_SCOPE_OP) {
				status =
				    acpi_ds_load2_begin_op(walk_state, NULL);
			} else {
				status =
				    acpi_ds_scope_stack_push(op->named.node,
							     op->named.node->
							     type, walk_state);
				if (ACPI_FAILURE(status)) {
					return_ACPI_STATUS(status);
				}
			}
		}
		break;

	case AML_CLASS_EXECUTE:
	case AML_CLASS_CREATE:

		break;

	default:

		break;
	}

	/* Nothing to do here during method execution */

	return_ACPI_STATUS(status);

error_exit:
	status = acpi_ds_method_error(status, walk_state);
	return_ACPI_STATUS(status);
}