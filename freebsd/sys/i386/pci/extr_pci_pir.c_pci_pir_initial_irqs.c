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
typedef  scalar_t__ uint8_t ;
struct pci_link {scalar_t__ pl_irq; int pl_id; int pl_routed; } ;
struct PIR_intpin {int /*<<< orphan*/  link; } ;
struct PIR_entry {int pe_intpin; int pe_bus; int pe_device; } ;

/* Variables and functions */
 scalar_t__ NUM_ISA_INTERRUPTS ; 
 scalar_t__ PCI_INVALID_IRQ ; 
 struct pci_link* pci_pir_find_link (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_pir_search_irq (int,int,scalar_t__) ; 
 int /*<<< orphan*/  pci_pir_valid_irq (struct pci_link*,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,int,int,scalar_t__,int,...) ; 

__attribute__((used)) static void
pci_pir_initial_irqs(struct PIR_entry *entry, struct PIR_intpin *intpin,
    void *arg)
{
	struct pci_link *pci_link;
	uint8_t irq, pin;

	pin = intpin - entry->pe_intpin;
	pci_link = pci_pir_find_link(intpin->link);
	irq = pci_pir_search_irq(entry->pe_bus, entry->pe_device, pin);
	if (irq == PCI_INVALID_IRQ || irq == pci_link->pl_irq)
		return;

	/* Don't trust any BIOS IRQs greater than 15. */
	if (irq >= NUM_ISA_INTERRUPTS) {
		printf(
	"$PIR: Ignoring invalid BIOS IRQ %d from %d.%d.INT%c for link %#x\n",
		    irq, entry->pe_bus, entry->pe_device, pin + 'A',
		    pci_link->pl_id);
		return;
	}

	/*
	 * If we don't have an IRQ for this link yet, then we trust the
	 * BIOS, even if it seems invalid from the $PIR entries.
	 */
	if (pci_link->pl_irq == PCI_INVALID_IRQ) {
		if (!pci_pir_valid_irq(pci_link, irq))
			printf(
	"$PIR: Using invalid BIOS IRQ %d from %d.%d.INT%c for link %#x\n",
			    irq, entry->pe_bus, entry->pe_device, pin + 'A',
			    pci_link->pl_id);
		pci_link->pl_irq = irq;
		pci_link->pl_routed = 1;
		return;
	}

	/*
	 * We have an IRQ and it doesn't match the current IRQ for this
	 * link.  If the new IRQ is invalid, then warn about it and ignore
	 * it.  If the old IRQ is invalid and the new IRQ is valid, then
	 * prefer the new IRQ instead.  If both IRQs are valid, then just
	 * use the first one.  Note that if we ever get into this situation
	 * we are having to guess which setting the BIOS actually routed.
	 * Perhaps we should just give up instead.
	 */
	if (!pci_pir_valid_irq(pci_link, irq)) {
		printf(
		"$PIR: BIOS IRQ %d for %d.%d.INT%c is not valid for link %#x\n",
		    irq, entry->pe_bus, entry->pe_device, pin + 'A',
		    pci_link->pl_id);
	} else if (!pci_pir_valid_irq(pci_link, pci_link->pl_irq)) {
		printf(
"$PIR: Preferring valid BIOS IRQ %d from %d.%d.INT%c for link %#x to IRQ %d\n", 
		    irq, entry->pe_bus, entry->pe_device, pin + 'A',
		    pci_link->pl_id, pci_link->pl_irq);
		pci_link->pl_irq = irq;
		pci_link->pl_routed = 1;
	} else
		printf(
	"$PIR: BIOS IRQ %d for %d.%d.INT%c does not match link %#x irq %d\n",
		    irq, entry->pe_bus, entry->pe_device, pin + 'A',
		    pci_link->pl_id, pci_link->pl_irq);
}