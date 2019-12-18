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
struct pmu_softc {int /*<<< orphan*/ * sc_irq; scalar_t__ sc_irqrid; int /*<<< orphan*/  sc_ih; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_ENTROPY ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pmu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pmu_intr ; 

__attribute__((used)) static int
setup_pmu_intr(device_t dev, device_t extint)
{
	struct pmu_softc *sc;
	sc = device_get_softc(dev);

	sc->sc_irqrid = 0;
	sc->sc_irq = bus_alloc_resource_any(extint, SYS_RES_IRQ, &sc->sc_irqrid,
           	RF_ACTIVE);
        if (sc->sc_irq == NULL) {
                device_printf(dev, "could not allocate interrupt\n");
                return (ENXIO);
        }

	if (bus_setup_intr(dev, sc->sc_irq, INTR_TYPE_MISC | INTR_MPSAFE 
	    | INTR_ENTROPY, NULL, pmu_intr, dev, &sc->sc_ih) != 0) {
                device_printf(dev, "could not setup interrupt\n");
                bus_release_resource(dev, SYS_RES_IRQ, sc->sc_irqrid,
                    sc->sc_irq);
                return (ENXIO);
        }

	return (0);
}