#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_8__ {int /*<<< orphan*/ * Handle; } ;
struct TYPE_7__ {int Level; scalar_t__ MessageId; char* Message; struct TYPE_7__* SubError; int /*<<< orphan*/  Filename; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_1__ ASL_ERROR_MSG ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
#define  ASL_OPTIMIZATION 132 
#define  ASL_REMARK 131 
#define  ASL_WARNING 130 
#define  ASL_WARNING2 129 
#define  ASL_WARNING3 128 
 int /*<<< orphan*/  AeDecodeErrorMessageId (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  AePrintErrorSourceLine (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  AePrintSubError (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  AslGbl_DisplayOptimizations ; 
 int /*<<< orphan*/  AslGbl_DisplayRemarks ; 
 int /*<<< orphan*/  AslGbl_DisplayWarnings ; 
 TYPE_2__* AslGbl_Files ; 
 scalar_t__ AslGbl_NoErrors ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void
AePrintException (
    UINT32                  FileId,
    ASL_ERROR_MSG           *Enode,
    char                    *Header)
{
    FILE                    *OutputFile;
    BOOLEAN                 PrematureEOF = FALSE;
    UINT32                  Total = 0;
    ACPI_STATUS             Status;
    ASL_ERROR_MSG           *Child = Enode->SubError;


    if (AslGbl_NoErrors)
    {
        return;
    }

    /*
     * Only listing files have a header, and remarks/optimizations
     * are always output
     */
    if (!Header)
    {
        /* Ignore remarks if requested */

        switch (Enode->Level)
        {
        case ASL_WARNING:
        case ASL_WARNING2:
        case ASL_WARNING3:

            if (!AslGbl_DisplayWarnings)
            {
                return;
            }
            break;

        case ASL_REMARK:

            if (!AslGbl_DisplayRemarks)
            {
                return;
            }
            break;

        case ASL_OPTIMIZATION:

            if (!AslGbl_DisplayOptimizations)
            {
                return;
            }
            break;

        default:

            break;
        }
    }

    /* Get the various required file handles */

    OutputFile = AslGbl_Files[FileId].Handle;

    if (Header)
    {
        fprintf (OutputFile, "%s", Header);
    }

    if (!Enode->Filename)
    {
        AeDecodeErrorMessageId (OutputFile, Enode, PrematureEOF, Total);
        return;
    }

    Status = AePrintErrorSourceLine (OutputFile, Enode, &PrematureEOF, &Total);
    if (ACPI_FAILURE (Status))
    {
        return;
    }

    /* If a NULL message ID, just print the raw message */

    if (Enode->MessageId == 0)
    {
        fprintf (OutputFile, "%s\n", Enode->Message);
        return;
    }

    AeDecodeErrorMessageId (OutputFile, Enode, PrematureEOF, Total);

    while (Child)
    {
        fprintf (OutputFile, "\n");
        AePrintSubError (OutputFile, Child);
        Child = Child->SubError;
    }
}