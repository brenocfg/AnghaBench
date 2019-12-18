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
 int /*<<< orphan*/ * AcpiGbl_TrsDecode ; 
 int /*<<< orphan*/ * AcpiGbl_TtpDecode ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AcpiDmIoFlags2 (
        UINT8               SpecificFlags)
{

    /* _TTP */

    AcpiOsPrintf (", %s",
        AcpiGbl_TtpDecode [ACPI_EXTRACT_1BIT_FLAG (SpecificFlags, 4)]);

    /*
     * TRS is only used if TTP is TypeTranslation. However, the disassembler
     * always emits exactly what is in the AML.
     */
    AcpiOsPrintf (", %s",
        AcpiGbl_TrsDecode [ACPI_EXTRACT_1BIT_FLAG (SpecificFlags, 5)]);
}