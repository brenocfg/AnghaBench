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
struct TYPE_2__ {scalar_t__ thread_id; } ;

/* Variables and functions */
 size_t ACPI_MAX_MUTEX ; 
 scalar_t__ ACPI_MUTEX_NOT_ACQUIRED ; 
 TYPE_1__* acpi_gbl_mutex_info ; 
 int /*<<< orphan*/  acpi_os_printf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  acpi_ut_get_mutex_name (size_t) ; 

void acpi_db_display_locks(void)
{
	u32 i;

	for (i = 0; i < ACPI_MAX_MUTEX; i++) {
		acpi_os_printf("%26s : %s\n", acpi_ut_get_mutex_name(i),
			       acpi_gbl_mutex_info[i].thread_id ==
			       ACPI_MUTEX_NOT_ACQUIRED ? "Locked" : "Unlocked");
	}
}