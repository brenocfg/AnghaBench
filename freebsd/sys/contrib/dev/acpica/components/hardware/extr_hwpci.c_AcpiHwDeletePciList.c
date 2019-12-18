#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* Next; } ;
typedef  TYPE_1__ ACPI_PCI_DEVICE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (TYPE_1__*) ; 

__attribute__((used)) static void
AcpiHwDeletePciList (
    ACPI_PCI_DEVICE         *ListHead)
{
    ACPI_PCI_DEVICE         *Next;
    ACPI_PCI_DEVICE         *Previous;


    Next = ListHead;
    while (Next)
    {
        Previous = Next;
        Next = Previous->Next;
        ACPI_FREE (Previous);
    }
}