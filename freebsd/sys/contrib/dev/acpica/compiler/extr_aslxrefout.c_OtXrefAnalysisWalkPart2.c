#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_9__ {scalar_t__ Node; scalar_t__ ParseOpcode; int /*<<< orphan*/  ExternalName; int /*<<< orphan*/  LogicalLineNumber; TYPE_5__* Parent; } ;
struct TYPE_11__ {TYPE_3__ Asl; } ;
struct TYPE_10__ {int /*<<< orphan*/  ThisMethodInvocations; TYPE_2__* MethodOp; } ;
struct TYPE_7__ {scalar_t__ Node; } ;
struct TYPE_8__ {TYPE_1__ Asl; } ;
typedef  TYPE_4__ ASL_XREF_INFO ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_5__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int /*<<< orphan*/  AE_CTRL_DEPTH ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  ASL_FILE_XREF_OUTPUT ; 
 char* AcpiNsGetNormalizedPathname (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlPrintFile (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ PARSEOP_METHOD ; 
 scalar_t__ PARSEOP_METHODCALL ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static ACPI_STATUS
OtXrefAnalysisWalkPart2 (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    ASL_XREF_INFO           *XrefInfo = (ASL_XREF_INFO *) Context;
    ACPI_PARSE_OBJECT       *CallerOp;
    char                    *CallerFullPathname;


    /* Looking for MethodCall Ops only */

    if (!Op->Asl.Node ||
        (Op->Asl.ParseOpcode != PARSEOP_METHODCALL))
    {
        return (AE_OK);
    }

    /* If not a match to the target method, we are done */

    if (Op->Asl.Node != XrefInfo->MethodOp->Asl.Node)
    {
        return (AE_CTRL_DEPTH);
    }

    /* Find parent method to get method caller namepath */

    CallerOp = Op->Asl.Parent;
    while (CallerOp &&
        (CallerOp->Asl.ParseOpcode != PARSEOP_METHOD))
    {
        CallerOp = CallerOp->Asl.Parent;
    }

    /* There is no parent method for External() statements */

    if (!CallerOp)
    {
        return (AE_OK);
    }

    CallerFullPathname = AcpiNsGetNormalizedPathname (
        CallerOp->Asl.Node, TRUE);

    FlPrintFile (ASL_FILE_XREF_OUTPUT,
        "[%5u]     %-40s Invocation path: %s\n",
        Op->Asl.LogicalLineNumber, CallerFullPathname,
        Op->Asl.ExternalName);

    ACPI_FREE (CallerFullPathname);
    XrefInfo->ThisMethodInvocations++;
    return (AE_OK);
}