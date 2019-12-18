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
struct TYPE_2__ {int reference_count; scalar_t__ type; union acpi_operand_object* next_object; } ;
union acpi_operand_object {TYPE_1__ common; } ;
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int acpi_object_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_STR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  ACPI_TYPE_BUFFER_FIELD 130 
#define  ACPI_TYPE_LOCAL_BANK_FIELD 129 
 scalar_t__ ACPI_TYPE_LOCAL_EXTRA ; 
#define  ACPI_TYPE_REGION 128 
 union acpi_operand_object* acpi_ut_allocate_object_desc_dbg (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_delete_object_desc (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (int) ; 
 int /*<<< orphan*/  kmemleak_not_leak (union acpi_operand_object*) ; 
 int /*<<< orphan*/  return_PTR (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ut_create_internal_object_dbg ; 

union acpi_operand_object *acpi_ut_create_internal_object_dbg(const char
							      *module_name,
							      u32 line_number,
							      u32 component_id,
							      acpi_object_type
							      type)
{
	union acpi_operand_object *object;
	union acpi_operand_object *second_object;

	ACPI_FUNCTION_TRACE_STR(ut_create_internal_object_dbg,
				acpi_ut_get_type_name(type));

	/* Allocate the raw object descriptor */

	object =
	    acpi_ut_allocate_object_desc_dbg(module_name, line_number,
					     component_id);
	if (!object) {
		return_PTR(NULL);
	}
	kmemleak_not_leak(object);

	switch (type) {
	case ACPI_TYPE_REGION:
	case ACPI_TYPE_BUFFER_FIELD:
	case ACPI_TYPE_LOCAL_BANK_FIELD:

		/* These types require a secondary object */

		second_object =
		    acpi_ut_allocate_object_desc_dbg(module_name, line_number,
						     component_id);
		if (!second_object) {
			acpi_ut_delete_object_desc(object);
			return_PTR(NULL);
		}

		second_object->common.type = ACPI_TYPE_LOCAL_EXTRA;
		second_object->common.reference_count = 1;

		/* Link the second object to the first */

		object->common.next_object = second_object;
		break;

	default:

		/* All others have no secondary object */
		break;
	}

	/* Save the object type in the object descriptor */

	object->common.type = (u8) type;

	/* Init the reference count */

	object->common.reference_count = 1;

	/* Any per-type initialization should go here */

	return_PTR(object);
}