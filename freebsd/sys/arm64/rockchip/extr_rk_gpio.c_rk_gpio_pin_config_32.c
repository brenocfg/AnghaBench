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
typedef  scalar_t__ uint32_t ;
struct rk_gpio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GPIO_PIN_INPUT ; 
 scalar_t__ GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  RK_GPIO_LOCK (struct rk_gpio_softc*) ; 
 scalar_t__ RK_GPIO_READ (struct rk_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RK_GPIO_SWPORTA_DDR ; 
 int /*<<< orphan*/  RK_GPIO_UNLOCK (struct rk_gpio_softc*) ; 
 int /*<<< orphan*/  RK_GPIO_WRITE (struct rk_gpio_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct rk_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rk_gpio_pin_config_32(device_t dev, uint32_t first_pin, uint32_t num_pins,
    uint32_t *pin_flags)
{
	struct rk_gpio_softc *sc;
	uint32_t reg, set, mask, flags;
	int i;

	sc = device_get_softc(dev);

	if (first_pin != 0 || num_pins > 32)
		return (EINVAL);

	set = 0;
	mask = 0;
	for (i = 0; i < num_pins; i++) {
		mask = (mask << 1) | 1;
		flags = pin_flags[i];
		if (flags & GPIO_PIN_INPUT) {
			set &= ~(1 << i);
		} else if (flags & GPIO_PIN_OUTPUT) {
			set |= (1 << i);
		}
	}

	RK_GPIO_LOCK(sc);
	reg = RK_GPIO_READ(sc, RK_GPIO_SWPORTA_DDR);
	reg &= ~mask;
	reg |= set;
	RK_GPIO_WRITE(sc, RK_GPIO_SWPORTA_DDR, reg);
	RK_GPIO_UNLOCK(sc);

	return (0);
}