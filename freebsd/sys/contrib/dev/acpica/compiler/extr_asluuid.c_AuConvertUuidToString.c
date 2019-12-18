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
typedef  size_t UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 size_t* AcpiGbl_MapToUuidOffset ; 
 char AcpiUtHexToAsciiChar (char,int) ; 
 size_t UUID_BUFFER_LENGTH ; 
 size_t UUID_HYPHEN1_OFFSET ; 
 size_t UUID_HYPHEN2_OFFSET ; 
 size_t UUID_HYPHEN3_OFFSET ; 
 size_t UUID_HYPHEN4_OFFSET ; 
 size_t UUID_STRING_LENGTH ; 

ACPI_STATUS
AuConvertUuidToString (
    char                    *UuidBuffer,
    char                    *OutString)
{
    UINT32                  i;


    if (!UuidBuffer || !OutString)
    {
        return (AE_BAD_PARAMETER);
    }

    for (i = 0; i < UUID_BUFFER_LENGTH; i++)
    {
        OutString[AcpiGbl_MapToUuidOffset[i]] =
            AcpiUtHexToAsciiChar (UuidBuffer[i], 4);

        OutString[AcpiGbl_MapToUuidOffset[i] + 1] =
            AcpiUtHexToAsciiChar (UuidBuffer[i], 0);
    }

    /* Insert required hyphens (dashes) */

    OutString[UUID_HYPHEN1_OFFSET] =
    OutString[UUID_HYPHEN2_OFFSET] =
    OutString[UUID_HYPHEN3_OFFSET] =
    OutString[UUID_HYPHEN4_OFFSET] = '-';

    OutString[UUID_STRING_LENGTH] = 0; /* Null terminate */
    return (AE_OK);
}