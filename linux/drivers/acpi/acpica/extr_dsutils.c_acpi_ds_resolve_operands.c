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
typedef  size_t u32 ;
struct acpi_walk_state {size_t num_operands; int /*<<< orphan*/ * operands; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ex_resolve_to_value (int /*<<< orphan*/ *,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  ds_resolve_operands ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ds_resolve_operands(struct acpi_walk_state *walk_state)
{
	u32 i;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE_PTR(ds_resolve_operands, walk_state);

	/*
	 * Attempt to resolve each of the valid operands
	 * Method arguments are passed by reference, not by value. This means
	 * that the actual objects are passed, not copies of the objects.
	 */
	for (i = 0; i < walk_state->num_operands; i++) {
		status =
		    acpi_ex_resolve_to_value(&walk_state->operands[i],
					     walk_state);
		if (ACPI_FAILURE(status)) {
			break;
		}
	}

	return_ACPI_STATUS(status);
}