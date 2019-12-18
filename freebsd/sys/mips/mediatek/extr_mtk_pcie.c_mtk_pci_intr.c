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
typedef  unsigned int uint32_t ;
struct mtk_pci_softc {unsigned int sc_irq_start; unsigned int sc_irq_end; struct intr_event** sc_eventstab; } ;
struct intr_event {int /*<<< orphan*/  ie_handlers; } ;

/* Variables and functions */
 scalar_t__ CK_SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  MTK_PCI_PCIINT ; 
 unsigned int MT_READ32 (struct mtk_pci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_event_handle (struct intr_event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 

__attribute__((used)) static int
mtk_pci_intr(void *arg)
{
	struct mtk_pci_softc *sc = arg;
	struct intr_event *event;
	uint32_t reg, irq, irqidx;

	reg = MT_READ32(sc, MTK_PCI_PCIINT);

	for (irq = sc->sc_irq_start; irq <= sc->sc_irq_end; irq++) {
		if (reg & (1u<<irq)) {
			irqidx = irq - sc->sc_irq_start;
			event = sc->sc_eventstab[irqidx];
			if (!event || CK_SLIST_EMPTY(&event->ie_handlers)) {
				if (irq != 0)
					printf("Stray PCI IRQ %d\n", irq);
				continue;
			}

			intr_event_handle(event, NULL);
		}
	}

	return (FILTER_HANDLED);
}