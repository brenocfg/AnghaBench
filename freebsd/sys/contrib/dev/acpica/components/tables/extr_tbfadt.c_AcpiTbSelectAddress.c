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
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BIOS_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (scalar_t__) ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AcpiGbl_Use32BitFadtAddresses ; 

__attribute__((used)) static UINT64
AcpiTbSelectAddress (
    char                    *RegisterName,
    UINT32                  Address32,
    UINT64                  Address64)
{

    if (!Address64)
    {
        /* 64-bit address is zero, use 32-bit address */

        return ((UINT64) Address32);
    }

    if (Address32 &&
       (Address64 != (UINT64) Address32))
    {
        /* Address mismatch between 32-bit and 64-bit versions */

        ACPI_BIOS_WARNING ((AE_INFO,
            "32/64X %s address mismatch in FADT: "
            "0x%8.8X/0x%8.8X%8.8X, using %u-bit address",
            RegisterName, Address32, ACPI_FORMAT_UINT64 (Address64),
            AcpiGbl_Use32BitFadtAddresses ? 32 : 64));

        /* 32-bit address override */

        if (AcpiGbl_Use32BitFadtAddresses)
        {
            return ((UINT64) Address32);
        }
    }

    /* Default is to use the 64-bit address */

    return (Address64);
}