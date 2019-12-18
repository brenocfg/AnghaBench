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
struct TYPE_2__ {int /*<<< orphan*/  reference_count; } ;
union acpi_operand_object {TYPE_1__ common; } ;
typedef  int u32 ;
struct acpi_simple_repair_info {int /*<<< orphan*/  (* object_converter ) (int /*<<< orphan*/ ,union acpi_operand_object*,union acpi_operand_object**) ;} ;
struct acpi_evaluate_info {int return_btype; int return_flags; int /*<<< orphan*/  full_pathname; int /*<<< orphan*/  node; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_REPAIR ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int ACPI_NOT_PACKAGE_ELEMENT ; 
 int ACPI_OBJECT_REPAIRED ; 
 int ACPI_OBJECT_WRAPPED ; 
 int ACPI_RTYPE_BUFFER ; 
 int ACPI_RTYPE_INTEGER ; 
 int ACPI_RTYPE_NONE ; 
 int ACPI_RTYPE_PACKAGE ; 
 int ACPI_RTYPE_STRING ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_WARN_ALWAYS ; 
 int /*<<< orphan*/  ACPI_WARN_PREDEFINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_AML_NO_RETURN_VALUE ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ns_convert_to_buffer (union acpi_operand_object*,union acpi_operand_object**) ; 
 int /*<<< orphan*/  acpi_ns_convert_to_integer (union acpi_operand_object*,union acpi_operand_object**) ; 
 int /*<<< orphan*/  acpi_ns_convert_to_string (union acpi_operand_object*,union acpi_operand_object**) ; 
 struct acpi_simple_repair_info* acpi_ns_match_simple_repair (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  acpi_ns_repair_null_element (struct acpi_evaluate_info*,int,int,union acpi_operand_object**) ; 
 int /*<<< orphan*/  acpi_ns_wrap_with_package (struct acpi_evaluate_info*,union acpi_operand_object*,union acpi_operand_object**) ; 
 int /*<<< orphan*/  acpi_ut_get_object_type_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ns_simple_repair ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,union acpi_operand_object*,union acpi_operand_object**) ; 

acpi_status
acpi_ns_simple_repair(struct acpi_evaluate_info *info,
		      u32 expected_btypes,
		      u32 package_index,
		      union acpi_operand_object **return_object_ptr)
{
	union acpi_operand_object *return_object = *return_object_ptr;
	union acpi_operand_object *new_object = NULL;
	acpi_status status;
	const struct acpi_simple_repair_info *predefined;

	ACPI_FUNCTION_NAME(ns_simple_repair);

	/*
	 * Special repairs for certain names that are in the repair table.
	 * Check if this name is in the list of repairable names.
	 */
	predefined = acpi_ns_match_simple_repair(info->node,
						 info->return_btype,
						 package_index);
	if (predefined) {
		if (!return_object) {
			ACPI_WARN_PREDEFINED((AE_INFO, info->full_pathname,
					      ACPI_WARN_ALWAYS,
					      "Missing expected return value"));
		}

		status = predefined->object_converter(info->node, return_object,
						      &new_object);
		if (ACPI_FAILURE(status)) {

			/* A fatal error occurred during a conversion */

			ACPI_EXCEPTION((AE_INFO, status,
					"During return object analysis"));
			return (status);
		}
		if (new_object) {
			goto object_repaired;
		}
	}

	/*
	 * Do not perform simple object repair unless the return type is not
	 * expected.
	 */
	if (info->return_btype & expected_btypes) {
		return (AE_OK);
	}

	/*
	 * At this point, we know that the type of the returned object was not
	 * one of the expected types for this predefined name. Attempt to
	 * repair the object by converting it to one of the expected object
	 * types for this predefined name.
	 */

	/*
	 * If there is no return value, check if we require a return value for
	 * this predefined name. Either one return value is expected, or none,
	 * for both methods and other objects.
	 *
	 * Try to fix if there was no return object. Warning if failed to fix.
	 */
	if (!return_object) {
		if (expected_btypes && (!(expected_btypes & ACPI_RTYPE_NONE))) {
			if (package_index != ACPI_NOT_PACKAGE_ELEMENT) {
				ACPI_WARN_PREDEFINED((AE_INFO,
						      info->full_pathname,
						      ACPI_WARN_ALWAYS,
						      "Found unexpected NULL package element"));

				status =
				    acpi_ns_repair_null_element(info,
								expected_btypes,
								package_index,
								return_object_ptr);
				if (ACPI_SUCCESS(status)) {
					return (AE_OK);	/* Repair was successful */
				}
			} else {
				ACPI_WARN_PREDEFINED((AE_INFO,
						      info->full_pathname,
						      ACPI_WARN_ALWAYS,
						      "Missing expected return value"));
			}

			return (AE_AML_NO_RETURN_VALUE);
		}
	}

	if (expected_btypes & ACPI_RTYPE_INTEGER) {
		status = acpi_ns_convert_to_integer(return_object, &new_object);
		if (ACPI_SUCCESS(status)) {
			goto object_repaired;
		}
	}
	if (expected_btypes & ACPI_RTYPE_STRING) {
		status = acpi_ns_convert_to_string(return_object, &new_object);
		if (ACPI_SUCCESS(status)) {
			goto object_repaired;
		}
	}
	if (expected_btypes & ACPI_RTYPE_BUFFER) {
		status = acpi_ns_convert_to_buffer(return_object, &new_object);
		if (ACPI_SUCCESS(status)) {
			goto object_repaired;
		}
	}
	if (expected_btypes & ACPI_RTYPE_PACKAGE) {
		/*
		 * A package is expected. We will wrap the existing object with a
		 * new package object. It is often the case that if a variable-length
		 * package is required, but there is only a single object needed, the
		 * BIOS will return that object instead of wrapping it with a Package
		 * object. Note: after the wrapping, the package will be validated
		 * for correct contents (expected object type or types).
		 */
		status =
		    acpi_ns_wrap_with_package(info, return_object, &new_object);
		if (ACPI_SUCCESS(status)) {
			/*
			 * The original object just had its reference count
			 * incremented for being inserted into the new package.
			 */
			*return_object_ptr = new_object;	/* New Package object */
			info->return_flags |= ACPI_OBJECT_REPAIRED;
			return (AE_OK);
		}
	}

	/* We cannot repair this object */

	return (AE_AML_OPERAND_TYPE);

object_repaired:

	/* Object was successfully repaired */

	if (package_index != ACPI_NOT_PACKAGE_ELEMENT) {

		/* Update reference count of new object */

		if (!(info->return_flags & ACPI_OBJECT_WRAPPED)) {
			new_object->common.reference_count =
			    return_object->common.reference_count;
		}

		ACPI_DEBUG_PRINT((ACPI_DB_REPAIR,
				  "%s: Converted %s to expected %s at Package index %u\n",
				  info->full_pathname,
				  acpi_ut_get_object_type_name(return_object),
				  acpi_ut_get_object_type_name(new_object),
				  package_index));
	} else {
		ACPI_DEBUG_PRINT((ACPI_DB_REPAIR,
				  "%s: Converted %s to expected %s\n",
				  info->full_pathname,
				  acpi_ut_get_object_type_name(return_object),
				  acpi_ut_get_object_type_name(new_object)));
	}

	/* Delete old object, install the new return object */

	acpi_ut_remove_reference(return_object);
	*return_object_ptr = new_object;
	info->return_flags |= ACPI_OBJECT_REPAIRED;
	return (AE_OK);
}