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
typedef  int uint32_t ;
struct chipc_gpio_update {int dummy; } ;
struct chipc_gpio_softc {int /*<<< orphan*/  dev; } ;
typedef  int chipc_gpio_pin_mode ;

/* Variables and functions */
#define  CC_GPIO_PIN_INPUT 130 
#define  CC_GPIO_PIN_OUTPUT 129 
#define  CC_GPIO_PIN_TRISTATE 128 
 int /*<<< orphan*/  CC_GPIO_UPDATE (struct chipc_gpio_update*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CC_GPIO_VALID_PIN (int) ; 
 int EINVAL ; 
 int GPIO_PIN_OUTPUT ; 
 int GPIO_PIN_PRESET_HIGH ; 
 int GPIO_PIN_PRESET_LOW ; 
 int GPIO_PIN_PULLDOWN ; 
 int GPIO_PIN_PULLUP ; 
 int GPIO_PIN_PULSATE ; 
 int chipc_gpio_check_flags (struct chipc_gpio_softc*,int,int,int*) ; 
 int /*<<< orphan*/  ctrl ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  out ; 
 int /*<<< orphan*/  outen ; 
 int /*<<< orphan*/  pulldown ; 
 int /*<<< orphan*/  pullup ; 
 int /*<<< orphan*/  timeroutmask ; 

__attribute__((used)) static int
chipc_gpio_pin_update(struct chipc_gpio_softc *sc,
    struct chipc_gpio_update *update, uint32_t pin_num, uint32_t flags)
{
	chipc_gpio_pin_mode	mode;
	int			error;

	if (!CC_GPIO_VALID_PIN(pin_num))
		return (EINVAL);

	/* Verify flag compatibility and determine the pin mode */
	if ((error = chipc_gpio_check_flags(sc, pin_num, flags, &mode)))
		return (error);

	/* Apply the mode-specific changes */
	switch (mode) {
	case CC_GPIO_PIN_INPUT:
		CC_GPIO_UPDATE(update, pin_num, pullup, false);
		CC_GPIO_UPDATE(update, pin_num, pulldown, false);
		CC_GPIO_UPDATE(update, pin_num, out, false);
		CC_GPIO_UPDATE(update, pin_num, outen, false);
		CC_GPIO_UPDATE(update, pin_num, timeroutmask, false);
		CC_GPIO_UPDATE(update, pin_num, ctrl, false);

		if (flags & GPIO_PIN_PULLUP) {
			CC_GPIO_UPDATE(update, pin_num, pullup, true);
		} else if (flags & GPIO_PIN_PULLDOWN) {
			CC_GPIO_UPDATE(update, pin_num, pulldown, true);
		}

		return (0);

	case CC_GPIO_PIN_OUTPUT:
		CC_GPIO_UPDATE(update, pin_num, pullup, false);
		CC_GPIO_UPDATE(update, pin_num, pulldown, false);
		CC_GPIO_UPDATE(update, pin_num, outen, true);
		CC_GPIO_UPDATE(update, pin_num, timeroutmask, false);
		CC_GPIO_UPDATE(update, pin_num, ctrl, false);

		if (flags & GPIO_PIN_PRESET_HIGH) {
			CC_GPIO_UPDATE(update, pin_num, out, true);
		} else if (flags & GPIO_PIN_PRESET_LOW) {
			CC_GPIO_UPDATE(update, pin_num, out, false);
		}

		if (flags & GPIO_PIN_PULSATE)
			CC_GPIO_UPDATE(update, pin_num, timeroutmask, true);

		return (0);

	case CC_GPIO_PIN_TRISTATE:
		CC_GPIO_UPDATE(update, pin_num, pullup, false);
		CC_GPIO_UPDATE(update, pin_num, pulldown, false);
		CC_GPIO_UPDATE(update, pin_num, out, false);
		CC_GPIO_UPDATE(update, pin_num, outen, false);
		CC_GPIO_UPDATE(update, pin_num, timeroutmask, false);
		CC_GPIO_UPDATE(update, pin_num, ctrl, true);

		if (flags & GPIO_PIN_OUTPUT)
			CC_GPIO_UPDATE(update, pin_num, outen, true);

		return (0);
	}

	device_printf(sc->dev, "unknown pin mode %d\n", mode);
	return (EINVAL);
}