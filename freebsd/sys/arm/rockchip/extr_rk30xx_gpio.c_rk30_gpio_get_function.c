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
typedef  unsigned int uint32_t ;
struct rk30_gpio_softc {int dummy; } ;

/* Variables and functions */
 unsigned int GPIO_PIN_INPUT ; 
 unsigned int GPIO_PIN_OUTPUT ; 
 unsigned int RK30_GPIO_READ (struct rk30_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RK30_GPIO_SWPORT_DDR ; 

__attribute__((used)) static uint32_t
rk30_gpio_get_function(struct rk30_gpio_softc *sc, uint32_t pin)
{

	if (RK30_GPIO_READ(sc, RK30_GPIO_SWPORT_DDR) & (1U << pin))
		return (GPIO_PIN_OUTPUT);
	else
		return (GPIO_PIN_INPUT);
}