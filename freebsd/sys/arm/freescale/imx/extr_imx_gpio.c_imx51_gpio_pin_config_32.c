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
typedef  scalar_t__ u_int ;
struct imx51_gpio_softc {scalar_t__ gpio_npins; int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GPIO_PIN_INPUT ; 
 scalar_t__ GPIO_PIN_OUTPUT ; 
 scalar_t__ GPIO_PIN_PRESET_HIGH ; 
 scalar_t__ GPIO_PIN_PRESET_LOW ; 
 int /*<<< orphan*/  IMX_GPIO_DR_REG ; 
 int /*<<< orphan*/  IMX_GPIO_OE_REG ; 
 scalar_t__ READ4 (struct imx51_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct imx51_gpio_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct imx51_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
imx51_gpio_pin_config_32(device_t dev, uint32_t first_pin, uint32_t num_pins,
    uint32_t *pin_flags)
{
	struct imx51_gpio_softc *sc;
	u_int i;
	uint32_t bit, drclr, drset, flags, oeclr, oeset, pads;

	sc = device_get_softc(dev);

	if (first_pin != 0 || num_pins > sc->gpio_npins)
		return (EINVAL);

	drclr = drset = oeclr = oeset = 0;
	pads = READ4(sc, IMX_GPIO_DR_REG);

	for (i = 0; i < num_pins; ++i) {
		bit = 1u << i;
		flags = pin_flags[i];
		if (flags & GPIO_PIN_INPUT) {
			oeclr |= bit;
		} else if (flags & GPIO_PIN_OUTPUT) {
			oeset |= bit;
			if (flags & GPIO_PIN_PRESET_LOW)
				drclr |= bit;
			else if (flags & GPIO_PIN_PRESET_HIGH)
				drset |= bit;
			else /* Drive whatever it's now pulled to. */
				drset |= pads & bit;
		}
	}

	mtx_lock_spin(&sc->sc_mtx);
	WRITE4(sc, IMX_GPIO_DR_REG,
	    (READ4(sc, IMX_GPIO_DR_REG) & ~drclr) | drset);
	WRITE4(sc, IMX_GPIO_OE_REG,
	    (READ4(sc, IMX_GPIO_OE_REG) & ~oeclr) | oeset);
	mtx_unlock_spin(&sc->sc_mtx);

	return (0);
}