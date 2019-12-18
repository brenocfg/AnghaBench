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
struct semaphore {int /*<<< orphan*/  wait_list; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_MUTEX ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  kfree (struct semaphore*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

acpi_status acpi_os_delete_semaphore(acpi_handle handle)
{
	struct semaphore *sem = (struct semaphore *)handle;

	if (!sem)
		return AE_BAD_PARAMETER;

	ACPI_DEBUG_PRINT((ACPI_DB_MUTEX, "Deleting semaphore[%p].\n", handle));

	BUG_ON(!list_empty(&sem->wait_list));
	kfree(sem);
	sem = NULL;

	return AE_OK;
}