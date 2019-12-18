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
struct gpio_pin {unsigned int gp_flags; int gp_pin; } ;
struct dwgpio_softc {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_LOCK (struct dwgpio_softc*) ; 
 unsigned int GPIO_PIN_INPUT ; 
 unsigned int GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  GPIO_SWPORT_DDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_UNLOCK (struct dwgpio_softc*) ; 
 int READ4 (struct dwgpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct dwgpio_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
dwgpio_pin_configure(struct dwgpio_softc *sc,
    struct gpio_pin *pin, unsigned int flags)
{
	int reg;

	GPIO_LOCK(sc);

	/*
	 * Manage input/output
	 */

	reg = READ4(sc, GPIO_SWPORT_DDR(sc->port));
	if (flags & (GPIO_PIN_INPUT|GPIO_PIN_OUTPUT)) {
		pin->gp_flags &= ~(GPIO_PIN_INPUT|GPIO_PIN_OUTPUT);
		if (flags & GPIO_PIN_OUTPUT) {
			pin->gp_flags |= GPIO_PIN_OUTPUT;
			reg |= (1 << pin->gp_pin);
		} else {
			pin->gp_flags |= GPIO_PIN_INPUT;
			reg &= ~(1 << pin->gp_pin);
		}
	}

	WRITE4(sc, GPIO_SWPORT_DDR(sc->port), reg);
	GPIO_UNLOCK(sc);
}