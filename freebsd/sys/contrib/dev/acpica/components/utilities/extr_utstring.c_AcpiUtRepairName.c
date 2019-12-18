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
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ ACPI_COMPARE_NAMESEG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_COPY_NAMESEG (size_t*,char*) ; 
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 size_t ACPI_NAMESEG_SIZE ; 
 int /*<<< orphan*/  ACPI_ROOT_PATHNAME ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AcpiGbl_EnableInterpreterSlack ; 
 scalar_t__ AcpiUtValidNameChar (char,size_t) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UtRepairName ; 

void
AcpiUtRepairName (
    char                    *Name)
{
    UINT32                  i;
    BOOLEAN                 FoundBadChar = FALSE;
    UINT32                  OriginalName;


    ACPI_FUNCTION_NAME (UtRepairName);


    /*
     * Special case for the root node. This can happen if we get an
     * error during the execution of module-level code.
     */
    if (ACPI_COMPARE_NAMESEG (Name, ACPI_ROOT_PATHNAME))
    {
        return;
    }

    ACPI_COPY_NAMESEG (&OriginalName, Name);

    /* Check each character in the name */

    for (i = 0; i < ACPI_NAMESEG_SIZE; i++)
    {
        if (AcpiUtValidNameChar (Name[i], i))
        {
            continue;
        }

        /*
         * Replace a bad character with something printable, yet technically
         * still invalid. This prevents any collisions with existing "good"
         * names in the namespace.
         */
        Name[i] = '*';
        FoundBadChar = TRUE;
    }

    if (FoundBadChar)
    {
        /* Report warning only if in strict mode or debug mode */

        if (!AcpiGbl_EnableInterpreterSlack)
        {
            ACPI_WARNING ((AE_INFO,
                "Invalid character(s) in name (0x%.8X), repaired: [%4.4s]",
                OriginalName, Name));
        }
        else
        {
            ACPI_DEBUG_PRINT ((ACPI_DB_INFO,
                "Invalid character(s) in name (0x%.8X), repaired: [%4.4s]",
                OriginalName, Name));
        }
    }
}