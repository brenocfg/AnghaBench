#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_char ;
struct pci_route_interrupt_args {scalar_t__ bus; int irq; int vector; } ;
typedef  TYPE_1__* int_entry_ptr ;
struct TYPE_2__ {scalar_t__ src_bus_id; int src_bus_irq; size_t dst_apic_id; int /*<<< orphan*/  dst_apic_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ MPCT_ENTRY_INT ; 
 int ioapic_get_vector (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** ioapics ; 

__attribute__((used)) static void
mptable_pci_route_interrupt_handler(u_char *entry, void *arg)
{
	struct pci_route_interrupt_args *args;
	int_entry_ptr intr;
	int vector;

	if (*entry != MPCT_ENTRY_INT)
		return;
	intr = (int_entry_ptr)entry;
	args = (struct pci_route_interrupt_args *)arg;
	if (intr->src_bus_id != args->bus || intr->src_bus_irq != args->irq)
		return;

	/* Make sure the APIC maps to a known APIC. */
	KASSERT(ioapics[intr->dst_apic_id] != NULL,
	    ("No I/O APIC %d to route interrupt to", intr->dst_apic_id));

	/*
	 * Look up the vector for this APIC / pin combination.  If we
	 * have previously matched an entry for this PCI IRQ but it
	 * has the same vector as this entry, just return.  Otherwise,
	 * we use the vector for this APIC / pin combination.
	 */
	vector = ioapic_get_vector(ioapics[intr->dst_apic_id],
	    intr->dst_apic_int);
	if (args->vector == vector)
		return;
	KASSERT(args->vector == -1,
	    ("Multiple IRQs for PCI interrupt %d.%d.INT%c: %d and %d\n",
	    args->bus, args->irq >> 2, 'A' + (args->irq & 0x3), args->vector,
	    vector));
	args->vector = vector;
}