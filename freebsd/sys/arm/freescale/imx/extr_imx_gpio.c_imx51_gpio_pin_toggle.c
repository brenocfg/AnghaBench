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
struct imx51_gpio_softc {scalar_t__ gpio_npins; int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IMX_GPIO_DR_REG ; 
 unsigned int READ4 (struct imx51_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct imx51_gpio_softc*,int /*<<< orphan*/ ,unsigned int) ; 
 struct imx51_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
imx51_gpio_pin_toggle(device_t dev, uint32_t pin)
{
	struct imx51_gpio_softc *sc;

	sc = device_get_softc(dev);

	if (pin >= sc->gpio_npins)
		return (EINVAL);

	mtx_lock_spin(&sc->sc_mtx);
	WRITE4(sc, IMX_GPIO_DR_REG,
	    (READ4(sc, IMX_GPIO_DR_REG) ^ (1U << pin)));
	mtx_unlock_spin(&sc->sc_mtx);

	return (0);
}