#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
struct TYPE_3__ {union acpi_generic_state* next; } ;
union acpi_generic_state {TYPE_2__ common; TYPE_1__ scope; } ;
struct acpi_walk_state {union acpi_generic_state* scope_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_delete_generic_state (union acpi_generic_state*) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds_scope_stack_clear ; 

void acpi_ds_scope_stack_clear(struct acpi_walk_state *walk_state)
{
	union acpi_generic_state *scope_info;

	ACPI_FUNCTION_NAME(ds_scope_stack_clear);

	while (walk_state->scope_info) {

		/* Pop a scope off the stack */

		scope_info = walk_state->scope_info;
		walk_state->scope_info = scope_info->scope.next;

		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Popped object type (%s)\n",
				  acpi_ut_get_type_name(scope_info->common.
							value)));

		acpi_ut_delete_generic_state(scope_info);
	}
}