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
typedef  size_t u_int ;
struct TYPE_2__ {scalar_t__ lpi_free; size_t lpi_base; size_t lpi_num; int /*<<< orphan*/  lpi_busy; } ;
struct its_dev {TYPE_1__ lpis; } ;
struct intr_irqsrc {int dummy; } ;
struct gicv3_its_softc {struct gicv3_its_irqsrc* sc_irqs; } ;
struct gicv3_its_irqsrc {struct its_dev* gi_its_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct gicv3_its_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct its_dev* its_device_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t pci_msix_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gicv3_its_alloc_msix(device_t dev, device_t child, device_t *pic,
    struct intr_irqsrc **isrcp)
{
	struct gicv3_its_softc *sc;
	struct gicv3_its_irqsrc *girq;
	struct its_dev *its_dev;
	u_int nvecs, irq;

	nvecs = pci_msix_count(child);
	its_dev = its_device_get(dev, child, nvecs);
	if (its_dev == NULL)
		return (ENXIO);

	KASSERT(its_dev->lpis.lpi_free > 0,
	    ("gicv3_its_alloc_msix: No free LPIs"));
	sc = device_get_softc(dev);
	irq = its_dev->lpis.lpi_base + its_dev->lpis.lpi_num -
	    its_dev->lpis.lpi_free;
	its_dev->lpis.lpi_free--;
	its_dev->lpis.lpi_busy++;
	girq = &sc->sc_irqs[irq];
	girq->gi_its_dev = its_dev;

	*pic = dev;
	*isrcp = (struct intr_irqsrc *)girq;

	return (0);
}