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
struct vf_gpio_softc {int dummy; } ;
struct gpio_pin {unsigned int gp_flags; int gp_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_LOCK (struct vf_gpio_softc*) ; 
 int /*<<< orphan*/  GPIO_PCOR (int) ; 
 unsigned int GPIO_PIN_INPUT ; 
 unsigned int GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  GPIO_UNLOCK (struct vf_gpio_softc*) ; 
 int /*<<< orphan*/  WRITE4 (struct vf_gpio_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vf_gpio_pin_configure(struct vf_gpio_softc *sc, struct gpio_pin *pin,
    unsigned int flags)
{

	GPIO_LOCK(sc);

	/*
	 * Manage input/output
	 */
	if (flags & (GPIO_PIN_INPUT|GPIO_PIN_OUTPUT)) {
		pin->gp_flags &= ~(GPIO_PIN_INPUT|GPIO_PIN_OUTPUT);
		if (flags & GPIO_PIN_OUTPUT) {
			pin->gp_flags |= GPIO_PIN_OUTPUT;

		} else {
			pin->gp_flags |= GPIO_PIN_INPUT;
			WRITE4(sc, GPIO_PCOR(pin->gp_pin),
			    (1 << (pin->gp_pin % 32)));
		}
	}

	GPIO_UNLOCK(sc);
}