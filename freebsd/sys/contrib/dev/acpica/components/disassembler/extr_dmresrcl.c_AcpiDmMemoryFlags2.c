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
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 size_t ACPI_EXTRACT_1BIT_FLAG (int /*<<< orphan*/ ,int) ; 
 size_t ACPI_EXTRACT_2BIT_FLAG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * AcpiGbl_MtpDecode ; 
 int /*<<< orphan*/ * AcpiGbl_TtpDecode ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AcpiDmMemoryFlags2 (
    UINT8                   SpecificFlags)
{

    AcpiOsPrintf (", %s, %s",
        AcpiGbl_MtpDecode [ACPI_EXTRACT_2BIT_FLAG (SpecificFlags, 3)],
        AcpiGbl_TtpDecode [ACPI_EXTRACT_1BIT_FLAG (SpecificFlags, 5)]);
}