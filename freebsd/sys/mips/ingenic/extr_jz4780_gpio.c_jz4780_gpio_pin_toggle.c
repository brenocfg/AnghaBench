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
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ pin_func; int pin_flags; } ;

/* Variables and functions */
 unsigned int CSR_READ_4 (struct jz4780_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct jz4780_gpio_softc*,int /*<<< orphan*/ ,unsigned int) ; 
 int EINVAL ; 
 int GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  JZ4780_GPIO_LOCK (struct jz4780_gpio_softc*) ; 
 unsigned int JZ4780_GPIO_PINS ; 
 int /*<<< orphan*/  JZ4780_GPIO_UNLOCK (struct jz4780_gpio_softc*) ; 
 scalar_t__ JZ_FUNC_GPIO ; 
 int /*<<< orphan*/  JZ_GPIO_PAT0C ; 
 int /*<<< orphan*/  JZ_GPIO_PAT0S ; 
 int /*<<< orphan*/  JZ_GPIO_PIN ; 
 struct jz4780_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jz4780_gpio_pin_toggle(device_t dev, uint32_t pin)
{
	struct jz4780_gpio_softc *sc;
	uint32_t data, mask;
	int retval;

	if (pin >= JZ4780_GPIO_PINS)
		return (EINVAL);

	retval = EINVAL;
	mask = (1u << pin);
	sc = device_get_softc(dev);
	JZ4780_GPIO_LOCK(sc);
	if (sc->pins[pin].pin_func == JZ_FUNC_GPIO &&
	    sc->pins[pin].pin_flags & GPIO_PIN_OUTPUT) {
		data = CSR_READ_4(sc, JZ_GPIO_PIN);
		CSR_WRITE_4(sc, (data & mask) ? JZ_GPIO_PAT0C : JZ_GPIO_PAT0S,
		    mask);
		retval = 0;
	}
	JZ4780_GPIO_UNLOCK(sc);

	return (retval);
}