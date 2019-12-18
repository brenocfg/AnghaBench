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
typedef  union acpi_object {int dummy; } acpi_object ;
typedef  size_t u32 ;
struct acpi_object_list {size_t count; union acpi_object* pointer; } ;
struct acpi_db_method_info {int /*<<< orphan*/  pathname; scalar_t__** args; int /*<<< orphan*/ * types; } ;
struct acpi_buffer {scalar_t__ length; int /*<<< orphan*/  pointer; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEBUGGER_MAX_ARGS ; 
 scalar_t__ ACPI_DEBUG_BUFFER_SIZE ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ AE_ABORT_METHOD ; 
 scalar_t__ AE_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_OK ; 
 void* FALSE ; 
 void* TRUE ; 
 scalar_t__ acpi_db_convert_to_object (int /*<<< orphan*/ ,scalar_t__*,union acpi_object*) ; 
 int /*<<< orphan*/  acpi_db_delete_objects (size_t,union acpi_object*) ; 
 int /*<<< orphan*/  acpi_dbg_level ; 
 scalar_t__ acpi_evaluate_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct acpi_object_list*,struct acpi_buffer*) ; 
 void* acpi_gbl_abort_method ; 
 void* acpi_gbl_cm_single_step ; 
 int /*<<< orphan*/  acpi_gbl_db_buffer ; 
 scalar_t__ acpi_gbl_db_output_to_file ; 
 void* acpi_gbl_method_executing ; 
 int /*<<< orphan*/  acpi_os_printf (char*) ; 
 int /*<<< orphan*/  db_execute_method ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

__attribute__((used)) static acpi_status
acpi_db_execute_method(struct acpi_db_method_info *info,
		       struct acpi_buffer *return_obj)
{
	acpi_status status;
	struct acpi_object_list param_objects;
	union acpi_object params[ACPI_DEBUGGER_MAX_ARGS + 1];
	u32 i;

	ACPI_FUNCTION_TRACE(db_execute_method);

	if (acpi_gbl_db_output_to_file && !acpi_dbg_level) {
		acpi_os_printf("Warning: debug output is not enabled!\n");
	}

	param_objects.count = 0;
	param_objects.pointer = NULL;

	/* Pass through any command-line arguments */

	if (info->args && info->args[0]) {

		/* Get arguments passed on the command line */

		for (i = 0; (info->args[i] && *(info->args[i])); i++) {

			/* Convert input string (token) to an actual union acpi_object */

			status = acpi_db_convert_to_object(info->types[i],
							   info->args[i],
							   &params[i]);
			if (ACPI_FAILURE(status)) {
				ACPI_EXCEPTION((AE_INFO, status,
						"While parsing method arguments"));
				goto cleanup;
			}
		}

		param_objects.count = i;
		param_objects.pointer = params;
	}

	/* Prepare for a return object of arbitrary size */

	return_obj->pointer = acpi_gbl_db_buffer;
	return_obj->length = ACPI_DEBUG_BUFFER_SIZE;

	/* Do the actual method execution */

	acpi_gbl_method_executing = TRUE;
	status = acpi_evaluate_object(NULL, info->pathname,
				      &param_objects, return_obj);

	acpi_gbl_cm_single_step = FALSE;
	acpi_gbl_method_executing = FALSE;

	if (ACPI_FAILURE(status)) {
		if ((status == AE_ABORT_METHOD) || acpi_gbl_abort_method) {

			/* Clear the abort and fall back to the debugger prompt */

			ACPI_EXCEPTION((AE_INFO, status,
					"Aborting top-level method"));

			acpi_gbl_abort_method = FALSE;
			status = AE_OK;
			goto cleanup;
		}

		ACPI_EXCEPTION((AE_INFO, status,
				"while executing %s from AML Debugger",
				info->pathname));

		if (status == AE_BUFFER_OVERFLOW) {
			ACPI_ERROR((AE_INFO,
				    "Possible buffer overflow within AML Debugger "
				    "buffer (size 0x%X needed 0x%X)",
				    ACPI_DEBUG_BUFFER_SIZE,
				    (u32)return_obj->length));
		}
	}

cleanup:
	acpi_db_delete_objects(param_objects.count, params);
	return_ACPI_STATUS(status);
}