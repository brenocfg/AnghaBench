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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  phys_cpuid_t ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_get_phys_id (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int acpi_map_cpuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int acpi_get_cpuid(acpi_handle handle, int type, u32 acpi_id)
{
	phys_cpuid_t phys_id;

	phys_id = acpi_get_phys_id(handle, type, acpi_id);

	return acpi_map_cpuid(phys_id, acpi_id);
}