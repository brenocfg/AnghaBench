#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct TYPE_3__* Next; int /*<<< orphan*/  Value; int /*<<< orphan*/  Type; int /*<<< orphan*/  InternalPath; } ;
typedef  TYPE_1__ ACPI_EXTERNAL_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiDmAddOneExternalToNamespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* AcpiGbl_ExternalList ; 

void
AcpiDmAddExternalListToNamespace (
    void)
{
    ACPI_EXTERNAL_LIST      *External = AcpiGbl_ExternalList;


    while (External)
    {
        AcpiDmAddOneExternalToNamespace (External->InternalPath,
            External->Type, External->Value);
        External = External->Next;
    }
}