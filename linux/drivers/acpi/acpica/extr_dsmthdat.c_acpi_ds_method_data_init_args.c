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
typedef  size_t u32 ;
struct acpi_walk_state {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object**) ; 
 size_t ACPI_METHOD_NUM_ARGS ; 
 int /*<<< orphan*/  ACPI_REFCLASS_ARG ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ds_method_data_set_value (int /*<<< orphan*/ ,size_t,union acpi_operand_object*,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  ds_method_data_init_args ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_method_data_init_args(union acpi_operand_object **params,
			      u32 max_param_count,
			      struct acpi_walk_state *walk_state)
{
	acpi_status status;
	u32 index = 0;

	ACPI_FUNCTION_TRACE_PTR(ds_method_data_init_args, params);

	if (!params) {
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "No parameter list passed to method\n"));
		return_ACPI_STATUS(AE_OK);
	}

	/* Copy passed parameters into the new method stack frame */

	while ((index < ACPI_METHOD_NUM_ARGS) &&
	       (index < max_param_count) && params[index]) {
		/*
		 * A valid parameter.
		 * Store the argument in the method/walk descriptor.
		 * Do not copy the arg in order to implement call by reference
		 */
		status =
		    acpi_ds_method_data_set_value(ACPI_REFCLASS_ARG, index,
						  params[index], walk_state);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}

		index++;
	}

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "%u args passed to method\n", index));
	return_ACPI_STATUS(AE_OK);
}