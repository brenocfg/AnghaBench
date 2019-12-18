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
 int EINVAL ; 
 int /*<<< orphan*/  GPIOMAXNAME ; 
 int /*<<< orphan*/  RK_GPIO_LOCK (struct rk_gpio_softc*) ; 
 int /*<<< orphan*/  RK_GPIO_UNLOCK (struct rk_gpio_softc*) ; 
 struct rk_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
rk_gpio_pin_getname(device_t dev, uint32_t pin, char *name)
{
	struct rk_gpio_softc *sc;

	sc = device_get_softc(dev);

	if (pin >= 32)
		return (EINVAL);

	RK_GPIO_LOCK(sc);
	snprintf(name, GPIOMAXNAME, "gpio%d", pin);
	RK_GPIO_UNLOCK(sc);

	return (0);
}