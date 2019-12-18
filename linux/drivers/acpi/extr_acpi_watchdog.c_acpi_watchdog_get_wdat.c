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
struct acpi_table_wdat {int dummy; } ;
struct acpi_table_header {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SIG_WDAT ; 
 scalar_t__ acpi_disabled ; 
 int /*<<< orphan*/  acpi_get_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_table_header**) ; 
 scalar_t__ acpi_watchdog_uses_rtc (struct acpi_table_wdat const*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static const struct acpi_table_wdat *acpi_watchdog_get_wdat(void)
{
	const struct acpi_table_wdat *wdat = NULL;
	acpi_status status;

	if (acpi_disabled)
		return NULL;

	status = acpi_get_table(ACPI_SIG_WDAT, 0,
				(struct acpi_table_header **)&wdat);
	if (ACPI_FAILURE(status)) {
		/* It is fine if there is no WDAT */
		return NULL;
	}

	if (acpi_watchdog_uses_rtc(wdat)) {
		pr_info("Skipping WDAT on this system because it uses RTC SRAM\n");
		return NULL;
	}

	return wdat;
}