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
struct mips_pic_softc {int /*<<< orphan*/  pic_irqs; int /*<<< orphan*/  nirqs; int /*<<< orphan*/  pic_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 struct mips_pic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ intr_pic_claim_root (int /*<<< orphan*/ ,intptr_t,int /*<<< orphan*/ ,struct mips_pic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_pic_deregister (int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/  mips_pic_intr ; 
 scalar_t__ mips_pic_register_isrcs (struct mips_pic_softc*) ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ ) ; 
 struct mips_pic_softc* pic_sc ; 
 intptr_t pic_xref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mips_pic_attach(device_t dev)
{
	struct		mips_pic_softc *sc;
	intptr_t	xref = pic_xref(dev);

	if (pic_sc)
		return (ENXIO);

	sc = device_get_softc(dev);

	sc->pic_dev = dev;
	pic_sc = sc;

	/* Set the number of interrupts */
	sc->nirqs = nitems(sc->pic_irqs);

	/* Register the interrupts */
	if (mips_pic_register_isrcs(sc) != 0) {
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

	/* Claim our root controller role */
	if (intr_pic_claim_root(dev, xref, mips_pic_intr, sc, 0) != 0) {
		device_printf(dev, "could not set PIC as a root\n");
		intr_pic_deregister(dev, xref);
		goto cleanup;
	}

	return (0);

cleanup:
	return(ENXIO);
}