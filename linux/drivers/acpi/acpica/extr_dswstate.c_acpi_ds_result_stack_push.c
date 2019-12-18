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
struct TYPE_2__ {int /*<<< orphan*/  descriptor_type; } ;
union acpi_generic_state {TYPE_1__ common; } ;
typedef  scalar_t__ u32 ;
struct acpi_walk_state {scalar_t__ result_size; int /*<<< orphan*/  results; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DESC_TYPE_STATE_RESULT ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_RESULTS_FRAME_OBJ_NUM ; 
 scalar_t__ ACPI_RESULTS_OBJ_NUM_MAX ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_STACK_OVERFLOW ; 
 union acpi_generic_state* acpi_ut_create_generic_state () ; 
 int /*<<< orphan*/  acpi_ut_push_generic_state (int /*<<< orphan*/ *,union acpi_generic_state*) ; 
 int /*<<< orphan*/  ds_result_stack_push ; 

__attribute__((used)) static acpi_status acpi_ds_result_stack_push(struct acpi_walk_state *walk_state)
{
	union acpi_generic_state *state;

	ACPI_FUNCTION_NAME(ds_result_stack_push);

	/* Check for stack overflow */

	if (((u32) walk_state->result_size + ACPI_RESULTS_FRAME_OBJ_NUM) >
	    ACPI_RESULTS_OBJ_NUM_MAX) {
		ACPI_ERROR((AE_INFO, "Result stack overflow: State=%p Num=%u",
			    walk_state, walk_state->result_size));
		return (AE_STACK_OVERFLOW);
	}

	state = acpi_ut_create_generic_state();
	if (!state) {
		return (AE_NO_MEMORY);
	}

	state->common.descriptor_type = ACPI_DESC_TYPE_STATE_RESULT;
	acpi_ut_push_generic_state(&walk_state->results, state);

	/* Increase the length of the result stack by the length of frame */

	walk_state->result_size += ACPI_RESULTS_FRAME_OBJ_NUM;

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Results=%p State=%p\n",
			  state, walk_state));

	return (AE_OK);
}