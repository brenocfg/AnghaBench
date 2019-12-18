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
struct TYPE_8__ {scalar_t__ aml_opcode; union acpi_parse_object* next; int /*<<< orphan*/  aml; } ;
union acpi_parse_object {TYPE_4__ common; } ;
typedef  scalar_t__ u32 ;
struct TYPE_5__ {int /*<<< orphan*/  aml_start; } ;
struct acpi_walk_state {scalar_t__ method_breakpoint; scalar_t__ user_breakpoint; TYPE_3__* control_state; TYPE_1__ parser_state; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_6__ {scalar_t__ value; } ;
struct TYPE_7__ {TYPE_2__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_LV_FUNCTIONS ; 
 scalar_t__ ACPI_LV_PARSE ; 
 scalar_t__ ACPI_PTR_DIFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_ABORT_METHOD ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_CLASS_ARGUMENT 129 
#define  AML_CLASS_UNKNOWN 128 
 scalar_t__ AML_ELSE_OP ; 
 scalar_t__ AML_IF_OP ; 
 scalar_t__ AML_INT_METHODCALL_OP ; 
 scalar_t__ AML_INT_NAMEDFIELD_OP ; 
 scalar_t__ AML_WHILE_OP ; 
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  acpi_db_get_display_op (struct acpi_walk_state*,union acpi_parse_object*) ; 
 int /*<<< orphan*/  acpi_db_start_command (struct acpi_walk_state*,union acpi_parse_object*) ; 
 scalar_t__ acpi_dbg_level ; 
 int /*<<< orphan*/  acpi_dm_disassemble (struct acpi_walk_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_enter_interpreter () ; 
 int /*<<< orphan*/  acpi_ex_exit_interpreter () ; 
 void* acpi_gbl_abort_method ; 
 void* acpi_gbl_cm_single_step ; 
 scalar_t__ acpi_gbl_db_output_to_file ; 
 scalar_t__ acpi_gbl_db_thread_id ; 
 void* acpi_gbl_step_to_next_call ; 
 scalar_t__ acpi_os_get_thread_id () ; 
 int /*<<< orphan*/  acpi_os_printf (char*,...) ; 
 int /*<<< orphan*/  acpi_ps_get_opcode_name (scalar_t__) ; 

acpi_status
acpi_db_single_step(struct acpi_walk_state *walk_state,
		    union acpi_parse_object *op, u32 opcode_class)
{
	union acpi_parse_object *next;
	acpi_status status = AE_OK;
	u32 original_debug_level;
	u32 aml_offset;

	ACPI_FUNCTION_ENTRY();

#ifndef ACPI_APPLICATION
	if (acpi_gbl_db_thread_id != acpi_os_get_thread_id()) {
		return (AE_OK);
	}
#endif

	/* Check the abort flag */

	if (acpi_gbl_abort_method) {
		acpi_gbl_abort_method = FALSE;
		return (AE_ABORT_METHOD);
	}

	aml_offset = (u32)ACPI_PTR_DIFF(op->common.aml,
					walk_state->parser_state.aml_start);

	/* Check for single-step breakpoint */

	if (walk_state->method_breakpoint &&
	    (walk_state->method_breakpoint <= aml_offset)) {

		/* Check if the breakpoint has been reached or passed */
		/* Hit the breakpoint, resume single step, reset breakpoint */

		acpi_os_printf("***Break*** at AML offset %X\n", aml_offset);
		acpi_gbl_cm_single_step = TRUE;
		acpi_gbl_step_to_next_call = FALSE;
		walk_state->method_breakpoint = 0;
	}

	/* Check for user breakpoint (Must be on exact Aml offset) */

	else if (walk_state->user_breakpoint &&
		 (walk_state->user_breakpoint == aml_offset)) {
		acpi_os_printf("***UserBreakpoint*** at AML offset %X\n",
			       aml_offset);
		acpi_gbl_cm_single_step = TRUE;
		acpi_gbl_step_to_next_call = FALSE;
		walk_state->method_breakpoint = 0;
	}

	/*
	 * Check if this is an opcode that we are interested in --
	 * namely, opcodes that have arguments
	 */
	if (op->common.aml_opcode == AML_INT_NAMEDFIELD_OP) {
		return (AE_OK);
	}

	switch (opcode_class) {
	case AML_CLASS_UNKNOWN:
	case AML_CLASS_ARGUMENT:	/* constants, literals, etc. do nothing */

		return (AE_OK);

	default:

		/* All other opcodes -- continue */
		break;
	}

	/*
	 * Under certain debug conditions, display this opcode and its operands
	 */
	if ((acpi_gbl_db_output_to_file) ||
	    (acpi_gbl_cm_single_step) || (acpi_dbg_level & ACPI_LV_PARSE)) {
		if ((acpi_gbl_db_output_to_file) ||
		    (acpi_dbg_level & ACPI_LV_PARSE)) {
			acpi_os_printf
			    ("\nAML Debug: Next AML Opcode to execute:\n");
		}

		/*
		 * Display this op (and only this op - zero out the NEXT field
		 * temporarily, and disable parser trace output for the duration of
		 * the display because we don't want the extraneous debug output)
		 */
		original_debug_level = acpi_dbg_level;
		acpi_dbg_level &= ~(ACPI_LV_PARSE | ACPI_LV_FUNCTIONS);
		next = op->common.next;
		op->common.next = NULL;

		/* Now we can disassemble and display it */

#ifdef ACPI_DISASSEMBLER
		acpi_dm_disassemble(walk_state,
				    acpi_db_get_display_op(walk_state, op),
				    ACPI_UINT32_MAX);
#else
		/*
		 * The AML Disassembler is not configured - at least we can
		 * display the opcode value and name
		 */
		acpi_os_printf("AML Opcode: %4.4X %s\n", op->common.aml_opcode,
			       acpi_ps_get_opcode_name(op->common.aml_opcode));
#endif

		if ((op->common.aml_opcode == AML_IF_OP) ||
		    (op->common.aml_opcode == AML_WHILE_OP)) {
			if (walk_state->control_state->common.value) {
				acpi_os_printf
				    ("Predicate = [True], IF block was executed\n");
			} else {
				acpi_os_printf
				    ("Predicate = [False], Skipping IF block\n");
			}
		} else if (op->common.aml_opcode == AML_ELSE_OP) {
			acpi_os_printf
			    ("Predicate = [False], ELSE block was executed\n");
		}

		/* Restore everything */

		op->common.next = next;
		acpi_os_printf("\n");
		if ((acpi_gbl_db_output_to_file) ||
		    (acpi_dbg_level & ACPI_LV_PARSE)) {
			acpi_os_printf("\n");
		}
		acpi_dbg_level = original_debug_level;
	}

	/* If we are not single stepping, just continue executing the method */

	if (!acpi_gbl_cm_single_step) {
		return (AE_OK);
	}

	/*
	 * If we are executing a step-to-call command,
	 * Check if this is a method call.
	 */
	if (acpi_gbl_step_to_next_call) {
		if (op->common.aml_opcode != AML_INT_METHODCALL_OP) {

			/* Not a method call, just keep executing */

			return (AE_OK);
		}

		/* Found a method call, stop executing */

		acpi_gbl_step_to_next_call = FALSE;
	}

	/*
	 * If the next opcode is a method call, we will "step over" it
	 * by default.
	 */
	if (op->common.aml_opcode == AML_INT_METHODCALL_OP) {

		/* Force no more single stepping while executing called method */

		acpi_gbl_cm_single_step = FALSE;

		/*
		 * Set the breakpoint on/before the call, it will stop execution
		 * as soon as we return
		 */
		walk_state->method_breakpoint = 1;	/* Must be non-zero! */
	}

	acpi_ex_exit_interpreter();
	status = acpi_db_start_command(walk_state, op);
	acpi_ex_enter_interpreter();

	/* User commands complete, continue execution of the interrupted method */

	return (status);
}