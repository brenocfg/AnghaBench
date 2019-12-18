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
struct TYPE_4__ {int /*<<< orphan*/  class; } ;
struct TYPE_3__ {int const type; } ;
union acpi_operand_object {TYPE_2__ reference; TYPE_1__ common; } ;
struct acpi_walk_state {int /*<<< orphan*/  opcode; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int acpi_object_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_REFCLASS_TABLE ; 
#define  ACPI_TYPE_BUFFER 137 
#define  ACPI_TYPE_BUFFER_FIELD 136 
#define  ACPI_TYPE_INTEGER 135 
#define  ACPI_TYPE_LOCAL_ALIAS 134 
#define  ACPI_TYPE_LOCAL_BANK_FIELD 133 
#define  ACPI_TYPE_LOCAL_INDEX_FIELD 132 
#define  ACPI_TYPE_LOCAL_METHOD_ALIAS 131 
 int const ACPI_TYPE_LOCAL_REFERENCE ; 
#define  ACPI_TYPE_LOCAL_REGION_FIELD 130 
#define  ACPI_TYPE_PACKAGE 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AML_COPY_OBJECT_OP ; 
 int /*<<< orphan*/  acpi_ex_resolve_to_value (union acpi_operand_object**,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ut_get_object_type_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (int) ; 
 int /*<<< orphan*/  ex_resolve_object ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_resolve_object(union acpi_operand_object **source_desc_ptr,
		       acpi_object_type target_type,
		       struct acpi_walk_state *walk_state)
{
	union acpi_operand_object *source_desc = *source_desc_ptr;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ex_resolve_object);

	/* Ensure we have a Target that can be stored to */

	switch (target_type) {
	case ACPI_TYPE_BUFFER_FIELD:
	case ACPI_TYPE_LOCAL_REGION_FIELD:
	case ACPI_TYPE_LOCAL_BANK_FIELD:
	case ACPI_TYPE_LOCAL_INDEX_FIELD:
		/*
		 * These cases all require only Integers or values that
		 * can be converted to Integers (Strings or Buffers)
		 */
	case ACPI_TYPE_INTEGER:
	case ACPI_TYPE_STRING:
	case ACPI_TYPE_BUFFER:
		/*
		 * Stores into a Field/Region or into a Integer/Buffer/String
		 * are all essentially the same. This case handles the
		 * "interchangeable" types Integer, String, and Buffer.
		 */
		if (source_desc->common.type == ACPI_TYPE_LOCAL_REFERENCE) {

			/* Resolve a reference object first */

			status =
			    acpi_ex_resolve_to_value(source_desc_ptr,
						     walk_state);
			if (ACPI_FAILURE(status)) {
				break;
			}
		}

		/* For copy_object, no further validation necessary */

		if (walk_state->opcode == AML_COPY_OBJECT_OP) {
			break;
		}

		/* Must have a Integer, Buffer, or String */

		if ((source_desc->common.type != ACPI_TYPE_INTEGER) &&
		    (source_desc->common.type != ACPI_TYPE_BUFFER) &&
		    (source_desc->common.type != ACPI_TYPE_STRING) &&
		    !((source_desc->common.type == ACPI_TYPE_LOCAL_REFERENCE) &&
		      (source_desc->reference.class == ACPI_REFCLASS_TABLE))) {

			/* Conversion successful but still not a valid type */

			ACPI_ERROR((AE_INFO,
				    "Cannot assign type [%s] to [%s] (must be type Int/Str/Buf)",
				    acpi_ut_get_object_type_name(source_desc),
				    acpi_ut_get_type_name(target_type)));

			status = AE_AML_OPERAND_TYPE;
		}
		break;

	case ACPI_TYPE_LOCAL_ALIAS:
	case ACPI_TYPE_LOCAL_METHOD_ALIAS:
		/*
		 * All aliases should have been resolved earlier, during the
		 * operand resolution phase.
		 */
		ACPI_ERROR((AE_INFO, "Store into an unresolved Alias object"));
		status = AE_AML_INTERNAL;
		break;

	case ACPI_TYPE_PACKAGE:
	default:
		/*
		 * All other types than Alias and the various Fields come here,
		 * including the untyped case - ACPI_TYPE_ANY.
		 */
		break;
	}

	return_ACPI_STATUS(status);
}