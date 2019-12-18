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
struct jz4780_pic_softc {int /*<<< orphan*/ * pic_res; int /*<<< orphan*/  pic_intrhand; int /*<<< orphan*/  pic_irqs; int /*<<< orphan*/  nirqs; int /*<<< orphan*/  pic_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_CLK ; 
 int /*<<< orphan*/  JZ_ICMR0 ; 
 int /*<<< orphan*/  JZ_ICMR1 ; 
 int /*<<< orphan*/  WRITE4 (struct jz4780_pic_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct jz4780_pic_softc*,int /*<<< orphan*/ *) ; 
 struct jz4780_pic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  intr_pic_deregister (int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/  jz4780_pic_intr ; 
 scalar_t__ jz4780_pic_register_isrcs (struct jz4780_pic_softc*) ; 
 int /*<<< orphan*/  jz4780_pic_spec ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ ) ; 
 intptr_t pic_xref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jz4780_pic_attach(device_t dev)
{
	struct jz4780_pic_softc *sc;
	intptr_t xref;

	xref = pic_xref(dev);

	sc = device_get_softc(dev);

	if (bus_alloc_resources(dev, jz4780_pic_spec, sc->pic_res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	sc->pic_dev = dev;

	/* Set the number of interrupts */
	sc->nirqs = nitems(sc->pic_irqs);

	/* Mask all interrupts */
	WRITE4(sc, JZ_ICMR0, 0xFFFFFFFF);
	WRITE4(sc, JZ_ICMR1, 0xFFFFFFFF);

	/* Register the interrupts */
	if (jz4780_pic_register_isrcs(sc) != 0) {
		device_printf(dev, "could not register PIC ISRCs\n");
		goto cleanup;
	}

	/*
	 * Now, when everything is initialized, it's right time to
	 * register interrupt controller to interrupt framefork.
	 */
	if (intr_pic_register(dev, xref) == NULL) {
		device_printf(dev, "could not register PIC\n");
		goto cleanup;
	}

	if (bus_setup_intr(dev, sc->pic_res[1], INTR_TYPE_CLK,
	    jz4780_pic_intr, NULL, sc, &sc->pic_intrhand)) {
		device_printf(dev, "could not setup irq handler\n");
		intr_pic_deregister(dev, xref);
		goto cleanup;
	}

	return (0);

cleanup:
	bus_release_resources(dev, jz4780_pic_spec, sc->pic_res);

	return(ENXIO);
}