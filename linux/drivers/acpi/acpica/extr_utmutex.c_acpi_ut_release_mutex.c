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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  size_t acpi_mutex_handle ;
struct TYPE_2__ {scalar_t__ thread_id; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_MUTEX ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 size_t ACPI_MAX_MUTEX ; 
 scalar_t__ ACPI_MUTEX_NOT_ACQUIRED ; 
 size_t ACPI_NUM_MUTEX ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NOT_ACQUIRED ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_RELEASE_DEADLOCK ; 
 TYPE_1__* acpi_gbl_mutex_info ; 
 scalar_t__ acpi_os_get_thread_id () ; 
 int /*<<< orphan*/  acpi_os_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_get_mutex_name (size_t) ; 
 int /*<<< orphan*/  ut_release_mutex ; 

acpi_status acpi_ut_release_mutex(acpi_mutex_handle mutex_id)
{
	ACPI_FUNCTION_NAME(ut_release_mutex);

	ACPI_DEBUG_PRINT((ACPI_DB_MUTEX, "Thread %u releasing Mutex [%s]\n",
			  (u32)acpi_os_get_thread_id(),
			  acpi_ut_get_mutex_name(mutex_id)));

	if (mutex_id > ACPI_MAX_MUTEX) {
		return (AE_BAD_PARAMETER);
	}

	/*
	 * Mutex must be acquired in order to release it!
	 */
	if (acpi_gbl_mutex_info[mutex_id].thread_id == ACPI_MUTEX_NOT_ACQUIRED) {
		ACPI_ERROR((AE_INFO,
			    "Mutex [%s] (0x%X) is not acquired, cannot release",
			    acpi_ut_get_mutex_name(mutex_id), mutex_id));

		return (AE_NOT_ACQUIRED);
	}
#ifdef ACPI_MUTEX_DEBUG
	{
		u32 i;
		/*
		 * Mutex debug code, for internal debugging only.
		 *
		 * Deadlock prevention. Check if this thread owns any mutexes of value
		 * greater than this one. If so, the thread has violated the mutex
		 * ordering rule. This indicates a coding error somewhere in
		 * the ACPI subsystem code.
		 */
		for (i = mutex_id; i < ACPI_NUM_MUTEX; i++) {
			if (acpi_gbl_mutex_info[i].thread_id ==
			    acpi_os_get_thread_id()) {
				if (i == mutex_id) {
					continue;
				}

				ACPI_ERROR((AE_INFO,
					    "Invalid release order: owns [%s], releasing [%s]",
					    acpi_ut_get_mutex_name(i),
					    acpi_ut_get_mutex_name(mutex_id)));

				return (AE_RELEASE_DEADLOCK);
			}
		}
	}
#endif

	/* Mark unlocked FIRST */

	acpi_gbl_mutex_info[mutex_id].thread_id = ACPI_MUTEX_NOT_ACQUIRED;

	acpi_os_release_mutex(acpi_gbl_mutex_info[mutex_id].mutex);
	return (AE_OK);
}