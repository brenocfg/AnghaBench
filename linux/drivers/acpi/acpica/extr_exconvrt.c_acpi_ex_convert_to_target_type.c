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
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
union acpi_operand_object {TYPE_1__ common; } ;
struct acpi_walk_state {int /*<<< orphan*/  opcode; TYPE_2__* op_info; } ;
typedef  scalar_t__ acpi_status ;
typedef  int /*<<< orphan*/  acpi_object_type ;
struct TYPE_4__ {int /*<<< orphan*/  runtime_args; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_IMPLICIT_CONVERSION ; 
 int /*<<< orphan*/  ACPI_IMPLICIT_CONVERT_HEX ; 
#define  ACPI_TYPE_BUFFER 140 
#define  ACPI_TYPE_BUFFER_FIELD 139 
#define  ACPI_TYPE_INTEGER 138 
#define  ACPI_TYPE_LOCAL_BANK_FIELD 137 
#define  ACPI_TYPE_LOCAL_INDEX_FIELD 136 
#define  ACPI_TYPE_LOCAL_REGION_FIELD 135 
#define  ACPI_TYPE_STRING 134 
 scalar_t__ AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_OK ; 
 scalar_t__ AE_TYPE ; 
#define  ARGI_FIXED_TARGET 133 
#define  ARGI_INTEGER_REF 132 
#define  ARGI_REFERENCE 131 
#define  ARGI_SIMPLE_TARGET 130 
#define  ARGI_STORE_TARGET 129 
#define  ARGI_TARGETREF 128 
 int GET_CURRENT_ARG_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_ex_convert_to_buffer (union acpi_operand_object*,union acpi_operand_object**) ; 
 scalar_t__ acpi_ex_convert_to_integer (union acpi_operand_object*,union acpi_operand_object**,int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_ex_convert_to_string (union acpi_operand_object*,union acpi_operand_object**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_get_object_type_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_convert_to_target_type ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

acpi_status
acpi_ex_convert_to_target_type(acpi_object_type destination_type,
			       union acpi_operand_object *source_desc,
			       union acpi_operand_object **result_desc,
			       struct acpi_walk_state *walk_state)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ex_convert_to_target_type);

	/* Default behavior */

	*result_desc = source_desc;

	/*
	 * If required by the target,
	 * perform implicit conversion on the source before we store it.
	 */
	switch (GET_CURRENT_ARG_TYPE(walk_state->op_info->runtime_args)) {
	case ARGI_SIMPLE_TARGET:
	case ARGI_FIXED_TARGET:
	case ARGI_INTEGER_REF:	/* Handles Increment, Decrement cases */

		switch (destination_type) {
		case ACPI_TYPE_LOCAL_REGION_FIELD:
			/*
			 * Named field can always handle conversions
			 */
			break;

		default:

			/* No conversion allowed for these types */

			if (destination_type != source_desc->common.type) {
				ACPI_DEBUG_PRINT((ACPI_DB_INFO,
						  "Explicit operator, will store (%s) over existing type (%s)\n",
						  acpi_ut_get_object_type_name
						  (source_desc),
						  acpi_ut_get_type_name
						  (destination_type)));
				status = AE_TYPE;
			}
		}
		break;

	case ARGI_TARGETREF:
	case ARGI_STORE_TARGET:

		switch (destination_type) {
		case ACPI_TYPE_INTEGER:
		case ACPI_TYPE_BUFFER_FIELD:
		case ACPI_TYPE_LOCAL_BANK_FIELD:
		case ACPI_TYPE_LOCAL_INDEX_FIELD:
			/*
			 * These types require an Integer operand. We can convert
			 * a Buffer or a String to an Integer if necessary.
			 */
			status =
			    acpi_ex_convert_to_integer(source_desc, result_desc,
						       ACPI_IMPLICIT_CONVERSION);
			break;

		case ACPI_TYPE_STRING:
			/*
			 * The operand must be a String. We can convert an
			 * Integer or Buffer if necessary
			 */
			status =
			    acpi_ex_convert_to_string(source_desc, result_desc,
						      ACPI_IMPLICIT_CONVERT_HEX);
			break;

		case ACPI_TYPE_BUFFER:
			/*
			 * The operand must be a Buffer. We can convert an
			 * Integer or String if necessary
			 */
			status =
			    acpi_ex_convert_to_buffer(source_desc, result_desc);
			break;

		default:

			ACPI_ERROR((AE_INFO,
				    "Bad destination type during conversion: 0x%X",
				    destination_type));
			status = AE_AML_INTERNAL;
			break;
		}
		break;

	case ARGI_REFERENCE:
		/*
		 * create_xxxx_field cases - we are storing the field object into the name
		 */
		break;

	default:

		ACPI_ERROR((AE_INFO,
			    "Unknown Target type ID 0x%X AmlOpcode 0x%X DestType %s",
			    GET_CURRENT_ARG_TYPE(walk_state->op_info->
						 runtime_args),
			    walk_state->opcode,
			    acpi_ut_get_type_name(destination_type)));
		status = AE_AML_INTERNAL;
	}

	/*
	 * Source-to-Target conversion semantics:
	 *
	 * If conversion to the target type cannot be performed, then simply
	 * overwrite the target with the new object and type.
	 */
	if (status == AE_TYPE) {
		status = AE_OK;
	}

	return_ACPI_STATUS(status);
}