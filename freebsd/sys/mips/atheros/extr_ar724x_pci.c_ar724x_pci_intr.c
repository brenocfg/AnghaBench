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
typedef  int uint32_t ;
struct intr_event {int /*<<< orphan*/  ie_handlers; } ;
struct ar71xx_pci_softc {int /*<<< orphan*/ * sc_intr_counter; struct intr_event** sc_eventstab; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_CPU_DDR_FLUSH_PCIE ; 
 int AR71XX_PCI_IRQ_START ; 
 int AR724X_PCI_INTR_DEV0 ; 
 int /*<<< orphan*/  AR724X_PCI_INTR_MASK ; 
 int /*<<< orphan*/  AR724X_PCI_INTR_STATUS ; 
 int ATH_READ_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ CK_SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int FILTER_HANDLED ; 
 int FILTER_STRAY ; 
 int /*<<< orphan*/  ar71xx_device_flush_ddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_event_handle (struct intr_event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mips_intrcnt_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
ar724x_pci_intr(void *arg)
{
	struct ar71xx_pci_softc *sc = arg;
	struct intr_event *event;
	uint32_t reg, irq, mask;


	reg = ATH_READ_REG(AR724X_PCI_INTR_STATUS);
	mask = ATH_READ_REG(AR724X_PCI_INTR_MASK);
	/*
	 * Handle only unmasked interrupts
	 */
	reg &= mask;
	if (reg & AR724X_PCI_INTR_DEV0) {

		irq = AR71XX_PCI_IRQ_START;
		event = sc->sc_eventstab[irq];
		if (!event || CK_SLIST_EMPTY(&event->ie_handlers)) {
			printf("Stray IRQ %d\n", irq);
			return (FILTER_STRAY);
		}

		/* Flush pending memory transactions */
		ar71xx_device_flush_ddr(AR71XX_CPU_DDR_FLUSH_PCIE);

		/* TODO: frame instead of NULL? */
		intr_event_handle(event, NULL);
		mips_intrcnt_inc(sc->sc_intr_counter[irq]);
	}

	return (FILTER_HANDLED);
}