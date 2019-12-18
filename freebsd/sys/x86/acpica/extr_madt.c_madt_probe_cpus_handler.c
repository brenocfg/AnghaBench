#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  LapicFlags; int /*<<< orphan*/  Id; } ;
struct TYPE_6__ {int /*<<< orphan*/  LapicFlags; int /*<<< orphan*/  LocalApicId; } ;
struct TYPE_5__ {int Type; } ;
typedef  TYPE_1__ ACPI_SUBTABLE_HEADER ;
typedef  TYPE_2__ ACPI_MADT_LOCAL_X2APIC ;
typedef  TYPE_3__ ACPI_MADT_LOCAL_APIC ;

/* Variables and functions */
#define  ACPI_MADT_TYPE_LOCAL_APIC 129 
#define  ACPI_MADT_TYPE_LOCAL_X2APIC 128 
 int /*<<< orphan*/  madt_parse_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
madt_probe_cpus_handler(ACPI_SUBTABLE_HEADER *entry, void *arg)
{
	ACPI_MADT_LOCAL_APIC *proc;
	ACPI_MADT_LOCAL_X2APIC *x2apic;

	switch (entry->Type) {
	case ACPI_MADT_TYPE_LOCAL_APIC:
		proc = (ACPI_MADT_LOCAL_APIC *)entry;
		madt_parse_cpu(proc->Id, proc->LapicFlags);
		break;
	case ACPI_MADT_TYPE_LOCAL_X2APIC:
		x2apic = (ACPI_MADT_LOCAL_X2APIC *)entry;
		madt_parse_cpu(x2apic->LocalApicId, x2apic->LapicFlags);
		break;
	}
}