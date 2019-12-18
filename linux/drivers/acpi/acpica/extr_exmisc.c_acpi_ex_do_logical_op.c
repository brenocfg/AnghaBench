#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ length; int /*<<< orphan*/  pointer; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
struct TYPE_4__ {int type; } ;
union acpi_operand_object {TYPE_3__ buffer; TYPE_2__ integer; TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_IMPLICIT_CONVERSION ; 
 int /*<<< orphan*/  ACPI_IMPLICIT_CONVERT_HEX ; 
#define  ACPI_TYPE_BUFFER 133 
#define  ACPI_TYPE_INTEGER 132 
#define  ACPI_TYPE_STRING 131 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_LOGICAL_EQUAL_OP 130 
#define  AML_LOGICAL_GREATER_OP 129 
#define  AML_LOGICAL_LESS_OP 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_ex_convert_to_buffer (union acpi_operand_object*,union acpi_operand_object**) ; 
 int /*<<< orphan*/  acpi_ex_convert_to_integer (union acpi_operand_object*,union acpi_operand_object**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_convert_to_string (union acpi_operand_object*,union acpi_operand_object**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ex_do_logical_op ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_do_logical_op(u16 opcode,
		      union acpi_operand_object *operand0,
		      union acpi_operand_object *operand1, u8 * logical_result)
{
	union acpi_operand_object *local_operand1 = operand1;
	u64 integer0;
	u64 integer1;
	u32 length0;
	u32 length1;
	acpi_status status = AE_OK;
	u8 local_result = FALSE;
	int compare;

	ACPI_FUNCTION_TRACE(ex_do_logical_op);

	/*
	 * Convert the second operand if necessary. The first operand
	 * determines the type of the second operand, (See the Data Types
	 * section of the ACPI 3.0+ specification.)  Both object types are
	 * guaranteed to be either Integer/String/Buffer by the operand
	 * resolution mechanism.
	 */
	switch (operand0->common.type) {
	case ACPI_TYPE_INTEGER:

		status = acpi_ex_convert_to_integer(operand1, &local_operand1,
						    ACPI_IMPLICIT_CONVERSION);
		break;

	case ACPI_TYPE_STRING:

		status =
		    acpi_ex_convert_to_string(operand1, &local_operand1,
					      ACPI_IMPLICIT_CONVERT_HEX);
		break;

	case ACPI_TYPE_BUFFER:

		status = acpi_ex_convert_to_buffer(operand1, &local_operand1);
		break;

	default:

		ACPI_ERROR((AE_INFO,
			    "Invalid object type for logical operator: %X",
			    operand0->common.type));
		status = AE_AML_INTERNAL;
		break;
	}

	if (ACPI_FAILURE(status)) {
		goto cleanup;
	}

	/*
	 * Two cases: 1) Both Integers, 2) Both Strings or Buffers
	 */
	if (operand0->common.type == ACPI_TYPE_INTEGER) {
		/*
		 * 1) Both operands are of type integer
		 *    Note: local_operand1 may have changed above
		 */
		integer0 = operand0->integer.value;
		integer1 = local_operand1->integer.value;

		switch (opcode) {
		case AML_LOGICAL_EQUAL_OP:	/* LEqual (Operand0, Operand1) */

			if (integer0 == integer1) {
				local_result = TRUE;
			}
			break;

		case AML_LOGICAL_GREATER_OP:	/* LGreater (Operand0, Operand1) */

			if (integer0 > integer1) {
				local_result = TRUE;
			}
			break;

		case AML_LOGICAL_LESS_OP:	/* LLess (Operand0, Operand1) */

			if (integer0 < integer1) {
				local_result = TRUE;
			}
			break;

		default:

			ACPI_ERROR((AE_INFO,
				    "Invalid comparison opcode: %X", opcode));
			status = AE_AML_INTERNAL;
			break;
		}
	} else {
		/*
		 * 2) Both operands are Strings or both are Buffers
		 *    Note: Code below takes advantage of common Buffer/String
		 *          object fields. local_operand1 may have changed above. Use
		 *          memcmp to handle nulls in buffers.
		 */
		length0 = operand0->buffer.length;
		length1 = local_operand1->buffer.length;

		/* Lexicographic compare: compare the data bytes */

		compare = memcmp(operand0->buffer.pointer,
				 local_operand1->buffer.pointer,
				 (length0 > length1) ? length1 : length0);

		switch (opcode) {
		case AML_LOGICAL_EQUAL_OP:	/* LEqual (Operand0, Operand1) */

			/* Length and all bytes must be equal */

			if ((length0 == length1) && (compare == 0)) {

				/* Length and all bytes match ==> TRUE */

				local_result = TRUE;
			}
			break;

		case AML_LOGICAL_GREATER_OP:	/* LGreater (Operand0, Operand1) */

			if (compare > 0) {
				local_result = TRUE;
				goto cleanup;	/* TRUE */
			}
			if (compare < 0) {
				goto cleanup;	/* FALSE */
			}

			/* Bytes match (to shortest length), compare lengths */

			if (length0 > length1) {
				local_result = TRUE;
			}
			break;

		case AML_LOGICAL_LESS_OP:	/* LLess (Operand0, Operand1) */

			if (compare > 0) {
				goto cleanup;	/* FALSE */
			}
			if (compare < 0) {
				local_result = TRUE;
				goto cleanup;	/* TRUE */
			}

			/* Bytes match (to shortest length), compare lengths */

			if (length0 < length1) {
				local_result = TRUE;
			}
			break;

		default:

			ACPI_ERROR((AE_INFO,
				    "Invalid comparison opcode: %X", opcode));
			status = AE_AML_INTERNAL;
			break;
		}
	}

cleanup:

	/* New object was created if implicit conversion performed - delete */

	if (local_operand1 != operand1) {
		acpi_ut_remove_reference(local_operand1);
	}

	/* Return the logical result and status */

	*logical_result = local_result;
	return_ACPI_STATUS(status);
}