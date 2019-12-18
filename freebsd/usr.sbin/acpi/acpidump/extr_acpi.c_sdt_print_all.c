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
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_handle_rsdt (int /*<<< orphan*/ *) ; 

void
sdt_print_all(ACPI_TABLE_HEADER *rsdp)
{
	acpi_handle_rsdt(rsdp);
}