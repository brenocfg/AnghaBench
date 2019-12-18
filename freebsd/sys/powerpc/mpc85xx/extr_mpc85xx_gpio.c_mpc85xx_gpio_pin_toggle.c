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
typedef  int uint32_t ;
struct mpc85xx_gpio_softc {int /*<<< orphan*/  out_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_LOCK (struct mpc85xx_gpio_softc*) ; 
 int /*<<< orphan*/  GPIO_UNLOCK (struct mpc85xx_gpio_softc*) ; 
 int /*<<< orphan*/  VALID_PIN (int) ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mpc85xx_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpc85xx_gpio_pin_toggle(device_t dev, uint32_t pin)
{
	struct mpc85xx_gpio_softc *sc = device_get_softc(dev);
	uint32_t val;

	if (!VALID_PIN(pin))
		return (EINVAL);

	GPIO_LOCK(sc);

	val = bus_read_4(sc->out_res, 0);
	val ^= (1 << (31 - pin));
	bus_write_4(sc->out_res, 0, val);
	
	GPIO_UNLOCK(sc);

	return (0);
}