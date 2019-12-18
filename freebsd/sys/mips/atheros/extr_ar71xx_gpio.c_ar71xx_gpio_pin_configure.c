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
struct gpio_pin {unsigned int gp_flags; int /*<<< orphan*/  gp_pin; } ;
struct ar71xx_gpio_softc {int dummy; } ;

/* Variables and functions */
 unsigned int GPIO_PIN_INPUT ; 
 unsigned int GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  ar71xx_gpio_oe_set_input (struct ar71xx_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar71xx_gpio_oe_set_output (struct ar71xx_gpio_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ar71xx_gpio_pin_configure(struct ar71xx_gpio_softc *sc, struct gpio_pin *pin,
    unsigned int flags)
{

	/*
	 * Manage input/output
	 */
	if (flags & (GPIO_PIN_INPUT|GPIO_PIN_OUTPUT)) {
		pin->gp_flags &= ~(GPIO_PIN_INPUT|GPIO_PIN_OUTPUT);
		if (flags & GPIO_PIN_OUTPUT) {
			pin->gp_flags |= GPIO_PIN_OUTPUT;
			ar71xx_gpio_oe_set_output(sc, pin->gp_pin);
		} else {
			pin->gp_flags |= GPIO_PIN_INPUT;
			ar71xx_gpio_oe_set_input(sc, pin->gp_pin);
		}
	}
}