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
struct TYPE_2__ {int aml_length; int /*<<< orphan*/  info_flags; int /*<<< orphan*/  owner_id; int /*<<< orphan*/ * aml_start; } ;
union acpi_operand_object {TYPE_1__ method; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct acpi_table_header {int length; int /*<<< orphan*/  signature; } ;
struct acpi_namespace_node {int /*<<< orphan*/  flags; } ;
struct acpi_evaluate_info {struct acpi_evaluate_info* full_pathname; struct acpi_namespace_node* node; int /*<<< orphan*/  node_flags; union acpi_operand_object* obj_desc; int /*<<< orphan*/  pass_number; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_owner_id ;

/* Variables and functions */
 struct acpi_evaluate_info* ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_DB_EVALUATION ; 
 int /*<<< orphan*/  ACPI_DB_PARSE ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (struct acpi_evaluate_info*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_GET_FUNCTION_NAME ; 
 int /*<<< orphan*/  ACPI_IMODE_EXECUTE ; 
 int /*<<< orphan*/  ACPI_METHOD_MODULE_LEVEL ; 
 int /*<<< orphan*/  ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  AE_BAD_HEADER ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_get_table_by_index (int,struct acpi_table_header**) ; 
 struct acpi_evaluate_info* acpi_ns_get_normalized_pathname (struct acpi_namespace_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ps_execute_table (struct acpi_evaluate_info*) ; 
 int /*<<< orphan*/  acpi_tb_get_owner_id (int,int /*<<< orphan*/ *) ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ns_execute_table ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ns_execute_table(u32 table_index, struct acpi_namespace_node *start_node)
{
	acpi_status status;
	struct acpi_table_header *table;
	acpi_owner_id owner_id;
	struct acpi_evaluate_info *info = NULL;
	u32 aml_length;
	u8 *aml_start;
	union acpi_operand_object *method_obj = NULL;

	ACPI_FUNCTION_TRACE(ns_execute_table);

	status = acpi_get_table_by_index(table_index, &table);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Table must consist of at least a complete header */

	if (table->length < sizeof(struct acpi_table_header)) {
		return_ACPI_STATUS(AE_BAD_HEADER);
	}

	aml_start = (u8 *)table + sizeof(struct acpi_table_header);
	aml_length = table->length - sizeof(struct acpi_table_header);

	status = acpi_tb_get_owner_id(table_index, &owner_id);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Create, initialize, and link a new temporary method object */

	method_obj = acpi_ut_create_internal_object(ACPI_TYPE_METHOD);
	if (!method_obj) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	/* Allocate the evaluation information block */

	info = ACPI_ALLOCATE_ZEROED(sizeof(struct acpi_evaluate_info));
	if (!info) {
		status = AE_NO_MEMORY;
		goto cleanup;
	}

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_PARSE,
			      "%s: Create table pseudo-method for [%4.4s] @%p, method %p\n",
			      ACPI_GET_FUNCTION_NAME, table->signature, table,
			      method_obj));

	method_obj->method.aml_start = aml_start;
	method_obj->method.aml_length = aml_length;
	method_obj->method.owner_id = owner_id;
	method_obj->method.info_flags |= ACPI_METHOD_MODULE_LEVEL;

	info->pass_number = ACPI_IMODE_EXECUTE;
	info->node = start_node;
	info->obj_desc = method_obj;
	info->node_flags = info->node->flags;
	info->full_pathname = acpi_ns_get_normalized_pathname(info->node, TRUE);
	if (!info->full_pathname) {
		status = AE_NO_MEMORY;
		goto cleanup;
	}

	/* Optional object evaluation log */

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_EVALUATION,
			      "%-26s:  (Definition Block level)\n",
			      "Module-level evaluation"));

	status = acpi_ps_execute_table(info);

	/* Optional object evaluation log */

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_EVALUATION,
			      "%-26s:  (Definition Block level)\n",
			      "Module-level complete"));

cleanup:
	if (info) {
		ACPI_FREE(info->full_pathname);
		info->full_pathname = NULL;
	}
	ACPI_FREE(info);
	acpi_ut_remove_reference(method_obj);
	return_ACPI_STATUS(status);
}