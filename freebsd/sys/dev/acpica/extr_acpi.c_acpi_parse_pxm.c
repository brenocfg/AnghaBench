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
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (scalar_t__) ; 
 scalar_t__ AE_NOT_FOUND ; 
 scalar_t__ acpi_GetInteger (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/ * acpi_get_handle (int /*<<< orphan*/ ) ; 
 int acpi_map_pxm_to_vm_domainid (int) ; 

__attribute__((used)) static int
acpi_parse_pxm(device_t dev)
{
#ifdef NUMA
#if defined(__i386__) || defined(__amd64__)
	ACPI_HANDLE handle;
	ACPI_STATUS status;
	int pxm;

	handle = acpi_get_handle(dev);
	if (handle == NULL)
		return (-2);
	status = acpi_GetInteger(handle, "_PXM", &pxm);
	if (ACPI_SUCCESS(status))
		return (acpi_map_pxm_to_vm_domainid(pxm));
	if (status == AE_NOT_FOUND)
		return (-2);
#endif
#endif
	return (-1);
}