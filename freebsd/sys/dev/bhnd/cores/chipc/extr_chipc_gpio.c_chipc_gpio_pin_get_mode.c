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
typedef  int /*<<< orphan*/  uint32_t ;
struct chipc_gpio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  chipc_gpio_pin_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CC_GPIO_ASSERT_VALID_PIN (struct chipc_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CC_GPIO_LOCK_ASSERT (struct chipc_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CC_GPIO_PIN_INPUT ; 
 int /*<<< orphan*/  CC_GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  CC_GPIO_PIN_TRISTATE ; 
 scalar_t__ CC_GPIO_RDFLAG (struct chipc_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIOCTRL ; 
 int /*<<< orphan*/  GPIOOUTEN ; 
 int /*<<< orphan*/  MA_OWNED ; 

__attribute__((used)) static chipc_gpio_pin_mode
chipc_gpio_pin_get_mode(struct chipc_gpio_softc *sc, uint32_t pin_num)
{
	CC_GPIO_LOCK_ASSERT(sc, MA_OWNED);
	CC_GPIO_ASSERT_VALID_PIN(sc, pin_num);

	if (CC_GPIO_RDFLAG(sc, pin_num, GPIOCTRL)) {
		return (CC_GPIO_PIN_TRISTATE);
	} else if (CC_GPIO_RDFLAG(sc, pin_num, GPIOOUTEN)) {
		return (CC_GPIO_PIN_OUTPUT);
	} else {
		return (CC_GPIO_PIN_INPUT);
	}
}