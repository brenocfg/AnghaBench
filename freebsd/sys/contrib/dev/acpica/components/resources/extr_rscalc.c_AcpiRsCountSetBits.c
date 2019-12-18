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
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 

__attribute__((used)) static UINT8
AcpiRsCountSetBits (
    UINT16                  BitField)
{
    UINT8                   BitsSet;


    ACPI_FUNCTION_ENTRY ();


    for (BitsSet = 0; BitField; BitsSet++)
    {
        /* Zero the least significant bit that is set */

        BitField &= (UINT16) (BitField - 1);
    }

    return (BitsSet);
}