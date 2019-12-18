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
typedef  union acpi_parse_object {int dummy; } acpi_parse_object ;
struct acpi_walk_state {int /*<<< orphan*/  parse_flags; int /*<<< orphan*/  method_is_nested; int /*<<< orphan*/  method_pathname; } ;
struct acpi_evaluate_info {int /*<<< orphan*/  node; TYPE_2__* obj_desc; int /*<<< orphan*/  full_pathname; int /*<<< orphan*/  pass_number; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_3__ {int info_flags; int /*<<< orphan*/  aml_length; int /*<<< orphan*/  aml_start; int /*<<< orphan*/  owner_id; } ;
struct TYPE_4__ {TYPE_1__ method; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_METHOD_MODULE_LEVEL ; 
 int /*<<< orphan*/  ACPI_PARSE_MODULE_LEVEL ; 
 int /*<<< orphan*/  ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 struct acpi_walk_state* acpi_ds_create_walk_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ds_delete_walk_state (struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ds_init_aml_walk (struct acpi_walk_state*,union acpi_parse_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_evaluate_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ds_scope_stack_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ex_enter_interpreter () ; 
 int /*<<< orphan*/  acpi_ex_exit_interpreter () ; 
 int /*<<< orphan*/  acpi_gbl_root_node ; 
 union acpi_parse_object* acpi_ps_create_scope_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ps_delete_parse_tree (union acpi_parse_object*) ; 
 int /*<<< orphan*/  acpi_ps_parse_aml (struct acpi_walk_state*) ; 
 int /*<<< orphan*/  ps_execute_table ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ps_execute_table(struct acpi_evaluate_info *info)
{
	acpi_status status;
	union acpi_parse_object *op = NULL;
	struct acpi_walk_state *walk_state = NULL;

	ACPI_FUNCTION_TRACE(ps_execute_table);

	/* Create and init a Root Node */

	op = acpi_ps_create_scope_op(info->obj_desc->method.aml_start);
	if (!op) {
		status = AE_NO_MEMORY;
		goto cleanup;
	}

	/* Create and initialize a new walk state */

	walk_state =
	    acpi_ds_create_walk_state(info->obj_desc->method.owner_id, NULL,
				      NULL, NULL);
	if (!walk_state) {
		status = AE_NO_MEMORY;
		goto cleanup;
	}

	status = acpi_ds_init_aml_walk(walk_state, op, info->node,
				       info->obj_desc->method.aml_start,
				       info->obj_desc->method.aml_length, info,
				       info->pass_number);
	if (ACPI_FAILURE(status)) {
		goto cleanup;
	}

	walk_state->method_pathname = info->full_pathname;
	walk_state->method_is_nested = FALSE;

	if (info->obj_desc->method.info_flags & ACPI_METHOD_MODULE_LEVEL) {
		walk_state->parse_flags |= ACPI_PARSE_MODULE_LEVEL;
	}

	/* Info->Node is the default location to load the table  */

	if (info->node && info->node != acpi_gbl_root_node) {
		status =
		    acpi_ds_scope_stack_push(info->node, ACPI_TYPE_METHOD,
					     walk_state);
		if (ACPI_FAILURE(status)) {
			goto cleanup;
		}
	}

	/*
	 * Parse the AML, walk_state will be deleted by parse_aml
	 */
	acpi_ex_enter_interpreter();
	status = acpi_ps_parse_aml(walk_state);
	acpi_ex_exit_interpreter();
	walk_state = NULL;

cleanup:
	if (walk_state) {
		acpi_ds_delete_walk_state(walk_state);
	}
	if (op) {
		acpi_ps_delete_parse_tree(op);
	}
	return_ACPI_STATUS(status);
}