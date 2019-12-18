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
struct aw_gpio_softc {TYPE_1__* padconf; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ npins; } ;

/* Variables and functions */
#define  AW_GPIO_INPUT 131 
 int /*<<< orphan*/  AW_GPIO_LOCK (struct aw_gpio_softc*) ; 
#define  AW_GPIO_OUTPUT 130 
#define  AW_GPIO_PULLDOWN 129 
#define  AW_GPIO_PULLUP 128 
 int /*<<< orphan*/  AW_GPIO_UNLOCK (struct aw_gpio_softc*) ; 
 int EINVAL ; 
 scalar_t__ GPIO_PIN_INPUT ; 
 scalar_t__ GPIO_PIN_OUTPUT ; 
 scalar_t__ GPIO_PIN_PULLDOWN ; 
 scalar_t__ GPIO_PIN_PULLUP ; 
 scalar_t__ aw_gpio_get_function (struct aw_gpio_softc*,scalar_t__) ; 
 scalar_t__ aw_gpio_get_pud (struct aw_gpio_softc*,scalar_t__) ; 
 struct aw_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_gpio_pin_getflags(device_t dev, uint32_t pin, uint32_t *flags)
{
	struct aw_gpio_softc *sc;
	uint32_t func;
	uint32_t pud;

	sc = device_get_softc(dev);
	if (pin >= sc->padconf->npins)
		return (EINVAL);

	AW_GPIO_LOCK(sc);
	func = aw_gpio_get_function(sc, pin);
	switch (func) {
	case AW_GPIO_INPUT:
		*flags = GPIO_PIN_INPUT;
		break;
	case AW_GPIO_OUTPUT:
		*flags = GPIO_PIN_OUTPUT;
		break;
	default:
		*flags = 0;
		break;
	}

	pud = aw_gpio_get_pud(sc, pin);
	switch (pud) {
	case AW_GPIO_PULLDOWN:
		*flags |= GPIO_PIN_PULLDOWN;
		break;
	case AW_GPIO_PULLUP:
		*flags |= GPIO_PIN_PULLUP;
		break;
	default:
		break;
	}

	AW_GPIO_UNLOCK(sc);

	return (0);
}