#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int target_type; union acpi_operand_object* object; int /*<<< orphan*/ * where; int /*<<< orphan*/ * index_pointer; int /*<<< orphan*/  class; int /*<<< orphan*/  value; } ;
struct TYPE_14__ {int /*<<< orphan*/  type; } ;
struct TYPE_13__ {size_t count; int /*<<< orphan*/ * elements; } ;
struct TYPE_11__ {size_t length; int /*<<< orphan*/ * pointer; } ;
struct TYPE_10__ {size_t length; int /*<<< orphan*/  pointer; } ;
struct TYPE_9__ {size_t value; } ;
union acpi_operand_object {TYPE_5__ reference; TYPE_7__ common; TYPE_6__ package; TYPE_4__ buffer; TYPE_3__ string; TYPE_2__ integer; } ;
typedef  size_t u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_walk_state {int opcode; union acpi_operand_object* result_obj; TYPE_1__* op_info; union acpi_operand_object** operands; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  size_t acpi_size ;
struct TYPE_8__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BIOS_EXCEPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (size_t) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_STR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_REFCLASS_INDEX ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
#define  ACPI_TYPE_BUFFER 135 
 void* ACPI_TYPE_BUFFER_FIELD ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_REFERENCE ; 
#define  ACPI_TYPE_PACKAGE 134 
#define  ACPI_TYPE_STRING 133 
 int /*<<< orphan*/  AE_AML_BAD_OPCODE ; 
 int /*<<< orphan*/  AE_AML_BUFFER_LIMIT ; 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_AML_PACKAGE_LIMIT ; 
 int /*<<< orphan*/  AE_AML_STRING_LIMIT ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_CONCATENATE_OP 132 
#define  AML_CONCATENATE_TEMPLATE_OP 131 
#define  AML_INDEX_OP 130 
 int AML_MATH ; 
#define  AML_MOD_OP 129 
#define  AML_TO_STRING_OP 128 
 int /*<<< orphan*/  acpi_ex_concat_template (union acpi_operand_object*,union acpi_operand_object*,union acpi_operand_object**,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ex_do_concatenate (union acpi_operand_object*,union acpi_operand_object*,union acpi_operand_object**,struct acpi_walk_state*) ; 
 size_t acpi_ex_do_math_op (int,size_t,size_t) ; 
 int /*<<< orphan*/  acpi_ex_store (union acpi_operand_object*,union acpi_operand_object*,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ps_get_opcode_name (int) ; 
 int /*<<< orphan*/  acpi_ut_add_reference (union acpi_operand_object*) ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 union acpi_operand_object* acpi_ut_create_string_object (size_t) ; 
 int /*<<< orphan*/  acpi_ut_divide (size_t,size_t,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ex_opcode_2A_1T_1R ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ex_opcode_2A_1T_1R(struct acpi_walk_state *walk_state)
{
	union acpi_operand_object **operand = &walk_state->operands[0];
	union acpi_operand_object *return_desc = NULL;
	u64 index;
	acpi_status status = AE_OK;
	acpi_size length = 0;

	ACPI_FUNCTION_TRACE_STR(ex_opcode_2A_1T_1R,
				acpi_ps_get_opcode_name(walk_state->opcode));

	/* Execute the opcode */

	if (walk_state->op_info->flags & AML_MATH) {

		/* All simple math opcodes (add, etc.) */

		return_desc = acpi_ut_create_internal_object(ACPI_TYPE_INTEGER);
		if (!return_desc) {
			status = AE_NO_MEMORY;
			goto cleanup;
		}

		return_desc->integer.value =
		    acpi_ex_do_math_op(walk_state->opcode,
				       operand[0]->integer.value,
				       operand[1]->integer.value);
		goto store_result_to_target;
	}

	switch (walk_state->opcode) {
	case AML_MOD_OP:	/* Mod (Dividend, Divisor, remainder_result (ACPI 2.0) */

		return_desc = acpi_ut_create_internal_object(ACPI_TYPE_INTEGER);
		if (!return_desc) {
			status = AE_NO_MEMORY;
			goto cleanup;
		}

		/* return_desc will contain the remainder */

		status = acpi_ut_divide(operand[0]->integer.value,
					operand[1]->integer.value,
					NULL, &return_desc->integer.value);
		break;

	case AML_CONCATENATE_OP:	/* Concatenate (Data1, Data2, Result) */

		status =
		    acpi_ex_do_concatenate(operand[0], operand[1], &return_desc,
					   walk_state);
		break;

	case AML_TO_STRING_OP:	/* to_string (Buffer, Length, Result) (ACPI 2.0) */
		/*
		 * Input object is guaranteed to be a buffer at this point (it may have
		 * been converted.)  Copy the raw buffer data to a new object of
		 * type String.
		 */

		/*
		 * Get the length of the new string. It is the smallest of:
		 * 1) Length of the input buffer
		 * 2) Max length as specified in the to_string operator
		 * 3) Length of input buffer up to a zero byte (null terminator)
		 *
		 * NOTE: A length of zero is ok, and will create a zero-length, null
		 *       terminated string.
		 */
		while ((length < operand[0]->buffer.length) &&	/* Length of input buffer */
		       (length < operand[1]->integer.value) &&	/* Length operand */
		       (operand[0]->buffer.pointer[length])) {	/* Null terminator */
			length++;
		}

		/* Allocate a new string object */

		return_desc = acpi_ut_create_string_object(length);
		if (!return_desc) {
			status = AE_NO_MEMORY;
			goto cleanup;
		}

		/*
		 * Copy the raw buffer data with no transform.
		 * (NULL terminated already)
		 */
		memcpy(return_desc->string.pointer,
		       operand[0]->buffer.pointer, length);
		break;

	case AML_CONCATENATE_TEMPLATE_OP:

		/* concatenate_res_template (Buffer, Buffer, Result) (ACPI 2.0) */

		status =
		    acpi_ex_concat_template(operand[0], operand[1],
					    &return_desc, walk_state);
		break;

	case AML_INDEX_OP:	/* Index (Source Index Result) */

		/* Create the internal return object */

		return_desc =
		    acpi_ut_create_internal_object(ACPI_TYPE_LOCAL_REFERENCE);
		if (!return_desc) {
			status = AE_NO_MEMORY;
			goto cleanup;
		}

		/* Initialize the Index reference object */

		index = operand[1]->integer.value;
		return_desc->reference.value = (u32) index;
		return_desc->reference.class = ACPI_REFCLASS_INDEX;

		/*
		 * At this point, the Source operand is a String, Buffer, or Package.
		 * Verify that the index is within range.
		 */
		switch ((operand[0])->common.type) {
		case ACPI_TYPE_STRING:

			if (index >= operand[0]->string.length) {
				length = operand[0]->string.length;
				status = AE_AML_STRING_LIMIT;
			}

			return_desc->reference.target_type =
			    ACPI_TYPE_BUFFER_FIELD;
			return_desc->reference.index_pointer =
			    &(operand[0]->buffer.pointer[index]);
			break;

		case ACPI_TYPE_BUFFER:

			if (index >= operand[0]->buffer.length) {
				length = operand[0]->buffer.length;
				status = AE_AML_BUFFER_LIMIT;
			}

			return_desc->reference.target_type =
			    ACPI_TYPE_BUFFER_FIELD;
			return_desc->reference.index_pointer =
			    &(operand[0]->buffer.pointer[index]);
			break;

		case ACPI_TYPE_PACKAGE:

			if (index >= operand[0]->package.count) {
				length = operand[0]->package.count;
				status = AE_AML_PACKAGE_LIMIT;
			}

			return_desc->reference.target_type = ACPI_TYPE_PACKAGE;
			return_desc->reference.where =
			    &operand[0]->package.elements[index];
			break;

		default:

			ACPI_ERROR((AE_INFO,
				    "Invalid object type: %X",
				    (operand[0])->common.type));
			status = AE_AML_INTERNAL;
			goto cleanup;
		}

		/* Failure means that the Index was beyond the end of the object */

		if (ACPI_FAILURE(status)) {
			ACPI_BIOS_EXCEPTION((AE_INFO, status,
					     "Index (0x%X%8.8X) is beyond end of object (length 0x%X)",
					     ACPI_FORMAT_UINT64(index),
					     (u32)length));
			goto cleanup;
		}

		/*
		 * Save the target object and add a reference to it for the life
		 * of the index
		 */
		return_desc->reference.object = operand[0];
		acpi_ut_add_reference(operand[0]);

		/* Store the reference to the Target */

		status = acpi_ex_store(return_desc, operand[2], walk_state);

		/* Return the reference */

		walk_state->result_obj = return_desc;
		goto cleanup;

	default:

		ACPI_ERROR((AE_INFO, "Unknown AML opcode 0x%X",
			    walk_state->opcode));
		status = AE_AML_BAD_OPCODE;
		break;
	}

store_result_to_target:

	if (ACPI_SUCCESS(status)) {
		/*
		 * Store the result of the operation (which is now in return_desc) into
		 * the Target descriptor.
		 */
		status = acpi_ex_store(return_desc, operand[2], walk_state);
		if (ACPI_FAILURE(status)) {
			goto cleanup;
		}

		if (!walk_state->result_obj) {
			walk_state->result_obj = return_desc;
		}
	}

cleanup:

	/* Delete return object on error */

	if (ACPI_FAILURE(status)) {
		acpi_ut_remove_reference(return_desc);
		walk_state->result_obj = NULL;
	}

	return_ACPI_STATUS(status);
}