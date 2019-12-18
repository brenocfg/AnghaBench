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
typedef  int /*<<< orphan*/  uint32_t ;
struct bcm_gpio_softc {int sc_gpio_npins; TYPE_1__* sc_gpio_pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  gp_flags; int /*<<< orphan*/  gp_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_GPIO_LOCK (struct bcm_gpio_softc*) ; 
 int /*<<< orphan*/  BCM_GPIO_UNLOCK (struct bcm_gpio_softc*) ; 
 int /*<<< orphan*/  bcm_gpio_func_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_gpio_set_function (struct bcm_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bcm_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bcm_gpio_set_alternate(device_t dev, uint32_t pin, uint32_t nfunc)
{
	struct bcm_gpio_softc *sc;
	int i;

	sc = device_get_softc(dev);
	BCM_GPIO_LOCK(sc);

	/* Set the pin function. */
	bcm_gpio_set_function(sc, pin, nfunc);

	/* Update the pin flags. */
	for (i = 0; i < sc->sc_gpio_npins; i++) {
		if (sc->sc_gpio_pins[i].gp_pin == pin)
			break;
	}
	if (i < sc->sc_gpio_npins)
		sc->sc_gpio_pins[i].gp_flags = bcm_gpio_func_flag(nfunc);

        BCM_GPIO_UNLOCK(sc);
}