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
struct TYPE_6__ {struct acpi_namespace_node* node; scalar_t__ sync_level; int /*<<< orphan*/  os_mutex; } ;
union acpi_operand_object {TYPE_3__ mutex; } ;
typedef  scalar_t__ u8 ;
struct acpi_walk_state {TYPE_2__** operands; } ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_4__ {scalar_t__ value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_MUTEX ; 
 int /*<<< orphan*/  ACPI_WALK_OPERANDS ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ns_attach_object (struct acpi_namespace_node*,union acpi_operand_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_create_mutex (int /*<<< orphan*/ *) ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ex_create_mutex ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ex_create_mutex(struct acpi_walk_state *walk_state)
{
	acpi_status status = AE_OK;
	union acpi_operand_object *obj_desc;

	ACPI_FUNCTION_TRACE_PTR(ex_create_mutex, ACPI_WALK_OPERANDS);

	/* Create the new mutex object */

	obj_desc = acpi_ut_create_internal_object(ACPI_TYPE_MUTEX);
	if (!obj_desc) {
		status = AE_NO_MEMORY;
		goto cleanup;
	}

	/* Create the actual OS Mutex */

	status = acpi_os_create_mutex(&obj_desc->mutex.os_mutex);
	if (ACPI_FAILURE(status)) {
		goto cleanup;
	}

	/* Init object and attach to NS node */

	obj_desc->mutex.sync_level = (u8)walk_state->operands[1]->integer.value;
	obj_desc->mutex.node =
	    (struct acpi_namespace_node *)walk_state->operands[0];

	status =
	    acpi_ns_attach_object(obj_desc->mutex.node, obj_desc,
				  ACPI_TYPE_MUTEX);

cleanup:
	/*
	 * Remove local reference to the object (on error, will cause deletion
	 * of both object and semaphore if present.)
	 */
	acpi_ut_remove_reference(obj_desc);
	return_ACPI_STATUS(status);
}