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
typedef  union acpi_operand_object {int dummy; } acpi_operand_object ;
struct TYPE_2__ {union acpi_operand_object** obj_desc; } ;
union acpi_generic_state {TYPE_1__ results; } ;
typedef  size_t u32 ;
struct acpi_walk_state {scalar_t__ result_count; union acpi_generic_state* results; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 size_t ACPI_RESULTS_FRAME_OBJ_NUM ; 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_AML_NO_RETURN_VALUE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ds_result_stack_pop (struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ut_get_object_type_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ds_result_pop ; 

acpi_status
acpi_ds_result_pop(union acpi_operand_object **object,
		   struct acpi_walk_state *walk_state)
{
	u32 index;
	union acpi_generic_state *state;
	acpi_status status;

	ACPI_FUNCTION_NAME(ds_result_pop);

	state = walk_state->results;

	/* Incorrect state of result stack */

	if (state && !walk_state->result_count) {
		ACPI_ERROR((AE_INFO, "No results on result stack"));
		return (AE_AML_INTERNAL);
	}

	if (!state && walk_state->result_count) {
		ACPI_ERROR((AE_INFO, "No result state for result stack"));
		return (AE_AML_INTERNAL);
	}

	/* Empty result stack */

	if (!state) {
		ACPI_ERROR((AE_INFO, "Result stack is empty! State=%p",
			    walk_state));
		return (AE_AML_NO_RETURN_VALUE);
	}

	/* Return object of the top element and clean that top element result stack */

	walk_state->result_count--;
	index = (u32)walk_state->result_count % ACPI_RESULTS_FRAME_OBJ_NUM;

	*object = state->results.obj_desc[index];
	if (!*object) {
		ACPI_ERROR((AE_INFO,
			    "No result objects on result stack, State=%p",
			    walk_state));
		return (AE_AML_NO_RETURN_VALUE);
	}

	state->results.obj_desc[index] = NULL;
	if (index == 0) {
		status = acpi_ds_result_stack_pop(walk_state);
		if (ACPI_FAILURE(status)) {
			return (status);
		}
	}

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "Obj=%p [%s] Index=%X State=%p Num=%X\n", *object,
			  acpi_ut_get_object_type_name(*object),
			  index, walk_state, walk_state->result_count));

	return (AE_OK);
}