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
struct tegra_gpio_irqsrc {int /*<<< orphan*/  irq; } ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int GPIO_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_LOCK (struct tegra_gpio_softc*) ; 
 scalar_t__ GPIO_REGNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_UNLOCK (struct tegra_gpio_softc*) ; 
 int bus_read_4 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static inline void
intr_write_modify(struct tegra_gpio_softc *sc, bus_addr_t reg,
    struct tegra_gpio_irqsrc *tgi, uint32_t val, uint32_t mask)
{
	uint32_t tmp;
	int bit;

	bit = GPIO_BIT(tgi->irq);
	GPIO_LOCK(sc);
	tmp = bus_read_4(sc->mem_res, reg + GPIO_REGNUM(tgi->irq));
	tmp &= ~(mask << bit);
	tmp |= val << bit;
	bus_write_4(sc->mem_res, reg + GPIO_REGNUM(tgi->irq), tmp);
	GPIO_UNLOCK(sc);
}