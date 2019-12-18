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
typedef  size_t UINT32 ;

/* Variables and functions */
 size_t ACPI_BUFFER_BYTES_PER_LINE ; 
 int /*<<< orphan*/  AcpiDmIndent (size_t) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 scalar_t__ isprint (scalar_t__) ; 

void
AcpiDmDisasmByteList (
    UINT32                  Level,
    UINT8                   *ByteData,
    UINT32                  ByteCount)
{
    UINT32                  i;
    UINT32                  j;
    UINT32                  CurrentIndex;
    UINT8                   BufChar;


    if (!ByteCount)
    {
        return;
    }

    for (i = 0; i < ByteCount; i += ACPI_BUFFER_BYTES_PER_LINE)
    {
        /* Line indent and offset prefix for each new line */

        AcpiDmIndent (Level);
        if (ByteCount > ACPI_BUFFER_BYTES_PER_LINE)
        {
            AcpiOsPrintf ("/* %04X */ ", i);
        }

        /* Dump the actual hex values */

        for (j = 0; j < ACPI_BUFFER_BYTES_PER_LINE; j++)
        {
            CurrentIndex = i + j;
            if (CurrentIndex >= ByteCount)
            {
                /* Dump fill spaces */

                AcpiOsPrintf ("      ");
                continue;
            }

            AcpiOsPrintf (" 0x%2.2X", ByteData[CurrentIndex]);

            /* Add comma if there are more bytes to display */

            if (CurrentIndex < (ByteCount - 1))
            {
                AcpiOsPrintf (",");
            }
            else
            {
                AcpiOsPrintf (" ");
            }
        }

        /* Dump the ASCII equivalents within a comment */

        AcpiOsPrintf ("  // ");
        for (j = 0; j < ACPI_BUFFER_BYTES_PER_LINE; j++)
        {
            CurrentIndex = i + j;
            if (CurrentIndex >= ByteCount)
            {
                break;
            }

            BufChar = ByteData[CurrentIndex];
            if (isprint (BufChar))
            {
                AcpiOsPrintf ("%c", BufChar);
            }
            else
            {
                AcpiOsPrintf (".");
            }
        }

        /* Finished with this line */

        AcpiOsPrintf ("\n");
    }
}