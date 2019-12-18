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
struct mtk_gpio_softc {TYPE_1__* pins; } ;
struct TYPE_2__ {int pin_flags; int /*<<< orphan*/  intr_polarity; int /*<<< orphan*/  intr_trigger; } ;

/* Variables and functions */
 int GPIO_PIN_INPUT ; 
 int GPIO_PIN_INVIN ; 
 int GPIO_PIN_INVOUT ; 
 int GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  GPIO_PIODIR ; 
 int /*<<< orphan*/  GPIO_PIOFENA ; 
 int /*<<< orphan*/  GPIO_PIOPOL ; 
 int /*<<< orphan*/  GPIO_PIORENA ; 
 int /*<<< orphan*/  INTR_POLARITY_HIGH ; 
 int /*<<< orphan*/  INTR_POLARITY_LOW ; 
 int /*<<< orphan*/  INTR_TRIGGER_EDGE ; 
 unsigned int MTK_READ_4 (struct mtk_gpio_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mtk_gpio_pin_probe(struct mtk_gpio_softc *sc, uint32_t pin)
{
	uint32_t mask = (1u << pin);
	uint32_t val;

	/* Clear cached gpio config */
	sc->pins[pin].pin_flags = 0;

	val = MTK_READ_4(sc, GPIO_PIORENA) |
	    MTK_READ_4(sc, GPIO_PIOFENA);
	if (val & mask) {
		/* Pin is in interrupt mode */
		sc->pins[pin].intr_trigger = INTR_TRIGGER_EDGE;
		val = MTK_READ_4(sc, GPIO_PIORENA);
		if (val & mask)
			sc->pins[pin].intr_polarity = INTR_POLARITY_HIGH;
		else
			sc->pins[pin].intr_polarity = INTR_POLARITY_LOW;
	}

	val = MTK_READ_4(sc, GPIO_PIODIR);
	if (val & mask)
		sc->pins[pin].pin_flags |= GPIO_PIN_OUTPUT;
	else
		sc->pins[pin].pin_flags |= GPIO_PIN_INPUT;

	val = MTK_READ_4(sc, GPIO_PIOPOL);
	if (val & mask) {
		if (sc->pins[pin].pin_flags & GPIO_PIN_INPUT) {
			sc->pins[pin].pin_flags |= GPIO_PIN_INVIN;
		} else {
			sc->pins[pin].pin_flags |= GPIO_PIN_INVOUT;
		}
	}
}