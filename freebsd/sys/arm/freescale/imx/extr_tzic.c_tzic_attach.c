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
struct tzic_softc {int /*<<< orphan*/ * tzicregs; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTCNTL_EN ; 
 int INTCNTL_NSEN ; 
 int INTCNTL_NSEN_MASK ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TZIC_ENCLEAR (int) ; 
 int /*<<< orphan*/  TZIC_INTCNTL ; 
 int /*<<< orphan*/  TZIC_INTSEC (int) ; 
 int /*<<< orphan*/  TZIC_PRIOMASK ; 
 int /*<<< orphan*/  TZIC_PRIORITY (int) ; 
 int /*<<< orphan*/  TZIC_SYNCCTRL ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct tzic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ tzic_pic_attach (struct tzic_softc*) ; 
 struct tzic_softc* tzic_sc ; 
 int /*<<< orphan*/  tzic_write_4 (struct tzic_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
tzic_attach(device_t dev)
{
	struct tzic_softc *sc = device_get_softc(dev);
	int i;

	if (tzic_sc)
		return (ENXIO);
	tzic_sc = sc;
	sc->dev = dev;

	i = 0;
	sc->tzicregs = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &i,
	    RF_ACTIVE);
	if (sc->tzicregs == NULL) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* route all interrupts to IRQ.  secure interrupts are for FIQ */
	for (i = 0; i < 4; i++)
		tzic_write_4(sc, TZIC_INTSEC(i), 0xffffffff);

	/* disable all interrupts */
	for (i = 0; i < 4; i++)
		tzic_write_4(sc, TZIC_ENCLEAR(i), 0xffffffff);

	/* Set all interrupts to priority 0 (max). */
	for (i = 0; i < 128 / 4; ++i)
		tzic_write_4(sc, TZIC_PRIORITY(i), 0);

	/*
	 * Set priority mask to lowest (unmasked) prio, set synchronizer to
	 * low-latency mode (as opposed to low-power), enable the controller.
	 */
	tzic_write_4(sc, TZIC_PRIOMASK, 0xff);
	tzic_write_4(sc, TZIC_SYNCCTRL, 0);
	tzic_write_4(sc, TZIC_INTCNTL, INTCNTL_NSEN_MASK|INTCNTL_NSEN|INTCNTL_EN);

	/* Register as a root pic. */
	if (tzic_pic_attach(sc) != 0) {
		device_printf(dev, "could not attach PIC\n");
		return (ENXIO);
	}

	return (0);
}