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
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiDmTableInfoEinj0 ; 
 int /*<<< orphan*/  AcpiDmTableInfoErst ; 
 int /*<<< orphan*/  DtCompileTwoSubtables (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ACPI_STATUS
DtCompileErst (
    void                    **List)
{
    ACPI_STATUS             Status;


    Status = DtCompileTwoSubtables (List,
        AcpiDmTableInfoErst, AcpiDmTableInfoEinj0);
    return (Status);
}