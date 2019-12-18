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
struct resource {int dummy; } ;
struct mtk_pci_softc {int sc_irq_start; int sc_irq_end; int /*<<< orphan*/ ** sc_eventstab; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 struct mtk_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int intr_event_remove_handler (void*) ; 
 int /*<<< orphan*/  mtk_pci_mask_irq (void*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int rman_get_start (struct resource*) ; 

__attribute__((used)) static int
mtk_pci_teardown_intr(device_t dev, device_t child, struct resource *ires,
	void *cookie)
{
	struct mtk_pci_softc *sc = device_get_softc(dev);
	int irq, result, irqidx;

	irq = rman_get_start(ires);
	if (irq < sc->sc_irq_start || irq > sc->sc_irq_end)
		return (EINVAL);

	irqidx = irq - sc->sc_irq_start;
	if (sc->sc_eventstab[irqidx] == NULL)
		panic("Trying to teardown unoccupied IRQ");

	mtk_pci_mask_irq((void*)irq);

	result = intr_event_remove_handler(cookie);
	if (!result)
		sc->sc_eventstab[irqidx] = NULL;
	

	return (result);
}