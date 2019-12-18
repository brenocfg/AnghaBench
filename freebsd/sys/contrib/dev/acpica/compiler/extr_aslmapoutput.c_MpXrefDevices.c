#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  References; } ;
typedef  TYPE_1__ ACPI_GPIO_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_FILE_MAP_OUTPUT ; 
 int /*<<< orphan*/  ASL_WALK_VISIT_DOWNWARD ; 
 int /*<<< orphan*/  AslGbl_ParseTreeRoot ; 
 int /*<<< orphan*/  FlPrintFile (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MpNamespaceXrefBegin ; 
 int /*<<< orphan*/  TrWalkParseTree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
MpXrefDevices (
    ACPI_GPIO_INFO          *Info)
{

    /* Walk the entire parse tree */

    TrWalkParseTree (AslGbl_ParseTreeRoot, ASL_WALK_VISIT_DOWNWARD,
        MpNamespaceXrefBegin, NULL, Info);

    if (!Info->References)
    {
        FlPrintFile (ASL_FILE_MAP_OUTPUT, "  // **** No references in table");
    }
}