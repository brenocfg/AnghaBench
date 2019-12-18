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
struct slotinfo {struct intxinfo* si_intpins; } ;
struct intxinfo {scalar_t__ ii_count; int /*<<< orphan*/  ii_ioapic_irq; int /*<<< orphan*/  ii_pirq_pin; } ;
struct businfo {struct slotinfo* slotinfo; } ;
typedef  int /*<<< orphan*/  (* pci_lintr_cb ) (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;

/* Variables and functions */
 int MAXSLOTS ; 
 struct businfo** pci_businfo ; 

void
pci_walk_lintr(int bus, pci_lintr_cb cb, void *arg)
{
	struct businfo *bi;
	struct slotinfo *si;
	struct intxinfo *ii;
	int slot, pin;

	if ((bi = pci_businfo[bus]) == NULL)
		return;

	for (slot = 0; slot < MAXSLOTS; slot++) {
		si = &bi->slotinfo[slot];
		for (pin = 0; pin < 4; pin++) {
			ii = &si->si_intpins[pin];
			if (ii->ii_count != 0)
				cb(bus, slot, pin + 1, ii->ii_pirq_pin,
				    ii->ii_ioapic_irq, arg);
		}
	}
}