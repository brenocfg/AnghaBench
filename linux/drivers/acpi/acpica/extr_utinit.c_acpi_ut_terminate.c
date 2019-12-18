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

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_delete_address_lists () ; 
 int /*<<< orphan*/  acpi_ut_free_gpe_lists () ; 
 int /*<<< orphan*/  return_VOID ; 
 int /*<<< orphan*/  ut_terminate ; 

__attribute__((used)) static void acpi_ut_terminate(void)
{
	ACPI_FUNCTION_TRACE(ut_terminate);

	acpi_ut_free_gpe_lists();
	acpi_ut_delete_address_lists();
	return_VOID;
}