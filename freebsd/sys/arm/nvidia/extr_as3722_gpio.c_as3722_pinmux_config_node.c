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
typedef  int uint8_t ;
struct as3722_softc {int gpio_npins; TYPE_1__** gpio_pins; int /*<<< orphan*/  dev; } ;
struct as3722_pincfg {int /*<<< orphan*/ * function; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int pin_ctrl_reg; int /*<<< orphan*/  pin_name; int /*<<< orphan*/  pin_cfg_flags; } ;

/* Variables and functions */
 scalar_t__ AS3722_GPIO0_CONTROL ; 
 int AS3722_GPIO_IOSF_MASK ; 
 int AS3722_GPIO_IOSF_SHIFT ; 
 int AS3722_GPIO_MODE_MASK ; 
 int AS3722_GPIO_MODE_SHIFT ; 
#define  AS3722_IOSF_CLK32K_OUT 139 
#define  AS3722_IOSF_GPIO_IN_INTERRUPT 138 
#define  AS3722_IOSF_INTERRUPT_OUT 137 
#define  AS3722_IOSF_OC_PG_SD0 136 
#define  AS3722_IOSF_OC_PG_SD6 135 
#define  AS3722_IOSF_POWERGOOD_OUT 134 
#define  AS3722_IOSF_PWM_IN 133 
#define  AS3722_IOSF_PWM_OUT 132 
#define  AS3722_IOSF_SOFT_RESET_IN 131 
#define  AS3722_IOSF_VOLTAGE_IN_STANDBY 130 
#define  AS3722_IOSF_VSUP_VBAT_LOW_UNDEBOUNCE_OUT 129 
#define  AS3722_IOSF_WATCHDOG_IN 128 
 int AS3722_MODE_INPUT ; 
 int AS3722_MODE_PUSH_PULL ; 
 int ENXIO ; 
 int WR1 (struct as3722_softc*,scalar_t__,int) ; 
 int as3722_pinmux_get_function (struct as3722_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
as3722_pinmux_config_node(struct as3722_softc *sc, char *pin_name,
    struct as3722_pincfg *cfg)
{
	uint8_t ctrl;
	int rv, fnc, pin;

	for (pin = 0; pin < sc->gpio_npins; pin++) {
		if (strcmp(sc->gpio_pins[pin]->pin_name, pin_name) == 0)
			 break;
	}
	if (pin >= sc->gpio_npins) {
		device_printf(sc->dev, "Unknown pin: %s\n", pin_name);
		return (ENXIO);
	}

	ctrl = sc->gpio_pins[pin]->pin_ctrl_reg;
	sc->gpio_pins[pin]->pin_cfg_flags = cfg->flags;
	if (cfg->function != NULL) {
		fnc = as3722_pinmux_get_function(sc, cfg->function);
		if (fnc == -1) {
			device_printf(sc->dev,
			    "Unknown function %s for pin %s\n", cfg->function,
			    sc->gpio_pins[pin]->pin_name);
			return (ENXIO);
		}
		switch (fnc) {
		case AS3722_IOSF_INTERRUPT_OUT:
		case AS3722_IOSF_VSUP_VBAT_LOW_UNDEBOUNCE_OUT:
		case AS3722_IOSF_OC_PG_SD0:
		case AS3722_IOSF_POWERGOOD_OUT:
		case AS3722_IOSF_CLK32K_OUT:
		case AS3722_IOSF_PWM_OUT:
		case AS3722_IOSF_OC_PG_SD6:
			ctrl &= ~(AS3722_GPIO_MODE_MASK <<
			    AS3722_GPIO_MODE_SHIFT);
			ctrl |= AS3722_MODE_PUSH_PULL << AS3722_GPIO_MODE_SHIFT;
			/* XXX Handle flags (OC + pullup) */
			break;
		case AS3722_IOSF_GPIO_IN_INTERRUPT:
		case AS3722_IOSF_PWM_IN:
		case AS3722_IOSF_VOLTAGE_IN_STANDBY:
		case AS3722_IOSF_WATCHDOG_IN:
		case AS3722_IOSF_SOFT_RESET_IN:
			ctrl &= ~(AS3722_GPIO_MODE_MASK <<
			    AS3722_GPIO_MODE_SHIFT);
			ctrl |= AS3722_MODE_INPUT << AS3722_GPIO_MODE_SHIFT;
			/* XXX Handle flags (pulldown + pullup) */

		default:
			break;
		}
		ctrl &= ~(AS3722_GPIO_IOSF_MASK << AS3722_GPIO_IOSF_SHIFT);
		ctrl |= fnc << AS3722_GPIO_IOSF_SHIFT;
	}
	rv = 0;
	if (ctrl != sc->gpio_pins[pin]->pin_ctrl_reg) {
		rv = WR1(sc, AS3722_GPIO0_CONTROL + pin, ctrl);
		sc->gpio_pins[pin]->pin_ctrl_reg = ctrl;
	}
	return (rv);
}