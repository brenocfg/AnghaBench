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
typedef  scalar_t__ ACPI_PHYSICAL_ADDRESS ;

/* Variables and functions */
 scalar_t__ acpi_get_root_from_loader () ; 
 scalar_t__ acpi_get_root_from_memory () ; 
 scalar_t__ acpi_root_phys ; 

ACPI_PHYSICAL_ADDRESS
AcpiOsGetRootPointer(void)
{

	if (acpi_root_phys == 0) {
		acpi_root_phys = acpi_get_root_from_loader();
		if (acpi_root_phys == 0)
			acpi_root_phys = acpi_get_root_from_memory();
	}

	return (acpi_root_phys);
}