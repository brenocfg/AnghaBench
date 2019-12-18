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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct octeon_gpio_softc {int gpio_npins; TYPE_1__* gpio_pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int gp_pin; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_LOCK (struct octeon_gpio_softc*) ; 
 int /*<<< orphan*/  GPIO_UNLOCK (struct octeon_gpio_softc*) ; 
 int /*<<< orphan*/  cvmx_gpio_clear (int) ; 
 int cvmx_gpio_read () ; 
 int /*<<< orphan*/  cvmx_gpio_set (int) ; 
 struct octeon_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
octeon_gpio_pin_toggle(device_t dev, uint32_t pin)
{
	int i;
	uint64_t state;
	struct octeon_gpio_softc *sc = device_get_softc(dev);

	for (i = 0; i < sc->gpio_npins; i++) {
		if (sc->gpio_pins[i].gp_pin == pin)
			break;
	}

	if (i >= sc->gpio_npins)
		return (EINVAL);

	GPIO_LOCK(sc);
	/*
	 * XXX: Need to check if read returns actual state of output 
	 * pins or we need to keep this information by ourself
	 */
	state = cvmx_gpio_read();
	if (state & (1 << pin))
		cvmx_gpio_clear(1 << pin);
	else
		cvmx_gpio_set(1 << pin);
	GPIO_UNLOCK(sc);

	return (0);
}