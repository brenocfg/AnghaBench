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
 scalar_t__ ASL_FILE_LISTING_OUTPUT ; 
 int /*<<< orphan*/  AePrintErrorLog (scalar_t__) ; 
 scalar_t__ AslGbl_CurrentAmlOffset ; 
 int /*<<< orphan*/  FlPrintFile (scalar_t__,char*) ; 
 int /*<<< orphan*/  LsFlushListingBuffer (scalar_t__) ; 
 scalar_t__ LsWriteOneSourceLine (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UtDisplayOneSummary (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
LsFinishSourceListing (
    UINT32                  FileId)
{

    if ((FileId == ASL_FILE_ASM_INCLUDE_OUTPUT) ||
        (FileId == ASL_FILE_C_INCLUDE_OUTPUT))
    {
        return;
    }

    LsFlushListingBuffer (FileId);
    AslGbl_CurrentAmlOffset = 0;

    /* Flush any remaining text in the source file */

    if (FileId == ASL_FILE_C_SOURCE_OUTPUT)
    {
        FlPrintFile (FileId, "    /*\n");
    }

    while (LsWriteOneSourceLine (FileId))
    { ; }

    if (FileId == ASL_FILE_C_SOURCE_OUTPUT)
    {
        FlPrintFile (FileId, "\n     */\n    };\n");
    }

    FlPrintFile (FileId, "\n");

    if (FileId == ASL_FILE_LISTING_OUTPUT)
    {
        /* Print a summary of the compile exceptions */

        FlPrintFile (FileId, "\n\nSummary of errors and warnings\n\n");
        AePrintErrorLog (FileId);
        FlPrintFile (FileId, "\n");
        UtDisplayOneSummary (FileId, TRUE);
        FlPrintFile (FileId, "\n");
    }
}