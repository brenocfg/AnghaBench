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
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned long u16 ;
typedef  int /*<<< orphan*/  acpi_physical_address ;

/* Variables and functions */
 scalar_t__ ACPI_EBDA_PTR_LOCATION ; 
 int /*<<< orphan*/  ACPI_EBDA_WINDOW_SIZE ; 
 scalar_t__ ACPI_HI_RSDP_WINDOW_BASE ; 
 int /*<<< orphan*/  ACPI_HI_RSDP_WINDOW_SIZE ; 
 int /*<<< orphan*/ * scan_mem_for_rsdp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_physical_address bios_get_rsdp_addr(void)
{
	unsigned long address;
	u8 *rsdp;

	/* Get the location of the Extended BIOS Data Area (EBDA) */
	address = *(u16 *)ACPI_EBDA_PTR_LOCATION;
	address <<= 4;

	/*
	 * Search EBDA paragraphs (EBDA is required to be a minimum of
	 * 1K length)
	 */
	if (address > 0x400) {
		rsdp = scan_mem_for_rsdp((u8 *)address, ACPI_EBDA_WINDOW_SIZE);
		if (rsdp)
			return (acpi_physical_address)(unsigned long)rsdp;
	}

	/* Search upper memory: 16-byte boundaries in E0000h-FFFFFh */
	rsdp = scan_mem_for_rsdp((u8 *) ACPI_HI_RSDP_WINDOW_BASE,
					ACPI_HI_RSDP_WINDOW_SIZE);
	if (rsdp)
		return (acpi_physical_address)(unsigned long)rsdp;

	return 0;
}