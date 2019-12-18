#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_5__ {int /*<<< orphan*/  Filename; int /*<<< orphan*/  Column; int /*<<< orphan*/  LogicalByteOffset; int /*<<< orphan*/  LogicalLineNumber; int /*<<< orphan*/  LineNumber; } ;
struct TYPE_6__ {TYPE_1__ Asl; } ;
typedef  int /*<<< orphan*/  ASL_ERROR_MSG ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AslInitEnode (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ AslIsExceptionIgnored (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslLogNewError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
AslDualParseOpError (
    UINT8                   Level,
    UINT16                  MainMsgId,
    ACPI_PARSE_OBJECT       *MainOp,
    char                    *MainMsg,
    UINT16                  SubMsgId,
    ACPI_PARSE_OBJECT       *SubOp,
    char                    *SubMsg)
{
    ASL_ERROR_MSG           *SubEnode = NULL;


    /* Check if user wants to ignore this exception */

    if (AslIsExceptionIgnored (Level, MainMsgId) || !MainOp)
    {
        return;
    }

    if (SubOp)
    {
        AslInitEnode (&SubEnode, Level, SubMsgId, SubOp->Asl.LineNumber,
            SubOp->Asl.LogicalLineNumber, SubOp->Asl.LogicalByteOffset,
            SubOp->Asl.Column, SubOp->Asl.Filename, SubMsg,
            NULL, NULL);
    }

    AslLogNewError (Level, MainMsgId, MainOp->Asl.LineNumber,
        MainOp->Asl.LogicalLineNumber, MainOp->Asl.LogicalByteOffset,
        MainOp->Asl.Column, MainOp->Asl.Filename, MainMsg,
        NULL, SubEnode);
}