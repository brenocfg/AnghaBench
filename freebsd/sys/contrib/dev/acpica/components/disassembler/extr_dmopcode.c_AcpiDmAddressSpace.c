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
typedef  int UINT8 ;

/* Variables and functions */
 int ACPI_NUM_PREDEFINED_REGIONS ; 
 int* AcpiGbl_RegionTypes ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 

void
AcpiDmAddressSpace (
    UINT8                   SpaceId)
{

    if (SpaceId >= ACPI_NUM_PREDEFINED_REGIONS)
    {
        if (SpaceId == 0x7F)
        {
            AcpiOsPrintf ("FFixedHW, ");
        }
        else
        {
            AcpiOsPrintf ("0x%.2X, ", SpaceId);
        }
    }
    else
    {
        AcpiOsPrintf ("%s, ", AcpiGbl_RegionTypes [SpaceId]);
    }
}