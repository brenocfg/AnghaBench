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
struct rk30_gpio_softc {int dummy; } ;
struct gpio_pin {unsigned int gp_flags; int /*<<< orphan*/  gp_pin; } ;

/* Variables and functions */
 unsigned int GPIO_PIN_INPUT ; 
 unsigned int GPIO_PIN_OUTPUT ; 
 unsigned int GPIO_PIN_PULLDOWN ; 
 unsigned int GPIO_PIN_PULLUP ; 
 int /*<<< orphan*/  RK30_GPIO_LOCK (struct rk30_gpio_softc*) ; 
 int /*<<< orphan*/  RK30_GPIO_UNLOCK (struct rk30_gpio_softc*) ; 
 int /*<<< orphan*/  rk30_gpio_set_function (struct rk30_gpio_softc*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rk30_gpio_set_pud (struct rk30_gpio_softc*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
rk30_gpio_pin_configure(struct rk30_gpio_softc *sc, struct gpio_pin *pin,
    unsigned int flags)
{

	RK30_GPIO_LOCK(sc);
	/*
	 * Manage input/output.
	 */
	if (flags & (GPIO_PIN_INPUT | GPIO_PIN_OUTPUT)) {
		pin->gp_flags &= ~(GPIO_PIN_INPUT | GPIO_PIN_OUTPUT);
		if (flags & GPIO_PIN_OUTPUT)
			pin->gp_flags |= GPIO_PIN_OUTPUT;
		else
			pin->gp_flags |= GPIO_PIN_INPUT;
		rk30_gpio_set_function(sc, pin->gp_pin, pin->gp_flags);
	}
	/* Manage Pull-up/pull-down. */
	pin->gp_flags &= ~(GPIO_PIN_PULLUP | GPIO_PIN_PULLDOWN);
	if (flags & (GPIO_PIN_PULLUP | GPIO_PIN_PULLDOWN)) {
		if (flags & GPIO_PIN_PULLUP)
			pin->gp_flags |= GPIO_PIN_PULLUP;
		else
			pin->gp_flags |= GPIO_PIN_PULLDOWN;
	}
	rk30_gpio_set_pud(sc, pin->gp_pin, pin->gp_flags);
	RK30_GPIO_UNLOCK(sc);
}