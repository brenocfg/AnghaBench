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
struct acpi_table_madt {int dummy; } ;
struct acpi_table_header {int dummy; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SIG_MADT ; 
 int /*<<< orphan*/  acpi_get_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_table_header**) ; 

__attribute__((used)) static struct acpi_table_madt *get_madt_table(void)
{
	static struct acpi_table_madt *madt;
	static int read_madt;

	if (!read_madt) {
		if (ACPI_FAILURE(acpi_get_table(ACPI_SIG_MADT, 0,
					(struct acpi_table_header **)&madt)))
			madt = NULL;
		read_madt++;
	}

	return madt;
}