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
struct TYPE_2__ {int flags; } ;
union acpi_operand_object {TYPE_1__ package; } ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  acpi_ds_get_package_arguments (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ds_init_package_element ; 
 union acpi_operand_object* acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ut_walk_package_tree (union acpi_operand_object*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

acpi_status
acpi_ns_init_one_package(acpi_handle obj_handle,
			 u32 level, void *context, void **return_value)
{
	acpi_status status;
	union acpi_operand_object *obj_desc;
	struct acpi_namespace_node *node =
	    (struct acpi_namespace_node *)obj_handle;

	obj_desc = acpi_ns_get_attached_object(node);
	if (!obj_desc) {
		return (AE_OK);
	}

	/* Exit if package is already initialized */

	if (obj_desc->package.flags & AOPOBJ_DATA_VALID) {
		return (AE_OK);
	}

	status = acpi_ds_get_package_arguments(obj_desc);
	if (ACPI_FAILURE(status)) {
		return (AE_OK);
	}

	status =
	    acpi_ut_walk_package_tree(obj_desc, NULL,
				      acpi_ds_init_package_element, NULL);
	if (ACPI_FAILURE(status)) {
		return (AE_OK);
	}

	obj_desc->package.flags |= AOPOBJ_DATA_VALID;
	return (AE_OK);
}