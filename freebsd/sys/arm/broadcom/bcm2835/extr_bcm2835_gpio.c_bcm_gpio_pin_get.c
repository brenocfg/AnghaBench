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
typedef  scalar_t__ uint32_t ;
struct bcm_gpio_softc {int sc_gpio_npins; TYPE_1__* sc_gpio_pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ gp_pin; } ;

/* Variables and functions */
 scalar_t__ BCM_GPIO_BANK (scalar_t__) ; 
 int /*<<< orphan*/  BCM_GPIO_GPLEV (scalar_t__) ; 
 int /*<<< orphan*/  BCM_GPIO_LOCK (struct bcm_gpio_softc*) ; 
 scalar_t__ BCM_GPIO_MASK (scalar_t__) ; 
 scalar_t__ BCM_GPIO_READ (struct bcm_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_UNLOCK (struct bcm_gpio_softc*) ; 
 int EINVAL ; 
 struct bcm_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcm_gpio_pin_get(device_t dev, uint32_t pin, unsigned int *val)
{
	struct bcm_gpio_softc *sc = device_get_softc(dev);
	uint32_t bank, reg_data;
	int i;

	for (i = 0; i < sc->sc_gpio_npins; i++) {
		if (sc->sc_gpio_pins[i].gp_pin == pin)
			break;
	}
	if (i >= sc->sc_gpio_npins)
		return (EINVAL);
	bank = BCM_GPIO_BANK(pin);
	BCM_GPIO_LOCK(sc);
	reg_data = BCM_GPIO_READ(sc, BCM_GPIO_GPLEV(bank));
	BCM_GPIO_UNLOCK(sc);
	*val = (reg_data & BCM_GPIO_MASK(pin)) ? 1 : 0;

	return (0);
}