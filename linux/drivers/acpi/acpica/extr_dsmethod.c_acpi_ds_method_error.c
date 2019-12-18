#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {int /*<<< orphan*/  aml_start; } ;
struct acpi_walk_state {int /*<<< orphan*/  op; int /*<<< orphan*/  opcode; TYPE_5__* deferred_node; TYPE_3__* method_node; TYPE_1__ parser_state; int /*<<< orphan*/  aml; } ;
typedef  int acpi_status ;
typedef  int /*<<< orphan*/  acpi_name ;
struct TYPE_9__ {int /*<<< orphan*/  integer; } ;
struct TYPE_10__ {TYPE_4__ name; } ;
struct TYPE_7__ {int /*<<< orphan*/  integer; } ;
struct TYPE_8__ {TYPE_2__ name; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_PTR_DIFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int) ; 
 int AE_CODE_CONTROL ; 
 int /*<<< orphan*/  acpi_db_dump_method_info (int,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ds_clear_implicit_return (struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ds_dump_method_stack (int,struct acpi_walk_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_enter_interpreter () ; 
 int /*<<< orphan*/  acpi_ex_exit_interpreter () ; 
 int acpi_gbl_exception_handler (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

acpi_status
acpi_ds_method_error(acpi_status status, struct acpi_walk_state *walk_state)
{
	u32 aml_offset;
	acpi_name name = 0;

	ACPI_FUNCTION_ENTRY();

	/* Ignore AE_OK and control exception codes */

	if (ACPI_SUCCESS(status) || (status & AE_CODE_CONTROL)) {
		return (status);
	}

	/* Invoke the global exception handler */

	if (acpi_gbl_exception_handler) {

		/* Exit the interpreter, allow handler to execute methods */

		acpi_ex_exit_interpreter();

		/*
		 * Handler can map the exception code to anything it wants, including
		 * AE_OK, in which case the executing method will not be aborted.
		 */
		aml_offset = (u32)ACPI_PTR_DIFF(walk_state->aml,
						walk_state->parser_state.
						aml_start);

		if (walk_state->method_node) {
			name = walk_state->method_node->name.integer;
		} else if (walk_state->deferred_node) {
			name = walk_state->deferred_node->name.integer;
		}

		status = acpi_gbl_exception_handler(status, name,
						    walk_state->opcode,
						    aml_offset, NULL);
		acpi_ex_enter_interpreter();
	}

	acpi_ds_clear_implicit_return(walk_state);

	if (ACPI_FAILURE(status)) {
		acpi_ds_dump_method_stack(status, walk_state, walk_state->op);

		/* Display method locals/args if debugger is present */

#ifdef ACPI_DEBUGGER
		acpi_db_dump_method_info(status, walk_state);
#endif
	}

	return (status);
}