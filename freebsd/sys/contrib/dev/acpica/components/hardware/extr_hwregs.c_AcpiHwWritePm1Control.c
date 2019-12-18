#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_3__ {scalar_t__ Address; } ;
struct TYPE_4__ {TYPE_1__ XPm1bControlBlock; TYPE_1__ XPm1aControlBlock; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 TYPE_2__ AcpiGbl_FADT ; 
 int /*<<< orphan*/  AcpiHwWrite (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  HwWritePm1Control ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiHwWritePm1Control (
    UINT32                  Pm1aControl,
    UINT32                  Pm1bControl)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (HwWritePm1Control);


    Status = AcpiHwWrite (Pm1aControl, &AcpiGbl_FADT.XPm1aControlBlock);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    if (AcpiGbl_FADT.XPm1bControlBlock.Address)
    {
        Status = AcpiHwWrite (Pm1bControl, &AcpiGbl_FADT.XPm1bControlBlock);
    }
    return_ACPI_STATUS (Status);
}