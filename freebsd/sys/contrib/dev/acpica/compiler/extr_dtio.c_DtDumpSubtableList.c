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

/* Variables and functions */
 int /*<<< orphan*/  ASL_DEBUG_OUTPUT ; 
 int /*<<< orphan*/  AslGbl_DebugFlag ; 
 int /*<<< orphan*/  AslGbl_RootTable ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DtDumpSubtableInfo ; 
 int /*<<< orphan*/  DtDumpSubtableTree ; 
 int /*<<< orphan*/  DtWalkTableTree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
DtDumpSubtableList (
    void)
{

    if (!AslGbl_DebugFlag || !AslGbl_RootTable)
    {
        return;
    }

    DbgPrint (ASL_DEBUG_OUTPUT,
        "Subtable Info:\n"
        "Depth                      Name Length   TotalLen LenSize  Flags    "
        "This     Parent   Child    Peer\n\n");
    DtWalkTableTree (AslGbl_RootTable, DtDumpSubtableInfo, NULL, NULL);

    DbgPrint (ASL_DEBUG_OUTPUT,
        "\nSubtable Tree: (Depth, Name, Subtable, Length, TotalLength)\n\n");
    DtWalkTableTree (AslGbl_RootTable, DtDumpSubtableTree, NULL, NULL);

    DbgPrint (ASL_DEBUG_OUTPUT, "\n");
}