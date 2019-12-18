#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct aw_gpio_softc {TYPE_2__* padconf; } ;
struct TYPE_4__ {size_t npins; TYPE_1__* pins; } ;
struct TYPE_3__ {size_t port; size_t pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  AW_GPIO_GP_CFG (size_t,size_t) ; 
 int /*<<< orphan*/  AW_GPIO_LOCK_ASSERT (struct aw_gpio_softc*) ; 
 size_t AW_GPIO_READ (struct aw_gpio_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
aw_gpio_get_function(struct aw_gpio_softc *sc, uint32_t pin)
{
	uint32_t bank, func, offset;

	/* Must be called with lock held. */
	AW_GPIO_LOCK_ASSERT(sc);

	if (pin > sc->padconf->npins)
		return (0);
	bank = sc->padconf->pins[pin].port;
	pin = sc->padconf->pins[pin].pin;
	offset = ((pin & 0x07) << 2);

	func = AW_GPIO_READ(sc, AW_GPIO_GP_CFG(bank, pin >> 3));

	return ((func >> offset) & 0x7);
}