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
struct mtk_pci_softc {int sc_irq_start; int sc_irq_end; struct intr_event** sc_eventstab; } ;
struct intr_event {int dummy; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct mtk_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_event_add_handler (struct intr_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int,void**) ; 
 int intr_event_create (struct intr_event**,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (void*),int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  intr_priority (int) ; 
 int /*<<< orphan*/  mtk_pci_mask_irq ; 
 int /*<<< orphan*/  mtk_pci_unmask_irq (void*) ; 
 int rman_get_start (struct resource*) ; 

__attribute__((used)) static int
mtk_pci_setup_intr(device_t bus, device_t child, struct resource *ires,
	int flags, driver_filter_t *filt, driver_intr_t *handler,
	void *arg, void **cookiep)
{
	struct mtk_pci_softc *sc = device_get_softc(bus);
	struct intr_event *event;
	int irq, error, irqidx;

	irq = rman_get_start(ires);

	if (irq < sc->sc_irq_start || irq > sc->sc_irq_end)
		return (EINVAL);

	irqidx = irq - sc->sc_irq_start;

	event = sc->sc_eventstab[irqidx];
	if (event == NULL) {
		error = intr_event_create(&event, (void *)irq, 0, irq,
		    mtk_pci_mask_irq, mtk_pci_unmask_irq, NULL, NULL,
		    "pci intr%d:", irq);

		if (error == 0) {
			sc->sc_eventstab[irqidx] = event;
		}
		else {
			return (error);
		}
	}

	intr_event_add_handler(event, device_get_nameunit(child), filt,
		handler, arg, intr_priority(flags), flags, cookiep);

	mtk_pci_unmask_irq((void*)irq);

	return (0);
}