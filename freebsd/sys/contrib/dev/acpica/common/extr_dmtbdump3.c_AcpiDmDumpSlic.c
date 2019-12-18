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
struct TYPE_4__ {scalar_t__ Length; } ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiDmDumpTable (scalar_t__,int,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmTableInfoSlic ; 

void
AcpiDmDumpSlic (
    ACPI_TABLE_HEADER       *Table)
{

    (void) AcpiDmDumpTable (Table->Length, sizeof (ACPI_TABLE_HEADER), Table,
        Table->Length - sizeof (*Table), AcpiDmTableInfoSlic);
}