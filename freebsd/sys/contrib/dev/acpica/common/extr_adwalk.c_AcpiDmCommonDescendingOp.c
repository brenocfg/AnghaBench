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
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmProcessResourceDescriptors (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  AcpiDmProcessSwitch (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ACPI_STATUS
AcpiDmCommonDescendingOp (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    ACPI_STATUS             Status;


    /* Resource descriptor conversion */

    Status = AcpiDmProcessResourceDescriptors (Op, Level, Context);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /* Switch/Case conversion */

    Status = AcpiDmProcessSwitch (Op);
    return (Status);
}