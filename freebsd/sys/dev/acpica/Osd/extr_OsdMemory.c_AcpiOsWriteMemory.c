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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  void* uint8_t ;
typedef  void* uint64_t ;
typedef  void* uint32_t ;
typedef  void* uint16_t ;
typedef  void* UINT64 ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_PHYSICAL_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  AE_OK ; 
 void* pmap_mapdev (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_unmapdev (int /*<<< orphan*/ ,int) ; 

ACPI_STATUS
AcpiOsWriteMemory(ACPI_PHYSICAL_ADDRESS Address, UINT64 Value, UINT32 Width)
{
    void	*LogicalAddress;

    LogicalAddress = pmap_mapdev(Address, Width / 8);
    if (LogicalAddress == NULL)
	return (AE_NOT_EXIST);

    switch (Width) {
    case 8:
	*(volatile uint8_t *)LogicalAddress = Value;
	break;
    case 16:
	*(volatile uint16_t *)LogicalAddress = Value;
	break;
    case 32:
	*(volatile uint32_t *)LogicalAddress = Value;
	break;
    case 64:
	*(volatile uint64_t *)LogicalAddress = Value;
	break;
    }

    pmap_unmapdev((vm_offset_t)LogicalAddress, Width / 8);

    return (AE_OK);
}