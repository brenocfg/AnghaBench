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
typedef  int UINT32 ;

/* Variables and functions */
#define  ASL_FILE_ASM_SOURCE_OUTPUT 130 
#define  ASL_FILE_C_SOURCE_OUTPUT 129 
#define  ASL_FILE_LISTING_OUTPUT 128 
 int /*<<< orphan*/ * AslGbl_AmlBuffer ; 
 scalar_t__ AslGbl_CurrentAmlOffset ; 
 scalar_t__ AslGbl_CurrentHexColumn ; 
 int /*<<< orphan*/  AslGbl_HexBytesWereWritten ; 
 int /*<<< orphan*/  FlPrintFile (int,char*,...) ; 
 int /*<<< orphan*/  FlWriteFile (int,char*,int) ; 
 scalar_t__ HEX_LISTING_LINE_SIZE ; 
 int /*<<< orphan*/  LsDumpAscii (int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LsDumpAsciiInComment (int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

void
LsFlushListingBuffer (
    UINT32                  FileId)
{
    UINT32                  i;


    if (AslGbl_CurrentHexColumn == 0)
    {
        return;
    }

    /* Write the hex bytes */

    switch (FileId)
    {
    case ASL_FILE_LISTING_OUTPUT:

        for (i = 0; i < AslGbl_CurrentHexColumn; i++)
        {
            FlPrintFile (FileId, "%2.2X ", AslGbl_AmlBuffer[i]);
        }

        for (i = 0; i < ((HEX_LISTING_LINE_SIZE - AslGbl_CurrentHexColumn) * 3); i++)
        {
            FlWriteFile (FileId, ".", 1);
        }

        /* Write the ASCII character associated with each of the bytes */

        LsDumpAscii (FileId, AslGbl_CurrentHexColumn, AslGbl_AmlBuffer);
        break;


    case ASL_FILE_ASM_SOURCE_OUTPUT:

        for (i = 0; i < AslGbl_CurrentHexColumn; i++)
        {
            if (i > 0)
            {
                FlPrintFile (FileId, ",");
            }

            FlPrintFile (FileId, "0%2.2Xh", AslGbl_AmlBuffer[i]);
        }

        for (i = 0; i < ((HEX_LISTING_LINE_SIZE - AslGbl_CurrentHexColumn) * 5); i++)
        {
            FlWriteFile (FileId, " ", 1);
        }

        FlPrintFile (FileId, "  ;%8.8X",
            AslGbl_CurrentAmlOffset - HEX_LISTING_LINE_SIZE);

        /* Write the ASCII character associated with each of the bytes */

        LsDumpAscii (FileId, AslGbl_CurrentHexColumn, AslGbl_AmlBuffer);
        break;


    case ASL_FILE_C_SOURCE_OUTPUT:

        for (i = 0; i < AslGbl_CurrentHexColumn; i++)
        {
            FlPrintFile (FileId, "0x%2.2X,", AslGbl_AmlBuffer[i]);
        }

        /* Pad hex output with spaces if line is shorter than max line size */

        for (i = 0; i < ((HEX_LISTING_LINE_SIZE - AslGbl_CurrentHexColumn) * 5); i++)
        {
            FlWriteFile (FileId, " ", 1);
        }

        /* AML offset for the start of the line */

        FlPrintFile (FileId, "    /* %8.8X",
            AslGbl_CurrentAmlOffset - AslGbl_CurrentHexColumn);

        /* Write the ASCII character associated with each of the bytes */

        LsDumpAsciiInComment (FileId, AslGbl_CurrentHexColumn, AslGbl_AmlBuffer);
        FlPrintFile (FileId, " */");
        break;

    default:

        /* No other types supported */

        return;
    }

    FlPrintFile (FileId, "\n");

    AslGbl_CurrentHexColumn = 0;
    AslGbl_HexBytesWereWritten = TRUE;
}