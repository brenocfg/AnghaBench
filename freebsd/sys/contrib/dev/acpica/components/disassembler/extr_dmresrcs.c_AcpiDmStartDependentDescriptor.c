#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_4__ {int /*<<< orphan*/  Flags; } ;
struct TYPE_5__ {TYPE_1__ StartDpf; } ;
typedef  TYPE_2__ AML_RESOURCE ;
typedef  int /*<<< orphan*/  ACPI_OP_WALK_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_EXTRACT_2BIT_FLAG (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ACPI_GET_2BIT_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmIndent (int) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 

void
AcpiDmStartDependentDescriptor (
    ACPI_OP_WALK_INFO       *Info,
    AML_RESOURCE            *Resource,
    UINT32                  Length,
    UINT32                  Level)
{

    AcpiDmIndent (Level);

    if (Length & 1)
    {
        AcpiOsPrintf ("StartDependentFn (0x%2.2X, 0x%2.2X)\n",
            (UINT32) ACPI_GET_2BIT_FLAG (Resource->StartDpf.Flags),
            (UINT32) ACPI_EXTRACT_2BIT_FLAG (Resource->StartDpf.Flags, 2));
    }
    else
    {
        AcpiOsPrintf ("StartDependentFnNoPri ()\n");
    }

    AcpiDmIndent (Level);
    AcpiOsPrintf ("{\n");
}