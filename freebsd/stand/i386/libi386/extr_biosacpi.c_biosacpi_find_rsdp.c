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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ACPI_TABLE_RSDP ;

/* Variables and functions */
 scalar_t__ PTOV (int) ; 
 int /*<<< orphan*/ * biosacpi_search_rsdp (char*,int) ; 

__attribute__((used)) static ACPI_TABLE_RSDP *
biosacpi_find_rsdp(void)
{
    ACPI_TABLE_RSDP	*rsdp;
    uint16_t		*addr;

    /* EBDA is the 1 KB addressed by the 16 bit pointer at 0x40E. */
    addr = (uint16_t *)PTOV(0x40E);
    if ((rsdp = biosacpi_search_rsdp((char *)(*addr << 4), 0x400)) != NULL)
	return (rsdp);

    /* Check the upper memory BIOS space, 0xe0000 - 0xfffff. */
    if ((rsdp = biosacpi_search_rsdp((char *)0xe0000, 0x20000)) != NULL)
	return (rsdp);

    return (NULL);
}