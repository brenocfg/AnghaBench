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
typedef  size_t u_int ;
struct bcm_mips74k_softc {int /*<<< orphan*/ * mem; scalar_t__ mem_rid; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 size_t BCM_MIPS74K_GET_TIMER_IRQ () ; 
 int /*<<< orphan*/  BCM_MIPS74K_INTR_SEL (size_t) ; 
 size_t BCM_MIPS74K_NUM_INTR ; 
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bcm_mips74k_pic_intr ; 
 int bcm_mips_attach (int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bcm_mips74k_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
bcm_mips74k_attach(device_t dev)
{
	struct bcm_mips74k_softc	*sc;
	u_int				 timer_irq;
	int				 error;

	sc = device_get_softc(dev);
	sc->dev = dev;

	/* Allocate our core's register block */
	sc->mem_rid = 0;
	sc->mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->mem_rid,
	    RF_ACTIVE);
	if (sc->mem == NULL) {
		device_printf(dev, "failed to allocate cpu register block\n");
		return (ENXIO);
	}

	/* Clear interrupt map */
	timer_irq = BCM_MIPS74K_GET_TIMER_IRQ();
	for (size_t i = 0; i < BCM_MIPS74K_NUM_INTR; i++) {
		/* We don't use the timer IRQ; leave it routed to the
		 * MIPS CPU */
		if (i == timer_irq)
			continue;

		bus_write_4(sc->mem, BCM_MIPS74K_INTR_SEL(i), 0);
	}

	/* Initialize the generic BHND MIPS driver state */
	error = bcm_mips_attach(dev, BCM_MIPS74K_NUM_INTR, timer_irq,
	    bcm_mips74k_pic_intr);
	if (error) {
		bus_release_resource(dev, SYS_RES_MEMORY, sc->mem_rid, sc->mem);
		return (error);
	}

	return (0);
}