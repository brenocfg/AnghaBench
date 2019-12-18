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
struct octeon_pmc_softc {int /*<<< orphan*/ * octeon_pmc_irq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_MISC ; 
 int OCTEON_PMC_IRQ ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,int,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct octeon_pmc_softc*,int /*<<< orphan*/ *) ; 
 struct octeon_pmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  octeon_pmc_intr ; 

__attribute__((used)) static int
octeon_pmc_attach(device_t dev)
{
	struct octeon_pmc_softc *sc;
	int error;
	int rid;

	sc = device_get_softc(dev);

	rid = 0;
	sc->octeon_pmc_irq = bus_alloc_resource(dev, 
	    SYS_RES_IRQ, &rid, OCTEON_PMC_IRQ,
	    OCTEON_PMC_IRQ, 1, RF_ACTIVE);

	if (sc->octeon_pmc_irq == NULL) {
		device_printf(dev, "could not allocate irq%d\n", OCTEON_PMC_IRQ);
		return (ENXIO);
	}

	error = bus_setup_intr(dev, sc->octeon_pmc_irq, 
	    INTR_TYPE_MISC, octeon_pmc_intr, NULL, sc, NULL);
	if (error != 0) {
		device_printf(dev, "bus_setup_intr failed: %d\n", error);
		return (error);
	}

	return (0);
}