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
typedef  int UINT32 ;

/* Variables and functions */
 int ACPI_FADT_V1_SIZE ; 
 int ACPI_FADT_V2_SIZE ; 
 int ACPI_FADT_V3_SIZE ; 
 int ACPI_FADT_V5_SIZE ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 

__attribute__((used)) static void
AcpiDmValidateFadtLength (
    UINT32                  Revision,
    UINT32                  Length)
{
    UINT32                  ExpectedLength;


    switch (Revision)
    {
    case 0:

        AcpiOsPrintf ("// ACPI Warning: Invalid FADT revision: 0\n");
        return;

    case 1:

        ExpectedLength = ACPI_FADT_V1_SIZE;
        break;

    case 2:

        ExpectedLength = ACPI_FADT_V2_SIZE;
        break;

    case 3:
    case 4:

        ExpectedLength = ACPI_FADT_V3_SIZE;
        break;

    case 5:

        ExpectedLength = ACPI_FADT_V5_SIZE;
        break;

    default:

        return;
    }

    if (Length == ExpectedLength)
    {
        return;
    }

    AcpiOsPrintf (
        "\n// ACPI Warning: FADT revision %X does not match length: "
        "found %X expected %X\n",
        Revision, Length, ExpectedLength);
}