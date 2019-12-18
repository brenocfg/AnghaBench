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
typedef  scalar_t__ acpi_physical_address ;
struct TYPE_2__ {scalar_t__ acpi_rsdp_addr; } ;

/* Variables and functions */
 scalar_t__ bios_get_rsdp_addr () ; 
 TYPE_1__* boot_params ; 
 scalar_t__ efi_get_rsdp_addr () ; 
 scalar_t__ kexec_get_rsdp_addr () ; 

acpi_physical_address get_rsdp_addr(void)
{
	acpi_physical_address pa;

	pa = boot_params->acpi_rsdp_addr;

	/*
	 * Try to get EFI data from setup_data. This can happen when we're a
	 * kexec'ed kernel and kexec(1) has passed all the required EFI info to
	 * us.
	 */
	if (!pa)
		pa = kexec_get_rsdp_addr();

	if (!pa)
		pa = efi_get_rsdp_addr();

	if (!pa)
		pa = bios_get_rsdp_addr();

	return pa;
}