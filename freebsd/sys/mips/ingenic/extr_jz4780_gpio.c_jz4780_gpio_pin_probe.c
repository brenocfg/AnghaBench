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
typedef  unsigned int uint32_t ;
struct jz4780_gpio_softc {TYPE_1__* pins; } ;
typedef  enum pin_function { ____Placeholder_pin_function } pin_function ;
struct TYPE_2__ {int pin_flags; int pin_func; int pin_caps; int /*<<< orphan*/  intr_polarity; int /*<<< orphan*/  intr_trigger; } ;

/* Variables and functions */
 unsigned int CSR_READ_4 (struct jz4780_gpio_softc*,int /*<<< orphan*/ ) ; 
 int GPIO_PIN_INPUT ; 
 int GPIO_PIN_OUTPUT ; 
 int GPIO_PIN_PULLDOWN ; 
 int GPIO_PIN_PULLUP ; 
 int /*<<< orphan*/  INTR_POLARITY_HIGH ; 
 int /*<<< orphan*/  INTR_POLARITY_LOW ; 
 int /*<<< orphan*/  INTR_TRIGGER_EDGE ; 
 int /*<<< orphan*/  INTR_TRIGGER_LEVEL ; 
 int JZ_FUNC_GPIO ; 
 int JZ_FUNC_INTR ; 
 int /*<<< orphan*/  JZ_GPIO_DPULL ; 
 int /*<<< orphan*/  JZ_GPIO_INT ; 
 int /*<<< orphan*/  JZ_GPIO_MASK ; 
 int /*<<< orphan*/  JZ_GPIO_PAT0 ; 
 int /*<<< orphan*/  JZ_GPIO_PAT1 ; 

__attribute__((used)) static void
jz4780_gpio_pin_probe(struct jz4780_gpio_softc *sc, uint32_t pin)
{
	uint32_t mask = (1u << pin);
	uint32_t val;

	/* Clear cached gpio config */
	sc->pins[pin].pin_flags = 0;

	/* First check if pin is in interrupt mode */
	val = CSR_READ_4(sc, JZ_GPIO_INT);
	if (val & mask) {
		/* Pin is in interrupt mode, decode interrupt triggering mode */
		val = CSR_READ_4(sc, JZ_GPIO_PAT1);
		if (val & mask)
			sc->pins[pin].intr_trigger = INTR_TRIGGER_EDGE;
		else
			sc->pins[pin].intr_trigger = INTR_TRIGGER_LEVEL;
		/* Decode interrupt polarity */
		val = CSR_READ_4(sc, JZ_GPIO_PAT0);
		if (val & mask)
			sc->pins[pin].intr_polarity = INTR_POLARITY_HIGH;
		else
			sc->pins[pin].intr_polarity = INTR_POLARITY_LOW;

		sc->pins[pin].pin_func = JZ_FUNC_INTR;
		sc->pins[pin].pin_flags = 0;
		return;
	}
	/* Next check if pin is in gpio mode */
	val = CSR_READ_4(sc, JZ_GPIO_MASK);
	if (val & mask) {
		/* Pin is in gpio mode, decode direction and bias */
		val = CSR_READ_4(sc, JZ_GPIO_PAT1);
		if (val & mask)
			sc->pins[pin].pin_flags |= GPIO_PIN_INPUT;
		else
			sc->pins[pin].pin_flags |= GPIO_PIN_OUTPUT;
		/* Check for bias */
		val = CSR_READ_4(sc, JZ_GPIO_DPULL);
		if ((val & mask) == 0)
			sc->pins[pin].pin_flags |= sc->pins[pin].pin_caps &
				(GPIO_PIN_PULLUP | GPIO_PIN_PULLDOWN);
		sc->pins[pin].pin_func = JZ_FUNC_GPIO;
		return;
	}
	/* By exclusion, pin is in alternate function mode */
	val = CSR_READ_4(sc, JZ_GPIO_DPULL);
	if ((val & mask) == 0)
		sc->pins[pin].pin_flags = sc->pins[pin].pin_caps &
			(GPIO_PIN_PULLUP | GPIO_PIN_PULLDOWN);
	val = ((CSR_READ_4(sc, JZ_GPIO_PAT1) & mask) >> pin) << 1;
	val = val | ((CSR_READ_4(sc, JZ_GPIO_PAT1) & mask) >> pin);
	sc->pins[pin].pin_func = (enum pin_function)val;
}