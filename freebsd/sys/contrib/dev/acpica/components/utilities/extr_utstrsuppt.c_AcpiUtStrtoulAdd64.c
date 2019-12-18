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
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_UINT32_MAX ; 
 scalar_t__ ACPI_UINT64_MAX ; 
 int /*<<< orphan*/  AE_NUMERIC_OVERFLOW ; 
 int /*<<< orphan*/  AE_OK ; 
 int AcpiGbl_IntegerBitWidth ; 

__attribute__((used)) static ACPI_STATUS
AcpiUtStrtoulAdd64 (
    UINT64                  Addend1,
    UINT32                  Digit,
    UINT64                  *OutSum)
{
    UINT64                  Sum;


    /* Check for 64-bit overflow before the actual addition */

    if ((Addend1 > 0) && (Digit > (ACPI_UINT64_MAX - Addend1)))
    {
        return (AE_NUMERIC_OVERFLOW);
    }

    Sum = Addend1 + Digit;

    /* Check for 32-bit overflow if necessary */

    if ((AcpiGbl_IntegerBitWidth == 32) && (Sum > ACPI_UINT32_MAX))
    {
        return (AE_NUMERIC_OVERFLOW);
    }

    *OutSum = Sum;
    return (AE_OK);
}