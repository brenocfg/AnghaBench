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
typedef  int uint32_t ;
struct mv_gpio_softc {TYPE_1__* gpio_setup; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int gp_flags; } ;

/* Variables and functions */
 int GPIO_PINS_PER_REG ; 
 int /*<<< orphan*/  MV_GPIO_ASSERT_LOCKED () ; 
 int MV_GPIO_IN_DEBOUNCE ; 
 int MV_GPIO_IN_IRQ_DOUBLE_EDGE ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_gpio_debounce_start (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv_gpio_intr_handler (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv_gpio_polarity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mv_gpio_exec_intr_handlers(device_t dev, uint32_t status, int high)
{
	int i, pin;
	struct mv_gpio_softc *sc;
	sc = (struct mv_gpio_softc *)device_get_softc(dev);

	MV_GPIO_ASSERT_LOCKED();

	i = 0;
	while (status != 0) {
		if (status & 1) {
			pin = (high ? (i + GPIO_PINS_PER_REG) : i);
			if (sc->gpio_setup[pin].gp_flags & MV_GPIO_IN_DEBOUNCE)
				mv_gpio_debounce_start(dev, pin);
			else if (sc->gpio_setup[pin].gp_flags & MV_GPIO_IN_IRQ_DOUBLE_EDGE) {
				mv_gpio_polarity(dev, pin, 0, 1);
				mv_gpio_intr_handler(dev, pin);
			} else
				mv_gpio_intr_handler(dev, pin);
		}
		status >>= 1;
		i++;
	}
}