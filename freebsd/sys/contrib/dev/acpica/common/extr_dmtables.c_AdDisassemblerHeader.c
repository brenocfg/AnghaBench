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
typedef  int /*<<< orphan*/  time_t ;
typedef  scalar_t__ UINT8 ;

/* Variables and functions */
 char* ACPI_COMMON_HEADER (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ACPI_IS_AML_TABLE ; 
 int /*<<< orphan*/  AML_DISASSEMBLER_NAME ; 
 scalar_t__ AcpiGbl_CstyleDisassembly ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 int /*<<< orphan*/  ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void
AdDisassemblerHeader (
    char                    *Filename,
    UINT8                   TableType)
{
    time_t                  Timer;


    time (&Timer);

    /* Header and input table info */

    AcpiOsPrintf ("/*\n");
    AcpiOsPrintf (ACPI_COMMON_HEADER (AML_DISASSEMBLER_NAME, " * "));

    if (TableType == ACPI_IS_AML_TABLE)
    {
        if (AcpiGbl_CstyleDisassembly)
        {
            AcpiOsPrintf (
                " * Disassembling to symbolic ASL+ operators\n"
                " *\n");
        }
        else
        {
            AcpiOsPrintf (
                " * Disassembling to non-symbolic legacy ASL operators\n"
                " *\n");
        }
    }

    AcpiOsPrintf (" * Disassembly of %s, %s", Filename, ctime (&Timer));
    AcpiOsPrintf (" *\n");
}