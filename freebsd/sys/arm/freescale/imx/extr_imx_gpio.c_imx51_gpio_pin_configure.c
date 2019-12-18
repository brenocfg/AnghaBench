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
typedef  int u_int ;
struct imx51_gpio_softc {int /*<<< orphan*/  sc_mtx; } ;
struct gpio_pin {unsigned int gp_flags; int gp_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR4 (struct imx51_gpio_softc*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int GPIO_PIN_INPUT ; 
 unsigned int GPIO_PIN_OPENDRAIN ; 
 unsigned int GPIO_PIN_OUTPUT ; 
 unsigned int GPIO_PIN_PRESET_HIGH ; 
 unsigned int GPIO_PIN_PRESET_LOW ; 
 int /*<<< orphan*/  IMX_GPIO_DR_REG ; 
 int /*<<< orphan*/  IMX_GPIO_OE_REG ; 
 int /*<<< orphan*/  IMX_GPIO_PSR_REG ; 
 int READ4 (struct imx51_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET4 (struct imx51_gpio_softc*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
imx51_gpio_pin_configure(struct imx51_gpio_softc *sc, struct gpio_pin *pin,
    unsigned int flags)
{
	u_int newflags, pad;

	mtx_lock_spin(&sc->sc_mtx);

	/*
	 * Manage input/output; other flags not supported yet (maybe not ever,
	 * since we have no connection to the pad config registers from here).
	 *
	 * When setting a pin to output, honor the PRESET_[LOW,HIGH] flags if
	 * present.  Otherwise, for glitchless transistions on pins with pulls,
	 * read the current state of the pad and preset the DR register to drive
	 * the current value onto the pin before enabling the pin for output.
	 *
	 * Note that changes to pin->gp_flags must be acccumulated in newflags
	 * and stored with a single writeback to gp_flags at the end, to enable
	 * unlocked reads of that value elsewhere. This is only about unlocked
	 * access to gp_flags from elsewhere; we still use locking in this
	 * function to protect r-m-w access to the hardware registers.
	 */
	if (flags & (GPIO_PIN_INPUT | GPIO_PIN_OUTPUT)) {
		newflags = pin->gp_flags & ~(GPIO_PIN_INPUT | GPIO_PIN_OUTPUT);
		if (flags & GPIO_PIN_OUTPUT) {
			if (flags & GPIO_PIN_PRESET_LOW) {
				pad = 0;
			} else if (flags & GPIO_PIN_PRESET_HIGH) {
				pad = 1;
			} else {
				if (flags & GPIO_PIN_OPENDRAIN)
					pad = READ4(sc, IMX_GPIO_PSR_REG);
				else
					pad = READ4(sc, IMX_GPIO_DR_REG);
				pad = (pad >> pin->gp_pin) & 1;
			}
			newflags |= GPIO_PIN_OUTPUT;
			SET4(sc, IMX_GPIO_DR_REG, (pad << pin->gp_pin));
			SET4(sc, IMX_GPIO_OE_REG, (1U << pin->gp_pin));
		} else {
			newflags |= GPIO_PIN_INPUT;
			CLEAR4(sc, IMX_GPIO_OE_REG, (1U << pin->gp_pin));
		}
		pin->gp_flags = newflags;
	}

	mtx_unlock_spin(&sc->sc_mtx);
}