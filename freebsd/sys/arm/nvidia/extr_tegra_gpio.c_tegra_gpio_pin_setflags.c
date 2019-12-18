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
typedef  size_t uint32_t ;
struct tegra_gpio_softc {size_t gpio_npins; int /*<<< orphan*/ * gpio_pins; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_CNF ; 
 int /*<<< orphan*/  GPIO_LOCK (struct tegra_gpio_softc*) ; 
 int /*<<< orphan*/  GPIO_MSK_CNF ; 
 int /*<<< orphan*/  GPIO_UNLOCK (struct tegra_gpio_softc*) ; 
 struct tegra_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int gpio_read (struct tegra_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_write_masked (struct tegra_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tegra_gpio_pin_configure (struct tegra_gpio_softc*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
tegra_gpio_pin_setflags(device_t dev, uint32_t pin, uint32_t flags)
{
	struct tegra_gpio_softc *sc;
	int cnf;

	sc = device_get_softc(dev);
	if (pin >= sc->gpio_npins)
		return (EINVAL);

	GPIO_LOCK(sc);
	cnf = gpio_read(sc, GPIO_CNF,  &sc->gpio_pins[pin]);
	if (cnf == 0) {
		/* XXX - allow this for while ....
		GPIO_UNLOCK(sc);
		return (ENXIO);
		*/
		gpio_write_masked(sc, GPIO_MSK_CNF,  &sc->gpio_pins[pin], 1);
	}
	tegra_gpio_pin_configure(sc, &sc->gpio_pins[pin], flags);
	GPIO_UNLOCK(sc);

	return (0);
}