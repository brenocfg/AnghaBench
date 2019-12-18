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
struct prt_lookup_request {scalar_t__ pr_slot; scalar_t__ pr_pin; TYPE_1__* pr_entry; } ;
struct TYPE_3__ {scalar_t__ Pin; int /*<<< orphan*/  Address; } ;
typedef  TYPE_1__ ACPI_PCI_ROUTING_TABLE ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_PCI_SLOT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
prt_lookup_device(ACPI_PCI_ROUTING_TABLE *entry, void *arg)
{
    struct prt_lookup_request *pr;

    pr = (struct prt_lookup_request *)arg;
    if (pr->pr_entry != NULL)
	return;

    /*
     * Compare the slot number (high word of Address) and pin number
     * (note that ACPI uses 0 for INTA) to check for a match.
     *
     * Note that the low word of the Address field (function number)
     * is required by the specification to be 0xffff.  We don't risk
     * checking it here.
     */
    if (ACPI_ADR_PCI_SLOT(entry->Address) == pr->pr_slot &&
	entry->Pin == pr->pr_pin)
	    pr->pr_entry = entry;
}