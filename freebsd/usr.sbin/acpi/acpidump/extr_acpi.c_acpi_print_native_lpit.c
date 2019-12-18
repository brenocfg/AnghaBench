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
struct TYPE_4__ {int Flags; } ;
struct TYPE_5__ {int Residency; int Latency; scalar_t__ CounterFrequency; int /*<<< orphan*/  ResidencyCounter; TYPE_1__ Header; int /*<<< orphan*/  EntryTrigger; } ;
typedef  TYPE_2__ ACPI_LPIT_NATIVE ;

/* Variables and functions */
 int ACPI_LPIT_NO_COUNTER ; 
 int /*<<< orphan*/  acpi_print_gas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
acpi_print_native_lpit(ACPI_LPIT_NATIVE *nl)
{
	printf("\tEntryTrigger=");
	acpi_print_gas(&nl->EntryTrigger);
	printf("\tResidency=%u\n", nl->Residency);
	printf("\tLatency=%u\n", nl->Latency);
	if (nl->Header.Flags & ACPI_LPIT_NO_COUNTER)
		printf("\tResidencyCounter=Not Present");
	else {
		printf("\tResidencyCounter=");
		acpi_print_gas(&nl->ResidencyCounter);
	}
	if (nl->CounterFrequency)
		printf("\tCounterFrequency=%ju\n", nl->CounterFrequency);
	else
		printf("\tCounterFrequency=TSC\n");
}