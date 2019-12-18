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
struct TYPE_4__ {int /*<<< orphan*/  reference_count; } ;
union acpi_operand_object {TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct acpi_evaluate_info {int /*<<< orphan*/  return_flags; int /*<<< orphan*/  full_pathname; TYPE_3__* parent_package; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_5__ {int /*<<< orphan*/  reference_count; } ;
struct TYPE_6__ {TYPE_2__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_REPAIR ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_OBJECT_REPAIRED ; 
 int ACPI_RTYPE_BUFFER ; 
 int ACPI_RTYPE_INTEGER ; 
 int ACPI_RTYPE_STRING ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 union acpi_operand_object* acpi_ut_create_buffer_object (int /*<<< orphan*/ ) ; 
 union acpi_operand_object* acpi_ut_create_integer_object (int /*<<< orphan*/ ) ; 
 union acpi_operand_object* acpi_ut_create_string_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_get_object_type_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ns_repair_null_element ; 

acpi_status
acpi_ns_repair_null_element(struct acpi_evaluate_info *info,
			    u32 expected_btypes,
			    u32 package_index,
			    union acpi_operand_object **return_object_ptr)
{
	union acpi_operand_object *return_object = *return_object_ptr;
	union acpi_operand_object *new_object;

	ACPI_FUNCTION_NAME(ns_repair_null_element);

	/* No repair needed if return object is non-NULL */

	if (return_object) {
		return (AE_OK);
	}

	/*
	 * Attempt to repair a NULL element of a Package object. This applies to
	 * predefined names that return a fixed-length package and each element
	 * is required. It does not apply to variable-length packages where NULL
	 * elements are allowed, especially at the end of the package.
	 */
	if (expected_btypes & ACPI_RTYPE_INTEGER) {

		/* Need an integer - create a zero-value integer */

		new_object = acpi_ut_create_integer_object((u64)0);
	} else if (expected_btypes & ACPI_RTYPE_STRING) {

		/* Need a string - create a NULL string */

		new_object = acpi_ut_create_string_object(0);
	} else if (expected_btypes & ACPI_RTYPE_BUFFER) {

		/* Need a buffer - create a zero-length buffer */

		new_object = acpi_ut_create_buffer_object(0);
	} else {
		/* Error for all other expected types */

		return (AE_AML_OPERAND_TYPE);
	}

	if (!new_object) {
		return (AE_NO_MEMORY);
	}

	/* Set the reference count according to the parent Package object */

	new_object->common.reference_count =
	    info->parent_package->common.reference_count;

	ACPI_DEBUG_PRINT((ACPI_DB_REPAIR,
			  "%s: Converted NULL package element to expected %s at index %u\n",
			  info->full_pathname,
			  acpi_ut_get_object_type_name(new_object),
			  package_index));

	*return_object_ptr = new_object;
	info->return_flags |= ACPI_OBJECT_REPAIRED;
	return (AE_OK);
}