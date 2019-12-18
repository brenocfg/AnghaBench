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
struct rk30_gpio_softc {scalar_t__ sc_bank; } ;

/* Variables and functions */
#define  GPIO_PIN_PULLDOWN 129 
#define  GPIO_PIN_PULLUP 128 
 int /*<<< orphan*/  RK30_GPIO_LOCK_ASSERT (struct rk30_gpio_softc*) ; 
 int RK30_GPIO_NONE ; 
 int RK30_GPIO_PULLDOWN ; 
 int RK30_GPIO_PULLUP ; 
 int /*<<< orphan*/  rk30_grf_gpio_pud (scalar_t__,int,int) ; 
 int /*<<< orphan*/  rk30_pmu_gpio_pud (int,int) ; 

__attribute__((used)) static void
rk30_gpio_set_pud(struct rk30_gpio_softc *sc, uint32_t pin, uint32_t state)
{
	uint32_t pud;

	/* Must be called with lock held. */
	RK30_GPIO_LOCK_ASSERT(sc);
	switch (state) {
	case GPIO_PIN_PULLUP:
		pud = RK30_GPIO_PULLUP;
		break;
	case GPIO_PIN_PULLDOWN:
		pud = RK30_GPIO_PULLDOWN;
		break;
	default:
		pud = RK30_GPIO_NONE;
	}
	/*
	 * The pull up/down registers for GPIO0A and half of GPIO0B
	 * (the first 12 pins on bank 0) are at a different location.
	 */
	if (sc->sc_bank == 0 && pin < 12)
		rk30_pmu_gpio_pud(pin, pud);
	else
		rk30_grf_gpio_pud(sc->sc_bank, pin, pud);
}