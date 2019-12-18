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
struct dwgpio_softc {int gpio_npins; int /*<<< orphan*/  port; TYPE_1__* gpio_pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ gp_pin; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_LOCK (struct dwgpio_softc*) ; 
 int /*<<< orphan*/  GPIO_SWPORT_DR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_UNLOCK (struct dwgpio_softc*) ; 
 int READ4 (struct dwgpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct dwgpio_softc*,int /*<<< orphan*/ ,int) ; 
 struct dwgpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dwgpio_pin_set(device_t dev, uint32_t pin, unsigned int value)
{
	struct dwgpio_softc *sc;
	int reg;
	int i;

	sc = device_get_softc(dev);

	for (i = 0; i < sc->gpio_npins; i++) {
		if (sc->gpio_pins[i].gp_pin == pin)
			break;
	}

	if (i >= sc->gpio_npins)
		return (EINVAL);

	GPIO_LOCK(sc);
	reg = READ4(sc, GPIO_SWPORT_DR(sc->port));
	if (value)
		reg |= (1 << i);
	else
		reg &= ~(1 << i);
	WRITE4(sc, GPIO_SWPORT_DR(sc->port), reg);
	GPIO_UNLOCK(sc);

	return (0);
}