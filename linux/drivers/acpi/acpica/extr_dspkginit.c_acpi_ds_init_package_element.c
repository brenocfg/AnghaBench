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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {scalar_t__ type; } ;
union acpi_operand_object {TYPE_1__ package; TYPE_3__ common; } ;
struct TYPE_5__ {union acpi_operand_object** this_target_obj; } ;
union acpi_generic_state {TYPE_2__ pkg; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_LOCAL_REFERENCE ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  acpi_ds_resolve_package_element (union acpi_operand_object**) ; 
 int /*<<< orphan*/  ds_init_package_element ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_init_package_element(u8 object_type,
			     union acpi_operand_object *source_object,
			     union acpi_generic_state *state, void *context)
{
	union acpi_operand_object **element_ptr;

	ACPI_FUNCTION_TRACE(ds_init_package_element);

	if (!source_object) {
		return_ACPI_STATUS(AE_OK);
	}

	/*
	 * The following code is a bit of a hack to workaround a (current)
	 * limitation of the acpi_pkg_callback interface. We need a pointer
	 * to the location within the element array because a new object
	 * may be created and stored there.
	 */
	if (context) {

		/* A direct call was made to this function */

		element_ptr = (union acpi_operand_object **)context;
	} else {
		/* Call came from acpi_ut_walk_package_tree */

		element_ptr = state->pkg.this_target_obj;
	}

	/* We are only interested in reference objects/elements */

	if (source_object->common.type == ACPI_TYPE_LOCAL_REFERENCE) {

		/* Attempt to resolve the (named) reference to a namespace node */

		acpi_ds_resolve_package_element(element_ptr);
	} else if (source_object->common.type == ACPI_TYPE_PACKAGE) {
		source_object->package.flags |= AOPOBJ_DATA_VALID;
	}

	return_ACPI_STATUS(AE_OK);
}