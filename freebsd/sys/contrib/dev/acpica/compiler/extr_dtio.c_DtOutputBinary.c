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
struct TYPE_2__ {int /*<<< orphan*/  Handle; } ;
typedef  int /*<<< orphan*/  DT_SUBTABLE ;

/* Variables and functions */
 scalar_t__ ACPI_UINT32_MAX ; 
 size_t ASL_FILE_AML_OUTPUT ; 
 int /*<<< orphan*/  AslAbort () ; 
 TYPE_1__* AslGbl_Files ; 
 scalar_t__ AslGbl_TableLength ; 
 scalar_t__ CmGetFileSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DtWalkTableTree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DtWriteBinary ; 

void
DtOutputBinary (
    DT_SUBTABLE             *RootTable)
{

    if (!RootTable)
    {
        return;
    }

    /* Walk the entire parse tree, emitting the binary data */

    DtWalkTableTree (RootTable, DtWriteBinary, NULL, NULL);

    AslGbl_TableLength = CmGetFileSize (AslGbl_Files[ASL_FILE_AML_OUTPUT].Handle);
    if (AslGbl_TableLength == ACPI_UINT32_MAX)
    {
        AslAbort ();
    }
}