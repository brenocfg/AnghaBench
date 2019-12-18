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
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_PROCESSOR_NOTIFY_PERFORMANCE ; 
 int /*<<< orphan*/  acpi_evaluate_ost (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_has_method (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void acpi_processor_ppc_ost(acpi_handle handle, int status)
{
	if (acpi_has_method(handle, "_OST"))
		acpi_evaluate_ost(handle, ACPI_PROCESSOR_NOTIFY_PERFORMANCE,
				  status, NULL);
}