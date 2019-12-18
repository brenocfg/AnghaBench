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
typedef  TYPE_1__* int_entry_ptr ;
struct TYPE_3__ {int src_bus_id; int src_bus_irq; int dst_apic_int; int /*<<< orphan*/  dst_apic_id; int /*<<< orphan*/  int_type; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTENTRY_TYPE_INT ; 
 int /*<<< orphan*/  MPCT_ENTRY_INT ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mpt_generate_pci_int(int bus, int slot, int pin, int pirq_pin, int ioapic_irq,
    void *arg)
{
	int_entry_ptr *mpiep, mpie;

	mpiep = arg;
	mpie = *mpiep;
	memset(mpie, 0, sizeof(*mpie));

	/*
	 * This is always after another I/O interrupt entry, so cheat
	 * and fetch the I/O APIC ID from the prior entry.
	 */
	mpie->type = MPCT_ENTRY_INT;
	mpie->int_type = INTENTRY_TYPE_INT;
	mpie->src_bus_id = bus;
	mpie->src_bus_irq = slot << 2 | (pin - 1);
	mpie->dst_apic_id = mpie[-1].dst_apic_id;
	mpie->dst_apic_int = ioapic_irq;

	*mpiep = mpie + 1;
}