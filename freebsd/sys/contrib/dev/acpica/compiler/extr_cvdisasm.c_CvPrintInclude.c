#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_5__ {scalar_t__ IncludeWritten; int /*<<< orphan*/  Filename; int /*<<< orphan*/  IncludeComment; TYPE_1__* Parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  File; int /*<<< orphan*/  Filename; } ;
typedef  TYPE_2__ ACPI_FILE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiDmIndent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsRedirectOutput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CvDbgPrint (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  CvPrintOneCommentList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static void
CvPrintInclude(
    ACPI_FILE_NODE          *FNode,
    UINT32                  Level)
{

    if (!FNode || FNode->IncludeWritten)
    {
        return;
    }

    CvDbgPrint ("Writing include for %s within %s\n",
        FNode->Filename, FNode->Parent->Filename);
    AcpiOsRedirectOutput (FNode->Parent->File);
    CvPrintOneCommentList (FNode->IncludeComment, Level);

    AcpiDmIndent (Level);
    AcpiOsPrintf ("Include (\"%s\")\n", FNode->Filename);
    CvDbgPrint ("emitted the following: Include (\"%s\")\n",
        FNode->Filename);
    FNode->IncludeWritten = TRUE;
}