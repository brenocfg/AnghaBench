#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  Type; } ;
struct TYPE_6__ {int /*<<< orphan*/ * WalkState; scalar_t__ Level; scalar_t__ Flags; } ;
typedef  int /*<<< orphan*/  ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;
typedef  TYPE_1__ ACPI_OP_WALK_INFO ;
typedef  TYPE_2__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiDmClearTempList () ; 
 int /*<<< orphan*/  AcpiDmCommonAscendingOp ; 
 int /*<<< orphan*/  AcpiDmCommonDescendingOp ; 
 int /*<<< orphan*/  AcpiDmWalkParseTree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * AcpiDsCreateWalkState (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiDsScopeStackPush (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ AcpiGbl_TempListHead ; 

void
AcpiDmConvertParseObjects (
    ACPI_PARSE_OBJECT       *ParseTreeRoot,
    ACPI_NAMESPACE_NODE     *NamespaceRoot)
{
    ACPI_STATUS             Status;
    ACPI_OP_WALK_INFO       Info;
    ACPI_WALK_STATE         *WalkState;


    if (!ParseTreeRoot)
    {
        return;
    }

    /* Create and initialize a new walk state */

    WalkState = AcpiDsCreateWalkState (0, ParseTreeRoot, NULL, NULL);
    if (!WalkState)
    {
        return;
    }

    Status = AcpiDsScopeStackPush (NamespaceRoot, NamespaceRoot->Type,
        WalkState);
    if (ACPI_FAILURE (Status))
    {
        ACPI_FREE (WalkState);
        return;
    }

    Info.Flags = 0;
    Info.Level = 0;
    Info.WalkState = WalkState;

    AcpiDmWalkParseTree (ParseTreeRoot, AcpiDmCommonDescendingOp,
        AcpiDmCommonAscendingOp, &Info);
    ACPI_FREE (WalkState);

    if (AcpiGbl_TempListHead) {
        AcpiDmClearTempList();
    }

    return;
}