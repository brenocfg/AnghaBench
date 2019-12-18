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
struct TYPE_6__ {scalar_t__ value; } ;
struct TYPE_5__ {scalar_t__ count; union acpi_operand_object** elements; } ;
struct TYPE_4__ {scalar_t__ type; } ;
union acpi_operand_object {TYPE_3__ integer; TYPE_2__ package; TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct acpi_evaluate_info {int /*<<< orphan*/  full_pathname; int /*<<< orphan*/  return_flags; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_REPAIR ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_OBJECT_REPAIRED ; 
 int /*<<< orphan*/  ACPI_SORT_ASCENDING ; 
 int /*<<< orphan*/  ACPI_SORT_DESCENDING ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 scalar_t__ ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_AML_PACKAGE_LIMIT ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ns_sort_list (union acpi_operand_object**,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_check_sorted_list ; 

__attribute__((used)) static acpi_status
acpi_ns_check_sorted_list(struct acpi_evaluate_info *info,
			  union acpi_operand_object *return_object,
			  u32 start_index,
			  u32 expected_count,
			  u32 sort_index,
			  u8 sort_direction, char *sort_key_name)
{
	u32 outer_element_count;
	union acpi_operand_object **outer_elements;
	union acpi_operand_object **elements;
	union acpi_operand_object *obj_desc;
	u32 i;
	u32 previous_value;

	ACPI_FUNCTION_NAME(ns_check_sorted_list);

	/* The top-level object must be a package */

	if (return_object->common.type != ACPI_TYPE_PACKAGE) {
		return (AE_AML_OPERAND_TYPE);
	}

	/*
	 * NOTE: assumes list of subpackages contains no NULL elements.
	 * Any NULL elements should have been removed by earlier call
	 * to acpi_ns_remove_null_elements.
	 */
	outer_element_count = return_object->package.count;
	if (!outer_element_count || start_index >= outer_element_count) {
		return (AE_AML_PACKAGE_LIMIT);
	}

	outer_elements = &return_object->package.elements[start_index];
	outer_element_count -= start_index;

	previous_value = 0;
	if (sort_direction == ACPI_SORT_DESCENDING) {
		previous_value = ACPI_UINT32_MAX;
	}

	/* Examine each subpackage */

	for (i = 0; i < outer_element_count; i++) {

		/* Each element of the top-level package must also be a package */

		if ((*outer_elements)->common.type != ACPI_TYPE_PACKAGE) {
			return (AE_AML_OPERAND_TYPE);
		}

		/* Each subpackage must have the minimum length */

		if ((*outer_elements)->package.count < expected_count) {
			return (AE_AML_PACKAGE_LIMIT);
		}

		elements = (*outer_elements)->package.elements;
		obj_desc = elements[sort_index];

		if (obj_desc->common.type != ACPI_TYPE_INTEGER) {
			return (AE_AML_OPERAND_TYPE);
		}

		/*
		 * The list must be sorted in the specified order. If we detect a
		 * discrepancy, sort the entire list.
		 */
		if (((sort_direction == ACPI_SORT_ASCENDING) &&
		     (obj_desc->integer.value < previous_value)) ||
		    ((sort_direction == ACPI_SORT_DESCENDING) &&
		     (obj_desc->integer.value > previous_value))) {
			acpi_ns_sort_list(&return_object->package.
					  elements[start_index],
					  outer_element_count, sort_index,
					  sort_direction);

			info->return_flags |= ACPI_OBJECT_REPAIRED;

			ACPI_DEBUG_PRINT((ACPI_DB_REPAIR,
					  "%s: Repaired unsorted list - now sorted by %s\n",
					  info->full_pathname, sort_key_name));
			return (AE_OK);
		}

		previous_value = (u32) obj_desc->integer.value;
		outer_elements++;
	}

	return (AE_OK);
}