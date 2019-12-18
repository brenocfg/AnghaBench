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

/* Variables and functions */
 scalar_t__ ASL_FILE_ASM_INCLUDE_OUTPUT ; 
 scalar_t__ ASL_FILE_C_INCLUDE_OUTPUT ; 
 scalar_t__ ASL_FILE_C_SOURCE_OUTPUT ; 
 scalar_t__ AslGbl_CurrentLine ; 
 scalar_t__ AslGbl_HexBytesWereWritten ; 
 scalar_t__ AslGbl_SourceLine ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FlPrintFile (scalar_t__,char*) ; 
 int /*<<< orphan*/  LsFlushListingBuffer (scalar_t__) ; 
 scalar_t__ LsWriteOneSourceLine (scalar_t__) ; 

void
LsWriteSourceLines (
    UINT32                  ToLineNumber,
    UINT32                  ToLogicalLineNumber,
    UINT32                  FileId)
{

    /* Nothing to do for these file types */

    if ((FileId == ASL_FILE_ASM_INCLUDE_OUTPUT) ||
        (FileId == ASL_FILE_C_INCLUDE_OUTPUT))
    {
        return;
    }

    AslGbl_CurrentLine = ToLogicalLineNumber;

    /* Flush any hex bytes remaining from the last opcode */

    LsFlushListingBuffer (FileId);

    /* Read lines and write them as long as we are not caught up */

    if (AslGbl_SourceLine < AslGbl_CurrentLine)
    {
        /*
         * If we just completed writing some AML hex bytes, output a linefeed
         * to add some whitespace for readability.
         */
        if (AslGbl_HexBytesWereWritten)
        {
            FlPrintFile (FileId, "\n");
            AslGbl_HexBytesWereWritten = FALSE;
        }

        if (FileId == ASL_FILE_C_SOURCE_OUTPUT)
        {
            FlPrintFile (FileId, "    /*\n");
        }

        /* Write one line at a time until we have reached the target line # */

        while ((AslGbl_SourceLine < AslGbl_CurrentLine) &&
                LsWriteOneSourceLine (FileId))
        { ; }

        if (FileId == ASL_FILE_C_SOURCE_OUTPUT)
        {
            FlPrintFile (FileId, "     */");
        }

        FlPrintFile (FileId, "\n");
    }
}