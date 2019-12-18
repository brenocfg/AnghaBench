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
struct TYPE_2__ {int pin_flags; int pin_func; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct jz4780_gpio_softc*,int /*<<< orphan*/ ,unsigned int) ; 
 int EINVAL ; 
 int GPIO_PIN_INPUT ; 
 int GPIO_PIN_OUTPUT ; 
 scalar_t__ JZ_FUNC_DEV_3 ; 
 int /*<<< orphan*/  JZ_GPIO_INTC ; 
 int /*<<< orphan*/  JZ_GPIO_MASKC ; 
 int /*<<< orphan*/  JZ_GPIO_PAT0C ; 
 int /*<<< orphan*/  JZ_GPIO_PAT0S ; 
 int /*<<< orphan*/  JZ_GPIO_PAT1C ; 
 int /*<<< orphan*/  JZ_GPIO_PAT1S ; 

__attribute__((used)) static int
jz4780_gpio_pin_set_func(struct jz4780_gpio_softc *sc, uint32_t pin,
    uint32_t func)
{
	uint32_t mask = (1u << pin);

	if (func > (uint32_t)JZ_FUNC_DEV_3)
		return (EINVAL);

	CSR_WRITE_4(sc, JZ_GPIO_INTC, mask);
	CSR_WRITE_4(sc, JZ_GPIO_MASKC, mask);
	if (func & 2)
		CSR_WRITE_4(sc, JZ_GPIO_PAT1S, mask);
	else
		CSR_WRITE_4(sc, JZ_GPIO_PAT1C, mask);
	if (func & 1)
		CSR_WRITE_4(sc, JZ_GPIO_PAT0S, mask);
	else
		CSR_WRITE_4(sc, JZ_GPIO_PAT0C, mask);

	sc->pins[pin].pin_flags &= ~(GPIO_PIN_INPUT | GPIO_PIN_OUTPUT);
	sc->pins[pin].pin_func = (enum pin_function)func;
	return (0);
}