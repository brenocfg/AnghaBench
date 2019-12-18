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
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ ACPI_COMPARE_NAMESEG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_RSDP_NAME ; 
 int /*<<< orphan*/  ACPI_SIG_DSDT ; 
 int /*<<< orphan*/  ACPI_SIG_FACS ; 
 int /*<<< orphan*/  ACPI_SIG_OSDT ; 
 int /*<<< orphan*/  ACPI_SIG_SSDT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
AcpiUtIsSpecialTable (
    char                    *Signature)
{

    if (ACPI_COMPARE_NAMESEG (Signature, ACPI_SIG_DSDT) ||
        ACPI_COMPARE_NAMESEG (Signature, ACPI_SIG_OSDT) ||
        ACPI_COMPARE_NAMESEG (Signature, ACPI_SIG_SSDT) ||
        ACPI_COMPARE_NAMESEG (Signature, ACPI_SIG_FACS) ||
        ACPI_COMPARE_NAMESEG (Signature, ACPI_RSDP_NAME))
    {
        return (TRUE);
    }

    return (FALSE);
}