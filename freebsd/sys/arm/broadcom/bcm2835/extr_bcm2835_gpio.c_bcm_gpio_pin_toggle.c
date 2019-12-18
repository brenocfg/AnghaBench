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
typedef  int uint32_t ;
struct bcm_gpio_softc {int sc_gpio_npins; TYPE_1__* sc_gpio_pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int gp_pin; } ;

/* Variables and functions */
 int BCM_GPIO_BANK (int) ; 
 int BCM_GPIO_GPCLR (int) ; 
 int /*<<< orphan*/  BCM_GPIO_GPLEV (int) ; 
 int BCM_GPIO_GPSET (int) ; 
 int /*<<< orphan*/  BCM_GPIO_LOCK (struct bcm_gpio_softc*) ; 
 int BCM_GPIO_MASK (int) ; 
 int BCM_GPIO_READ (struct bcm_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_UNLOCK (struct bcm_gpio_softc*) ; 
 int /*<<< orphan*/  BCM_GPIO_WRITE (struct bcm_gpio_softc*,int,int) ; 
 int EINVAL ; 
 scalar_t__ bcm_gpio_pin_is_ro (struct bcm_gpio_softc*,int) ; 
 struct bcm_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcm_gpio_pin_toggle(device_t dev, uint32_t pin)
{
	struct bcm_gpio_softc *sc = device_get_softc(dev);
	uint32_t bank, data, reg;
	int i;

	for (i = 0; i < sc->sc_gpio_npins; i++) {
		if (sc->sc_gpio_pins[i].gp_pin == pin)
			break;
	}
	if (i >= sc->sc_gpio_npins)
		return (EINVAL);
	/* We never write to read-only/reserved pins. */
	if (bcm_gpio_pin_is_ro(sc, pin))
		return (EINVAL);
	BCM_GPIO_LOCK(sc);
	bank = BCM_GPIO_BANK(pin);
	data = BCM_GPIO_READ(sc, BCM_GPIO_GPLEV(bank));
	if (data & BCM_GPIO_MASK(pin))
		reg = BCM_GPIO_GPCLR(bank);
	else
		reg = BCM_GPIO_GPSET(bank);
	BCM_GPIO_WRITE(sc, reg, BCM_GPIO_MASK(pin));
	BCM_GPIO_UNLOCK(sc);

	return (0);
}