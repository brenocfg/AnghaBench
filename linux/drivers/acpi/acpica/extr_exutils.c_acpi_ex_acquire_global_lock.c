#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_WAIT_FOREVER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int AML_FIELD_LOCK_RULE_MASK ; 
 int /*<<< orphan*/  acpi_ex_acquire_mutex_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_gbl_global_lock_mutex ; 
 int /*<<< orphan*/  acpi_os_get_thread_id () ; 
 int /*<<< orphan*/  ex_acquire_global_lock ; 
 int /*<<< orphan*/  return_VOID ; 

void acpi_ex_acquire_global_lock(u32 field_flags)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(ex_acquire_global_lock);

	/* Only use the lock if the always_lock bit is set */

	if (!(field_flags & AML_FIELD_LOCK_RULE_MASK)) {
		return_VOID;
	}

	/* Attempt to get the global lock, wait forever */

	status = acpi_ex_acquire_mutex_object(ACPI_WAIT_FOREVER,
					      acpi_gbl_global_lock_mutex,
					      acpi_os_get_thread_id());

	if (ACPI_FAILURE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Could not acquire Global Lock"));
	}

	return_VOID;
}