#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {union acpi_parse_object* arg; } ;
struct TYPE_6__ {int /*<<< orphan*/  aml_opcode; TYPE_1__ value; struct acpi_namespace_node* node; } ;
union acpi_parse_object {TYPE_2__ common; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  length; int /*<<< orphan*/  address; } ;
struct TYPE_7__ {int /*<<< orphan*/  pointer; } ;
union acpi_operand_object {TYPE_4__ region; TYPE_3__ string; } ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_walk_state {union acpi_operand_object** operands; } ;
struct acpi_table_header {int /*<<< orphan*/  length; } ;
struct acpi_namespace_node {int dummy; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_parse_object*) ; 
 int /*<<< orphan*/  ACPI_PTR_TO_PHYSADDR (struct acpi_table_header*) ; 
 int /*<<< orphan*/  ACPI_WALK_OPERANDS ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_NOT_EXIST ; 
 scalar_t__ AE_NOT_FOUND ; 
 int /*<<< orphan*/  AOPOBJ_DATA_VALID ; 
 scalar_t__ acpi_ds_create_operands (struct acpi_walk_state*,union acpi_parse_object*) ; 
 scalar_t__ acpi_ex_resolve_operands (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 scalar_t__ acpi_get_table_by_index (int /*<<< orphan*/ ,struct acpi_table_header**) ; 
 union acpi_operand_object* acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 
 scalar_t__ acpi_tb_find_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ds_eval_table_region_operands ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

acpi_status
acpi_ds_eval_table_region_operands(struct acpi_walk_state *walk_state,
				   union acpi_parse_object *op)
{
	acpi_status status;
	union acpi_operand_object *obj_desc;
	union acpi_operand_object **operand;
	struct acpi_namespace_node *node;
	union acpi_parse_object *next_op;
	struct acpi_table_header *table;
	u32 table_index;

	ACPI_FUNCTION_TRACE_PTR(ds_eval_table_region_operands, op);

	/*
	 * This is where we evaluate the Signature string, oem_id string,
	 * and oem_table_id string of the Data Table Region declaration
	 */
	node = op->common.node;

	/* next_op points to Signature string op */

	next_op = op->common.value.arg;

	/*
	 * Evaluate/create the Signature string, oem_id string,
	 * and oem_table_id string operands
	 */
	status = acpi_ds_create_operands(walk_state, next_op);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	operand = &walk_state->operands[0];

	/*
	 * Resolve the Signature string, oem_id string,
	 * and oem_table_id string operands
	 */
	status =
	    acpi_ex_resolve_operands(op->common.aml_opcode, ACPI_WALK_OPERANDS,
				     walk_state);
	if (ACPI_FAILURE(status)) {
		goto cleanup;
	}

	/* Find the ACPI table */

	status = acpi_tb_find_table(operand[0]->string.pointer,
				    operand[1]->string.pointer,
				    operand[2]->string.pointer, &table_index);
	if (ACPI_FAILURE(status)) {
		if (status == AE_NOT_FOUND) {
			ACPI_ERROR((AE_INFO,
				    "ACPI Table [%4.4s] OEM:(%s, %s) not found in RSDT/XSDT",
				    operand[0]->string.pointer,
				    operand[1]->string.pointer,
				    operand[2]->string.pointer));
		}
		goto cleanup;
	}

	status = acpi_get_table_by_index(table_index, &table);
	if (ACPI_FAILURE(status)) {
		goto cleanup;
	}

	obj_desc = acpi_ns_get_attached_object(node);
	if (!obj_desc) {
		status = AE_NOT_EXIST;
		goto cleanup;
	}

	obj_desc->region.address = ACPI_PTR_TO_PHYSADDR(table);
	obj_desc->region.length = table->length;

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "RgnObj %p Addr %8.8X%8.8X Len %X\n",
			  obj_desc,
			  ACPI_FORMAT_UINT64(obj_desc->region.address),
			  obj_desc->region.length));

	/* Now the address and length are valid for this opregion */

	obj_desc->region.flags |= AOPOBJ_DATA_VALID;

cleanup:
	acpi_ut_remove_reference(operand[0]);
	acpi_ut_remove_reference(operand[1]);
	acpi_ut_remove_reference(operand[2]);

	return_ACPI_STATUS(status);
}