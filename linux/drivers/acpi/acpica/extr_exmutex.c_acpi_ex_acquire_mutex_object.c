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
struct TYPE_2__ {scalar_t__ thread_id; int acquisition_depth; int /*<<< orphan*/ * owner_thread; scalar_t__ original_sync_level; int /*<<< orphan*/  os_mutex; } ;
union acpi_operand_object {TYPE_1__ mutex; } ;
typedef  int /*<<< orphan*/  u16 ;
typedef  scalar_t__ acpi_thread_id ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ev_acquire_global_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_system_wait_mutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 union acpi_operand_object* acpi_gbl_global_lock_mutex ; 
 int /*<<< orphan*/  ex_acquire_mutex_object ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_acquire_mutex_object(u16 timeout,
			     union acpi_operand_object *obj_desc,
			     acpi_thread_id thread_id)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ex_acquire_mutex_object, obj_desc);

	if (!obj_desc) {
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	/* Support for multiple acquires by the owning thread */

	if (obj_desc->mutex.thread_id == thread_id) {
		/*
		 * The mutex is already owned by this thread, just increment the
		 * acquisition depth
		 */
		obj_desc->mutex.acquisition_depth++;
		return_ACPI_STATUS(AE_OK);
	}

	/* Acquire the mutex, wait if necessary. Special case for Global Lock */

	if (obj_desc == acpi_gbl_global_lock_mutex) {
		status = acpi_ev_acquire_global_lock(timeout);
	} else {
		status =
		    acpi_ex_system_wait_mutex(obj_desc->mutex.os_mutex,
					      timeout);
	}

	if (ACPI_FAILURE(status)) {

		/* Includes failure from a timeout on time_desc */

		return_ACPI_STATUS(status);
	}

	/* Acquired the mutex: update mutex object */

	obj_desc->mutex.thread_id = thread_id;
	obj_desc->mutex.acquisition_depth = 1;
	obj_desc->mutex.original_sync_level = 0;
	obj_desc->mutex.owner_thread = NULL;	/* Used only for AML Acquire() */

	return_ACPI_STATUS(AE_OK);
}