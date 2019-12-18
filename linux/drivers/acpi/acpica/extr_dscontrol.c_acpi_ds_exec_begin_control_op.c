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
struct TYPE_10__ {int aml_opcode; } ;
union acpi_parse_object {TYPE_4__ common; } ;
struct TYPE_11__ {int opcode; scalar_t__ loop_timeout; int /*<<< orphan*/  package_end; int /*<<< orphan*/  aml_predicate_start; } ;
union acpi_generic_state {TYPE_5__ control; } ;
typedef  scalar_t__ u64 ;
struct TYPE_9__ {int /*<<< orphan*/  pkg_end; int /*<<< orphan*/  aml; } ;
struct acpi_walk_state {int /*<<< orphan*/  last_predicate; TYPE_6__* control_state; TYPE_3__ parser_state; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_8__ {int /*<<< orphan*/  state; } ;
struct TYPE_7__ {int /*<<< orphan*/  aml_predicate_start; } ;
struct TYPE_12__ {TYPE_2__ common; TYPE_1__ control; } ;

/* Variables and functions */
 int ACPI_100NSEC_PER_SEC ; 
 int /*<<< orphan*/  ACPI_CONTROL_CONDITIONAL_EXECUTING ; 
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_CTRL_TRUE ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_ELSE_OP 131 
#define  AML_IF_OP 130 
#define  AML_RETURN_OP 129 
#define  AML_WHILE_OP 128 
 int acpi_gbl_max_loop_iterations ; 
 scalar_t__ acpi_os_get_timer () ; 
 union acpi_generic_state* acpi_ut_create_control_state () ; 
 int /*<<< orphan*/  acpi_ut_push_generic_state (TYPE_6__**,union acpi_generic_state*) ; 
 int /*<<< orphan*/  ds_exec_begin_control_op ; 

acpi_status
acpi_ds_exec_begin_control_op(struct acpi_walk_state *walk_state,
			      union acpi_parse_object *op)
{
	acpi_status status = AE_OK;
	union acpi_generic_state *control_state;

	ACPI_FUNCTION_NAME(ds_exec_begin_control_op);

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH, "Op=%p Opcode=%2.2X State=%p\n",
			  op, op->common.aml_opcode, walk_state));

	switch (op->common.aml_opcode) {
	case AML_WHILE_OP:
		/*
		 * If this is an additional iteration of a while loop, continue.
		 * There is no need to allocate a new control state.
		 */
		if (walk_state->control_state) {
			if (walk_state->control_state->control.
			    aml_predicate_start ==
			    (walk_state->parser_state.aml - 1)) {

				/* Reset the state to start-of-loop */

				walk_state->control_state->common.state =
				    ACPI_CONTROL_CONDITIONAL_EXECUTING;
				break;
			}
		}

		/*lint -fallthrough */

	case AML_IF_OP:
		/*
		 * IF/WHILE: Create a new control state to manage these
		 * constructs. We need to manage these as a stack, in order
		 * to handle nesting.
		 */
		control_state = acpi_ut_create_control_state();
		if (!control_state) {
			status = AE_NO_MEMORY;
			break;
		}
		/*
		 * Save a pointer to the predicate for multiple executions
		 * of a loop
		 */
		control_state->control.aml_predicate_start =
		    walk_state->parser_state.aml - 1;
		control_state->control.package_end =
		    walk_state->parser_state.pkg_end;
		control_state->control.opcode = op->common.aml_opcode;
		control_state->control.loop_timeout = acpi_os_get_timer() +
		    (u64)(acpi_gbl_max_loop_iterations * ACPI_100NSEC_PER_SEC);

		/* Push the control state on this walk's control stack */

		acpi_ut_push_generic_state(&walk_state->control_state,
					   control_state);
		break;

	case AML_ELSE_OP:

		/* Predicate is in the state object */
		/* If predicate is true, the IF was executed, ignore ELSE part */

		if (walk_state->last_predicate) {
			status = AE_CTRL_TRUE;
		}

		break;

	case AML_RETURN_OP:

		break;

	default:

		break;
	}

	return (status);
}