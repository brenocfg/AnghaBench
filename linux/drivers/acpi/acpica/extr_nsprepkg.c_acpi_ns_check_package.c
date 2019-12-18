#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int type; size_t count1; size_t count2; int /*<<< orphan*/  object_type2; int /*<<< orphan*/  object_type1; } ;
struct TYPE_7__ {size_t count; int /*<<< orphan*/  tail_object_type; int /*<<< orphan*/ * object_type; } ;
union acpi_predefined_info {TYPE_6__ ret_info; TYPE_1__ ret_info3; } ;
struct TYPE_11__ {int length; } ;
struct TYPE_10__ {size_t count; union acpi_operand_object** elements; } ;
struct TYPE_9__ {int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int /*<<< orphan*/  value; } ;
union acpi_operand_object {TYPE_5__ buffer; TYPE_4__ package; TYPE_3__ common; TYPE_2__ integer; } ;
typedef  size_t u32 ;
struct acpi_evaluate_info {int /*<<< orphan*/  node_flags; int /*<<< orphan*/  full_pathname; union acpi_predefined_info* predefined; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_NAMES ; 
 int /*<<< orphan*/  ACPI_DB_REPAIR ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
#define  ACPI_PTYPE1_FIXED 140 
#define  ACPI_PTYPE1_OPTION 139 
#define  ACPI_PTYPE1_VAR 138 
#define  ACPI_PTYPE2 137 
#define  ACPI_PTYPE2_COUNT 136 
#define  ACPI_PTYPE2_FIXED 135 
#define  ACPI_PTYPE2_FIX_VAR 134 
#define  ACPI_PTYPE2_MIN 133 
#define  ACPI_PTYPE2_PKG_COUNT 132 
#define  ACPI_PTYPE2_REV_FIXED 131 
#define  ACPI_PTYPE2_UUID_PAIR 130 
#define  ACPI_PTYPE2_VAR_VAR 129 
#define  ACPI_PTYPE_CUSTOM 128 
 int /*<<< orphan*/  ACPI_RTYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  ACPI_WARN_PREDEFINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_AML_OPERAND_VALUE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ns_check_object_type (struct acpi_evaluate_info*,union acpi_operand_object**,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  acpi_ns_check_package_elements (struct acpi_evaluate_info*,union acpi_operand_object**,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ns_check_package_list (struct acpi_evaluate_info*,union acpi_predefined_info const*,union acpi_operand_object**,size_t) ; 
 int /*<<< orphan*/  acpi_ns_custom_package (struct acpi_evaluate_info*,union acpi_operand_object**,size_t) ; 
 int /*<<< orphan*/  acpi_ns_remove_null_elements (struct acpi_evaluate_info*,int,union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ns_wrap_with_package (struct acpi_evaluate_info*,union acpi_operand_object*,union acpi_operand_object**) ; 
 int /*<<< orphan*/  ns_check_package ; 

acpi_status
acpi_ns_check_package(struct acpi_evaluate_info *info,
		      union acpi_operand_object **return_object_ptr)
{
	union acpi_operand_object *return_object = *return_object_ptr;
	const union acpi_predefined_info *package;
	union acpi_operand_object **elements;
	acpi_status status = AE_OK;
	u32 expected_count;
	u32 count;
	u32 i;

	ACPI_FUNCTION_NAME(ns_check_package);

	/* The package info for this name is in the next table entry */

	package = info->predefined + 1;

	ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
			  "%s Validating return Package of Type %X, Count %X\n",
			  info->full_pathname, package->ret_info.type,
			  return_object->package.count));

	/*
	 * For variable-length Packages, we can safely remove all embedded
	 * and trailing NULL package elements
	 */
	acpi_ns_remove_null_elements(info, package->ret_info.type,
				     return_object);

	/* Extract package count and elements array */

	elements = return_object->package.elements;
	count = return_object->package.count;

	/*
	 * Most packages must have at least one element. The only exception
	 * is the variable-length package (ACPI_PTYPE1_VAR).
	 */
	if (!count) {
		if (package->ret_info.type == ACPI_PTYPE1_VAR) {
			return (AE_OK);
		}

		ACPI_WARN_PREDEFINED((AE_INFO, info->full_pathname,
				      info->node_flags,
				      "Return Package has no elements (empty)"));

		return (AE_AML_OPERAND_VALUE);
	}

	/*
	 * Decode the type of the expected package contents
	 *
	 * PTYPE1 packages contain no subpackages
	 * PTYPE2 packages contain subpackages
	 */
	switch (package->ret_info.type) {
	case ACPI_PTYPE_CUSTOM:

		status = acpi_ns_custom_package(info, elements, count);
		break;

	case ACPI_PTYPE1_FIXED:
		/*
		 * The package count is fixed and there are no subpackages
		 *
		 * If package is too small, exit.
		 * If package is larger than expected, issue warning but continue
		 */
		expected_count =
		    package->ret_info.count1 + package->ret_info.count2;
		if (count < expected_count) {
			goto package_too_small;
		} else if (count > expected_count) {
			ACPI_DEBUG_PRINT((ACPI_DB_REPAIR,
					  "%s: Return Package is larger than needed - "
					  "found %u, expected %u\n",
					  info->full_pathname, count,
					  expected_count));
		}

		/* Validate all elements of the returned package */

		status = acpi_ns_check_package_elements(info, elements,
							package->ret_info.
							object_type1,
							package->ret_info.
							count1,
							package->ret_info.
							object_type2,
							package->ret_info.
							count2, 0);
		break;

	case ACPI_PTYPE1_VAR:
		/*
		 * The package count is variable, there are no subpackages, and all
		 * elements must be of the same type
		 */
		for (i = 0; i < count; i++) {
			status = acpi_ns_check_object_type(info, elements,
							   package->ret_info.
							   object_type1, i);
			if (ACPI_FAILURE(status)) {
				return (status);
			}

			elements++;
		}
		break;

	case ACPI_PTYPE1_OPTION:
		/*
		 * The package count is variable, there are no subpackages. There are
		 * a fixed number of required elements, and a variable number of
		 * optional elements.
		 *
		 * Check if package is at least as large as the minimum required
		 */
		expected_count = package->ret_info3.count;
		if (count < expected_count) {
			goto package_too_small;
		}

		/* Variable number of sub-objects */

		for (i = 0; i < count; i++) {
			if (i < package->ret_info3.count) {

				/* These are the required package elements (0, 1, or 2) */

				status =
				    acpi_ns_check_object_type(info, elements,
							      package->
							      ret_info3.
							      object_type[i],
							      i);
				if (ACPI_FAILURE(status)) {
					return (status);
				}
			} else {
				/* These are the optional package elements */

				status =
				    acpi_ns_check_object_type(info, elements,
							      package->
							      ret_info3.
							      tail_object_type,
							      i);
				if (ACPI_FAILURE(status)) {
					return (status);
				}
			}

			elements++;
		}
		break;

	case ACPI_PTYPE2_REV_FIXED:

		/* First element is the (Integer) revision */

		status =
		    acpi_ns_check_object_type(info, elements,
					      ACPI_RTYPE_INTEGER, 0);
		if (ACPI_FAILURE(status)) {
			return (status);
		}

		elements++;
		count--;

		/* Examine the subpackages */

		status =
		    acpi_ns_check_package_list(info, package, elements, count);
		break;

	case ACPI_PTYPE2_PKG_COUNT:

		/* First element is the (Integer) count of subpackages to follow */

		status =
		    acpi_ns_check_object_type(info, elements,
					      ACPI_RTYPE_INTEGER, 0);
		if (ACPI_FAILURE(status)) {
			return (status);
		}

		/*
		 * Count cannot be larger than the parent package length, but allow it
		 * to be smaller. The >= accounts for the Integer above.
		 */
		expected_count = (u32)(*elements)->integer.value;
		if (expected_count >= count) {
			goto package_too_small;
		}

		count = expected_count;
		elements++;

		/* Examine the subpackages */

		status =
		    acpi_ns_check_package_list(info, package, elements, count);
		break;

	case ACPI_PTYPE2:
	case ACPI_PTYPE2_FIXED:
	case ACPI_PTYPE2_MIN:
	case ACPI_PTYPE2_COUNT:
	case ACPI_PTYPE2_FIX_VAR:
		/*
		 * These types all return a single Package that consists of a
		 * variable number of subpackages.
		 *
		 * First, ensure that the first element is a subpackage. If not,
		 * the BIOS may have incorrectly returned the object as a single
		 * package instead of a Package of Packages (a common error if
		 * there is only one entry). We may be able to repair this by
		 * wrapping the returned Package with a new outer Package.
		 */
		if (*elements
		    && ((*elements)->common.type != ACPI_TYPE_PACKAGE)) {

			/* Create the new outer package and populate it */

			status =
			    acpi_ns_wrap_with_package(info, return_object,
						      return_object_ptr);
			if (ACPI_FAILURE(status)) {
				return (status);
			}

			/* Update locals to point to the new package (of 1 element) */

			return_object = *return_object_ptr;
			elements = return_object->package.elements;
			count = 1;
		}

		/* Examine the subpackages */

		status =
		    acpi_ns_check_package_list(info, package, elements, count);
		break;

	case ACPI_PTYPE2_VAR_VAR:
		/*
		 * Returns a variable list of packages, each with a variable list
		 * of objects.
		 */
		break;

	case ACPI_PTYPE2_UUID_PAIR:

		/* The package must contain pairs of (UUID + type) */

		if (count & 1) {
			expected_count = count + 1;
			goto package_too_small;
		}

		while (count > 0) {
			status = acpi_ns_check_object_type(info, elements,
							   package->ret_info.
							   object_type1, 0);
			if (ACPI_FAILURE(status)) {
				return (status);
			}

			/* Validate length of the UUID buffer */

			if ((*elements)->buffer.length != 16) {
				ACPI_WARN_PREDEFINED((AE_INFO,
						      info->full_pathname,
						      info->node_flags,
						      "Invalid length for UUID Buffer"));
				return (AE_AML_OPERAND_VALUE);
			}

			status = acpi_ns_check_object_type(info, elements + 1,
							   package->ret_info.
							   object_type2, 0);
			if (ACPI_FAILURE(status)) {
				return (status);
			}

			elements += 2;
			count -= 2;
		}
		break;

	default:

		/* Should not get here if predefined info table is correct */

		ACPI_WARN_PREDEFINED((AE_INFO, info->full_pathname,
				      info->node_flags,
				      "Invalid internal return type in table entry: %X",
				      package->ret_info.type));

		return (AE_AML_INTERNAL);
	}

	return (status);

package_too_small:

	/* Error exit for the case with an incorrect package count */

	ACPI_WARN_PREDEFINED((AE_INFO, info->full_pathname, info->node_flags,
			      "Return Package is too small - found %u elements, expected %u",
			      count, expected_count));

	return (AE_AML_OPERAND_VALUE);
}