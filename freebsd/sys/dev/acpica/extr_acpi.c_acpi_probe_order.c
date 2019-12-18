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
typedef  scalar_t__ ACPI_OBJECT_TYPE ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_PROCESSOR ; 
 int /*<<< orphan*/  AcpiGetType (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ acpi_MatchHid (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
acpi_probe_order(ACPI_HANDLE handle, int *order)
{
	ACPI_OBJECT_TYPE type;

	/*
	 * 0. CPUs
	 * 1. I/O port and memory system resource holders
	 * 2. Clocks and timers (to handle early accesses)
	 * 3. Embedded controllers (to handle early accesses)
	 * 4. PCI Link Devices
	 */
	AcpiGetType(handle, &type);
	if (type == ACPI_TYPE_PROCESSOR)
		*order = 0;
	else if (acpi_MatchHid(handle, "PNP0C01") ||
	    acpi_MatchHid(handle, "PNP0C02"))
		*order = 1;
	else if (acpi_MatchHid(handle, "PNP0100") ||
	    acpi_MatchHid(handle, "PNP0103") ||
	    acpi_MatchHid(handle, "PNP0B00"))
		*order = 2;
	else if (acpi_MatchHid(handle, "PNP0C09"))
		*order = 3;
	else if (acpi_MatchHid(handle, "PNP0C0F"))
		*order = 4;
}