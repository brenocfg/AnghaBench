#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_5__ {scalar_t__ Address; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_GENERIC_ADDRESS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiHwWrite (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static ACPI_STATUS
AcpiHwWriteMultiple (
    UINT32                  Value,
    ACPI_GENERIC_ADDRESS    *RegisterA,
    ACPI_GENERIC_ADDRESS    *RegisterB)
{
    ACPI_STATUS             Status;


    /* The first register is always required */

    Status = AcpiHwWrite (Value, RegisterA);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /*
     * Second register is optional
     *
     * No bit shifting or clearing is necessary, because of how the PM1
     * registers are defined in the ACPI specification:
     *
     * "Although the bits can be split between the two register blocks (each
     * register block has a unique pointer within the FADT), the bit positions
     * are maintained. The register block with unimplemented bits (that is,
     * those implemented in the other register block) always returns zeros,
     * and writes have no side effects"
     */
    if (RegisterB->Address)
    {
        Status = AcpiHwWrite (Value, RegisterB);
    }

    return (Status);
}