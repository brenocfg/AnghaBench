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
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
union acpi_operand_object {TYPE_1__ integer; } ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_walk_state {int opcode; union acpi_operand_object** operands; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_STR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_AML_BAD_OPCODE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_RELEASE_OP 133 
#define  AML_RESET_OP 132 
#define  AML_SIGNAL_OP 131 
#define  AML_SLEEP_OP 130 
#define  AML_STALL_OP 129 
#define  AML_UNLOAD_OP 128 
 int /*<<< orphan*/  acpi_ex_release_mutex (union acpi_operand_object*,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ex_system_do_sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_system_do_stall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_system_reset_event (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ex_system_signal_event (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ex_unload_table (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ps_get_opcode_name (int) ; 
 int /*<<< orphan*/  ex_opcode_1A_0T_0R ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ex_opcode_1A_0T_0R(struct acpi_walk_state *walk_state)
{
	union acpi_operand_object **operand = &walk_state->operands[0];
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE_STR(ex_opcode_1A_0T_0R,
				acpi_ps_get_opcode_name(walk_state->opcode));

	/* Examine the AML opcode */

	switch (walk_state->opcode) {
	case AML_RELEASE_OP:	/*  Release (mutex_object) */

		status = acpi_ex_release_mutex(operand[0], walk_state);
		break;

	case AML_RESET_OP:	/*  Reset (event_object) */

		status = acpi_ex_system_reset_event(operand[0]);
		break;

	case AML_SIGNAL_OP:	/*  Signal (event_object) */

		status = acpi_ex_system_signal_event(operand[0]);
		break;

	case AML_SLEEP_OP:	/*  Sleep (msec_time) */

		status = acpi_ex_system_do_sleep(operand[0]->integer.value);
		break;

	case AML_STALL_OP:	/*  Stall (usec_time) */

		status =
		    acpi_ex_system_do_stall((u32) operand[0]->integer.value);
		break;

	case AML_UNLOAD_OP:	/*  Unload (Handle) */

		status = acpi_ex_unload_table(operand[0]);
		break;

	default:		/*  Unknown opcode  */

		ACPI_ERROR((AE_INFO, "Unknown AML opcode 0x%X",
			    walk_state->opcode));
		status = AE_AML_BAD_OPCODE;
		break;
	}

	return_ACPI_STATUS(status);
}