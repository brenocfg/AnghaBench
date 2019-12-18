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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u_long ;
typedef  int /*<<< orphan*/  ACPI_TABLE_RSDP ;

/* Variables and functions */
 int ACPI_EBDA_PTR_LOCATION ; 
 int ACPI_EBDA_WINDOW_SIZE ; 
 int ACPI_HI_RSDP_WINDOW_BASE ; 
 int ACPI_HI_RSDP_WINDOW_SIZE ; 
 int /*<<< orphan*/ * acpi_get_rsdp (int) ; 
 int /*<<< orphan*/  acpi_mem_fd ; 
 int /*<<< orphan*/  pread (int /*<<< orphan*/ ,int*,int,int) ; 

__attribute__((used)) static ACPI_TABLE_RSDP *
acpi_scan_rsd_ptr(void)
{
#if defined(__amd64__) || defined(__i386__)
	ACPI_TABLE_RSDP *rsdp;
	u_long		addr, end;

	/*
	 * On ia32, scan physical memory for the RSD PTR if above failed.
	 * According to section 5.2.2 of the ACPI spec, we only consider
	 * two regions for the base address:
	 * 1. EBDA (1 KB area addressed by the 16 bit pointer at 0x40E
	 * 2. High memory (0xE0000 - 0xFFFFF)
	 */
	addr = ACPI_EBDA_PTR_LOCATION;
	pread(acpi_mem_fd, &addr, sizeof(uint16_t), addr);
	addr <<= 4;
	end = addr + ACPI_EBDA_WINDOW_SIZE;
	for (; addr < end; addr += 16)
		if ((rsdp = acpi_get_rsdp(addr)) != NULL)
			return (rsdp);
	addr = ACPI_HI_RSDP_WINDOW_BASE;
	end = addr + ACPI_HI_RSDP_WINDOW_SIZE;
	for (; addr < end; addr += 16)
		if ((rsdp = acpi_get_rsdp(addr)) != NULL)
			return (rsdp);
#endif /* __amd64__ || __i386__ */
	return (NULL);
}