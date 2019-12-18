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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct as3722_softc {int gpio_npins; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AS3722_GPIO_SIGNAL_OUT ; 
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_LOCK (struct as3722_softc*) ; 
 int /*<<< orphan*/  GPIO_UNLOCK (struct as3722_softc*) ; 
 int RD1 (struct as3722_softc*,int /*<<< orphan*/ ,int*) ; 
 int RM1 (struct as3722_softc*,int /*<<< orphan*/ ,int,int) ; 
 struct as3722_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
as3722_gpio_pin_toggle(device_t dev, uint32_t pin)
{
	struct as3722_softc *sc;
	uint8_t tmp;
	int rv;

	sc = device_get_softc(dev);
	if (pin >= sc->gpio_npins)
		return (EINVAL);

	GPIO_LOCK(sc);
	rv = RD1(sc, AS3722_GPIO_SIGNAL_OUT, &tmp);
	if (rv != 0) {
		GPIO_UNLOCK(sc);
		return (rv);
	}
	tmp ^= (1 <<pin);
	rv = RM1(sc, AS3722_GPIO_SIGNAL_OUT, (1 << pin), tmp);
	GPIO_UNLOCK(sc);
	return (0);
}