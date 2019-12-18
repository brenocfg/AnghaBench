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
typedef  scalar_t__ u32 ;
struct acpi_walk_state {scalar_t__ num_operands; union acpi_operand_object** operands; } ;
typedef  size_t s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ds_obj_stack_pop_and_delete ; 

void
acpi_ds_obj_stack_pop_and_delete(u32 pop_count,
				 struct acpi_walk_state *walk_state)
{
	s32 i;
	union acpi_operand_object *obj_desc;

	ACPI_FUNCTION_NAME(ds_obj_stack_pop_and_delete);

	if (pop_count == 0) {
		return;
	}

	for (i = (s32)pop_count - 1; i >= 0; i--) {
		if (walk_state->num_operands == 0) {
			return;
		}

		/* Pop the stack and delete an object if present in this stack entry */

		walk_state->num_operands--;
		obj_desc = walk_state->operands[i];
		if (obj_desc) {
			acpi_ut_remove_reference(walk_state->operands[i]);
			walk_state->operands[i] = NULL;
		}
	}

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Count=%X State=%p #Ops=%X\n",
			  pop_count, walk_state, walk_state->num_operands));
}