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
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ UUID_HYPHEN1_OFFSET ; 
 scalar_t__ UUID_HYPHEN2_OFFSET ; 
 scalar_t__ UUID_HYPHEN3_OFFSET ; 
 scalar_t__ UUID_HYPHEN4_OFFSET ; 
 scalar_t__ UUID_STRING_LENGTH ; 
 int /*<<< orphan*/  isxdigit (int) ; 
 scalar_t__ strlen (char*) ; 

ACPI_STATUS
AuValidateUuid (
    char                    *InString)
{
    UINT32                  i;


    if (!InString || (strlen (InString) != UUID_STRING_LENGTH))
    {
        return (AE_BAD_PARAMETER);
    }

    /* Check all 36 characters for correct format */

    for (i = 0; i < UUID_STRING_LENGTH; i++)
    {
        /* Must have 4 hyphens (dashes) in these positions: */

        if ((i == UUID_HYPHEN1_OFFSET) ||
            (i == UUID_HYPHEN2_OFFSET) ||
            (i == UUID_HYPHEN3_OFFSET) ||
            (i == UUID_HYPHEN4_OFFSET))
        {
            if (InString[i] != '-')
            {
                return (AE_BAD_PARAMETER);
            }
        }
        else
        {
            /* All other positions must contain hex digits */

            if (!isxdigit ((int) InString[i]))
            {
                return (AE_BAD_PARAMETER);
            }
        }
    }

    return (AE_OK);
}