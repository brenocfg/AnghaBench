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
struct TYPE_2__ {int /*<<< orphan*/  gp_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_GPIO_BANK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_GPCLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_GPSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_LOCK (struct bcm_gpio_softc*) ; 
 int /*<<< orphan*/  BCM_GPIO_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_UNLOCK (struct bcm_gpio_softc*) ; 
 int /*<<< orphan*/  BCM_GPIO_WRITE (struct bcm_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ bcm_gpio_pin_is_ro (struct bcm_gpio_softc*,int /*<<< orphan*/ ) ; 
 struct bcm_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcm_gpio_pin_set(device_t dev, uint32_t pin, unsigned int value)
{
	struct bcm_gpio_softc *sc = device_get_softc(dev);
	uint32_t bank, reg;
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
	if (value)
		reg = BCM_GPIO_GPSET(bank);
	else
		reg = BCM_GPIO_GPCLR(bank);
	BCM_GPIO_WRITE(sc, reg, BCM_GPIO_MASK(pin));
	BCM_GPIO_UNLOCK(sc);

	return (0);
}