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
struct tegra_gpio_softc {int /*<<< orphan*/  mem_res; } ;
struct gpio_pin {int /*<<< orphan*/  gp_pin; } ;
typedef  scalar_t__ bus_size_t ;

/* Variables and functions */
 int GPIO_BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ GPIO_REGNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static inline void
gpio_write_masked(struct tegra_gpio_softc *sc, bus_size_t reg,
    struct gpio_pin *pin, uint32_t val)
{
	uint32_t tmp;
	int bit;

	bit = GPIO_BIT(pin->gp_pin);
	tmp = 0x100 << bit;		/* mask */
	tmp |= (val & 1) << bit;	/* value */
	bus_write_4(sc->mem_res, reg + GPIO_REGNUM(pin->gp_pin), tmp);
}