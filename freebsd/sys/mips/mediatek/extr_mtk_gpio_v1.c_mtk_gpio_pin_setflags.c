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
struct mtk_gpio_softc {scalar_t__ num_pins; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GPIO_PIN_INPUT ; 
 scalar_t__ GPIO_PIN_INVIN ; 
 scalar_t__ GPIO_PIN_INVOUT ; 
 scalar_t__ GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  MTK_GPIO_LOCK (struct mtk_gpio_softc*) ; 
 int /*<<< orphan*/  MTK_GPIO_UNLOCK (struct mtk_gpio_softc*) ; 
 struct mtk_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mtk_gpio_pin_set_direction (struct mtk_gpio_softc*,scalar_t__,scalar_t__) ; 
 int mtk_gpio_pin_set_invert (struct mtk_gpio_softc*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
mtk_gpio_pin_setflags(device_t dev, uint32_t pin, uint32_t flags)
{
	struct mtk_gpio_softc *sc;
	int retval;

	sc = device_get_softc(dev);

	if (pin >= sc->num_pins)
		return (EINVAL);

	MTK_GPIO_LOCK(sc);
	retval = mtk_gpio_pin_set_direction(sc, pin,
	    flags & (GPIO_PIN_INPUT | GPIO_PIN_OUTPUT));
	if (retval == 0)
		retval = mtk_gpio_pin_set_invert(sc, pin,
		    flags & (GPIO_PIN_INVIN | GPIO_PIN_INVOUT));
	MTK_GPIO_UNLOCK(sc);

	return (retval);
}