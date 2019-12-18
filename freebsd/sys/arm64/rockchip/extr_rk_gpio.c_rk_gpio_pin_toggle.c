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
struct rk_gpio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  RK_GPIO_LOCK (struct rk_gpio_softc*) ; 
 int RK_GPIO_READ (struct rk_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RK_GPIO_SWPORTA_DR ; 
 int /*<<< orphan*/  RK_GPIO_UNLOCK (struct rk_gpio_softc*) ; 
 int /*<<< orphan*/  RK_GPIO_WRITE (struct rk_gpio_softc*,int /*<<< orphan*/ ,int) ; 
 struct rk_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rk_gpio_pin_toggle(device_t dev, uint32_t pin)
{
	struct rk_gpio_softc *sc;
	uint32_t reg;

	sc = device_get_softc(dev);

	RK_GPIO_LOCK(sc);
	reg = RK_GPIO_READ(sc, RK_GPIO_SWPORTA_DR);
	if (reg & (1 << pin))
		reg &= ~(1 << pin);
	else
		reg |= (1 << pin);
	RK_GPIO_WRITE(sc, RK_GPIO_SWPORTA_DR, reg);
	RK_GPIO_UNLOCK(sc);

	return (0);
}