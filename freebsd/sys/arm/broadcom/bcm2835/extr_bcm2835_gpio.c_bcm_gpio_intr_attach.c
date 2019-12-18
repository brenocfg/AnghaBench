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
struct bcm_gpio_softc {int /*<<< orphan*/ * sc_intrhand; int /*<<< orphan*/ ** sc_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  bcm_gpio_intr_bank0 ; 
 int /*<<< orphan*/  bcm_gpio_intr_bank1 ; 
 scalar_t__ bcm_gpio_pic_attach (struct bcm_gpio_softc*) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bcm_gpio_softc*,int /*<<< orphan*/ *) ; 
 struct bcm_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
bcm_gpio_intr_attach(device_t dev)
{
	struct bcm_gpio_softc *sc;

	/*
	 *  Only first two interrupt lines are used. Third line is
	 *  mirrored second line and forth line is common for all banks.
	 */
	sc = device_get_softc(dev);
	if (sc->sc_res[1] == NULL || sc->sc_res[2] == NULL)
		return (-1);

	if (bcm_gpio_pic_attach(sc) != 0) {
		device_printf(dev, "unable to attach PIC\n");
		return (-1);
	}
	if (bus_setup_intr(dev, sc->sc_res[1], INTR_TYPE_MISC | INTR_MPSAFE,
	    bcm_gpio_intr_bank0, NULL, sc, &sc->sc_intrhand[0]) != 0)
		return (-1);
	if (bus_setup_intr(dev, sc->sc_res[2], INTR_TYPE_MISC | INTR_MPSAFE,
	    bcm_gpio_intr_bank1, NULL, sc, &sc->sc_intrhand[1]) != 0)
		return (-1);

	return (0);
}