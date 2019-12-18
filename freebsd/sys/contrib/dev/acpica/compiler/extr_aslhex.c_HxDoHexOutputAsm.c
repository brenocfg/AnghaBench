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
typedef  size_t UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_FILE_AML_OUTPUT ; 
 int /*<<< orphan*/  ASL_FILE_HEX_OUTPUT ; 
 size_t FlGetFileSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlPrintFile (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  FlSeekFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HEX_TABLE_LINE_SIZE ; 
 size_t HxReadAmlOutputFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LsDumpAsciiInComment (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
HxDoHexOutputAsm (
    void)
{
    UINT8                   FileData[HEX_TABLE_LINE_SIZE];
    UINT32                  LineLength;
    UINT32                  Offset = 0;
    UINT32                  AmlFileSize;
    UINT32                  i;


    /* Get AML size, seek back to start */

    AmlFileSize = FlGetFileSize (ASL_FILE_AML_OUTPUT);
    FlSeekFile (ASL_FILE_AML_OUTPUT, 0);

    FlPrintFile (ASL_FILE_HEX_OUTPUT, "; Assembly code source output\n");
    FlPrintFile (ASL_FILE_HEX_OUTPUT, "; AML code block contains 0x%X bytes\n;\n",
        AmlFileSize);

    while (Offset < AmlFileSize)
    {
        /* Read enough bytes needed for one output line */

        LineLength = HxReadAmlOutputFile (FileData);
        if (!LineLength)
        {
            break;
        }

        FlPrintFile (ASL_FILE_HEX_OUTPUT, "  db  ");

        for (i = 0; i < LineLength; i++)
        {
            /*
             * Print each hex byte.
             * Add a comma until the last byte of the line
             */
            FlPrintFile (ASL_FILE_HEX_OUTPUT, "0%2.2Xh", FileData[i]);
            if ((i + 1) < LineLength)
            {
                FlPrintFile (ASL_FILE_HEX_OUTPUT, ",");
            }
        }

        FlPrintFile (ASL_FILE_HEX_OUTPUT, " ");

        /* Add fill spaces if needed for last line */

        if (LineLength < HEX_TABLE_LINE_SIZE)
        {
            FlPrintFile (ASL_FILE_HEX_OUTPUT, "%*s",
                5 * (HEX_TABLE_LINE_SIZE - LineLength), " ");
        }

        /* Emit the offset and ascii dump for the entire line */

        FlPrintFile (ASL_FILE_HEX_OUTPUT, "  ; %8.8X", Offset);
        LsDumpAsciiInComment (ASL_FILE_HEX_OUTPUT, LineLength, FileData);

        FlPrintFile (ASL_FILE_HEX_OUTPUT, "\n");

        Offset += LineLength;
    }

    FlPrintFile (ASL_FILE_HEX_OUTPUT, "\n");
}