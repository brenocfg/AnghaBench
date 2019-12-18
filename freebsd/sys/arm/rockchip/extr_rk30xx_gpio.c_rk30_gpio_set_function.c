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
typedef  scalar_t__ uint32_t ;
struct rk30_gpio_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  RK30_GPIO_LOCK_ASSERT (struct rk30_gpio_softc*) ; 
 scalar_t__ RK30_GPIO_READ (struct rk30_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RK30_GPIO_SWPORT_DDR ; 
 int /*<<< orphan*/  RK30_GPIO_WRITE (struct rk30_gpio_softc*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
rk30_gpio_set_function(struct rk30_gpio_softc *sc, uint32_t pin, uint32_t func)
{
	uint32_t data;

	/* Must be called with lock held. */
	RK30_GPIO_LOCK_ASSERT(sc);
	data = RK30_GPIO_READ(sc, RK30_GPIO_SWPORT_DDR);
	if (func == GPIO_PIN_OUTPUT)
		data |= (1U << pin);
	else
		data &= ~(1U << pin);
	RK30_GPIO_WRITE(sc, RK30_GPIO_SWPORT_DDR, data);
}