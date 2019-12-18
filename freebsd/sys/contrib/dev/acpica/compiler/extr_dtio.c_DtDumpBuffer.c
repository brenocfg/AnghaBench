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
 int /*<<< orphan*/  FlPrintFile (int,char*,...) ; 
 scalar_t__ isprint (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
DtDumpBuffer (
    UINT32                  FileId,
    UINT8                   *Buffer,
    UINT32                  Offset,
    UINT32                  Length)
{
    UINT32                  i;
    UINT32                  j;
    UINT8                   BufChar;


    FlPrintFile (FileId, "Output: [%3.3Xh %4.4d %3d] ",
        Offset, Offset, Length);

    i = 0;
    while (i < Length)
    {
        if (i >= 16)
        {
            FlPrintFile (FileId, "%24s", "");
        }

        /* Print 16 hex chars */

        for (j = 0; j < 16;)
        {
            if (i + j >= Length)
            {
                /* Dump fill spaces */

                FlPrintFile (FileId, "   ");
                j++;
                continue;
            }

            FlPrintFile (FileId, "%02X ", Buffer[i+j]);
            j++;
        }

        FlPrintFile (FileId, " ");
        for (j = 0; j < 16; j++)
        {
            if (i + j >= Length)
            {
                FlPrintFile (FileId, "\n\n");
                return;
            }

            BufChar = Buffer[(ACPI_SIZE) i + j];
            if (isprint (BufChar))
            {
                FlPrintFile (FileId, "%c", BufChar);
            }
            else
            {
                FlPrintFile (FileId, ".");
            }
        }

        /* Done with that line. */

        FlPrintFile (FileId, "\n");
        i += 16;
    }

    FlPrintFile (FileId, "\n\n");
}