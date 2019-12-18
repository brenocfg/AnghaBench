#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  Filename; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_CTRL_CONTINUE ; 
 int /*<<< orphan*/  AE_OK ; 
 size_t ASL_FILE_INPUT ; 
 int /*<<< orphan*/  AcpiAllocateRootTable (int) ; 
 int /*<<< orphan*/  AcpiDmUnresolvedWarning (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGbl_DmOpt_Disasm ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AdAmlDisassemble (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AeClearErrorLog () ; 
 scalar_t__ AslGbl_DoCompile ; 
 TYPE_1__* AslGbl_Files ; 
 int /*<<< orphan*/  AslGbl_OutputFilenamePrefix ; 
 int /*<<< orphan*/  AslToFile ; 
 int /*<<< orphan*/  TRUE ; 

ACPI_STATUS
AslDoDisassembly (
    void)
{
    ACPI_STATUS             Status;


    Status = AcpiAllocateRootTable (4);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not initialize ACPI Table Manager, %s\n",
            AcpiFormatException (Status));
        return (Status);
    }

    /* This is where the disassembly happens */

    AcpiGbl_DmOpt_Disasm = TRUE;
    Status = AdAmlDisassemble (AslToFile,
        AslGbl_Files[ASL_FILE_INPUT].Filename, AslGbl_OutputFilenamePrefix,
        &AslGbl_Files[ASL_FILE_INPUT].Filename);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /* Check if any control methods were unresolved */

    AcpiDmUnresolvedWarning (0);

    /* Clear Error log */

    AeClearErrorLog ();

    /*
     * AslGbl_Files[ASL_FILE_INPUT].Filename was replaced with the
     * .DSL disassembly file, which can now be compiled if requested
     */
    if (AslGbl_DoCompile)
    {
        AcpiOsPrintf ("\nCompiling \"%s\"\n",
            AslGbl_Files[ASL_FILE_INPUT].Filename);
        return (AE_CTRL_CONTINUE);
    }

    return (AE_OK);
}