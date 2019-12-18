#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * WalkState; scalar_t__ Level; scalar_t__ Count; scalar_t__ Flags; } ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;
typedef  TYPE_1__ ACPI_OP_WALK_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiDmDumpDescending ; 
 int /*<<< orphan*/  AcpiDmWalkParseTree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*) ; 

void
AcpiDmDumpTree (
    ACPI_PARSE_OBJECT       *Origin)
{
    ACPI_OP_WALK_INFO       Info;


    if (!Origin)
    {
        return;
    }

    AcpiOsPrintf ("/*\nAML Parse Tree\n\n");
    Info.Flags = 0;
    Info.Count = 0;
    Info.Level = 0;
    Info.WalkState = NULL;

    AcpiDmWalkParseTree (Origin, AcpiDmDumpDescending, NULL, &Info);
    AcpiOsPrintf ("*/\n\n");
}