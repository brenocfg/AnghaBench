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
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiEvWalkGpeList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiHwEnableRuntimeGpeBlock ; 
 int /*<<< orphan*/  HwEnableAllRuntimeGpes ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiHwEnableAllRuntimeGpes (
    void)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (HwEnableAllRuntimeGpes);


    Status = AcpiEvWalkGpeList (AcpiHwEnableRuntimeGpeBlock, NULL);
    return_ACPI_STATUS (Status);
}