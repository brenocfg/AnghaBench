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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT32 ;
typedef  size_t ACPI_SIZE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_MOVE_16_TO_32 (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACPI_MOVE_32_TO_32 (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
#define  DB_BYTE_DISPLAY 131 
 int DB_DISPLAY_DATA_ONLY ; 
#define  DB_DWORD_DISPLAY 130 
#define  DB_QWORD_DISPLAY 129 
#define  DB_WORD_DISPLAY 128 
 scalar_t__ isprint (int /*<<< orphan*/ ) ; 

void
AcpiUtDumpBuffer (
    UINT8                   *Buffer,
    UINT32                  Count,
    UINT32                  Display,
    UINT32                  BaseOffset)
{
    UINT32                  i = 0;
    UINT32                  j;
    UINT32                  Temp32;
    UINT8                   BufChar;
    UINT32                  DisplayDataOnly = Display & DB_DISPLAY_DATA_ONLY;


    Display &= ~DB_DISPLAY_DATA_ONLY;
    if (!Buffer)
    {
        AcpiOsPrintf ("Null Buffer Pointer in DumpBuffer!\n");
        return;
    }

    if ((Count < 4) || (Count & 0x01))
    {
        Display = DB_BYTE_DISPLAY;
    }

    /* Nasty little dump buffer routine! */

    while (i < Count)
    {
        /* Print current offset */

        if (!DisplayDataOnly)
        {
            AcpiOsPrintf ("%8.4X: ", (BaseOffset + i));
        }

        /* Print 16 hex chars */

        for (j = 0; j < 16;)
        {
            if (i + j >= Count)
            {
                /* Dump fill spaces */

                AcpiOsPrintf ("%*s", ((Display * 2) + 1), " ");
                j += Display;
                continue;
            }

            switch (Display)
            {
            case DB_BYTE_DISPLAY:
            default:    /* Default is BYTE display */

                AcpiOsPrintf ("%02X ", Buffer[(ACPI_SIZE) i + j]);
                break;

            case DB_WORD_DISPLAY:

                ACPI_MOVE_16_TO_32 (&Temp32, &Buffer[(ACPI_SIZE) i + j]);
                AcpiOsPrintf ("%04X ", Temp32);
                break;

            case DB_DWORD_DISPLAY:

                ACPI_MOVE_32_TO_32 (&Temp32, &Buffer[(ACPI_SIZE) i + j]);
                AcpiOsPrintf ("%08X ", Temp32);
                break;

            case DB_QWORD_DISPLAY:

                ACPI_MOVE_32_TO_32 (&Temp32, &Buffer[(ACPI_SIZE) i + j]);
                AcpiOsPrintf ("%08X", Temp32);

                ACPI_MOVE_32_TO_32 (&Temp32, &Buffer[(ACPI_SIZE) i + j + 4]);
                AcpiOsPrintf ("%08X ", Temp32);
                break;
            }

            j += Display;
        }

        /*
         * Print the ASCII equivalent characters but watch out for the bad
         * unprintable ones (printable chars are 0x20 through 0x7E)
         */
        if (!DisplayDataOnly)
        {
            AcpiOsPrintf (" ");
            for (j = 0; j < 16; j++)
            {
                if (i + j >= Count)
                {
                    AcpiOsPrintf ("\n");
                    return;
                }

                /*
                 * Add comment characters so rest of line is ignored when
                 * compiled
                 */
                if (j == 0)
                {
                    AcpiOsPrintf ("// ");
                }

                BufChar = Buffer[(ACPI_SIZE) i + j];
                if (isprint (BufChar))
                {
                    AcpiOsPrintf ("%c", BufChar);
                }
                else
                {
                    AcpiOsPrintf (".");
                }
            }

            /* Done with that line. */

            AcpiOsPrintf ("\n");
        }
        i += 16;
    }

    return;
}