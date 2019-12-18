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
typedef  int u_int ;
struct trapframe {int dummy; } ;
struct tegra_gpio_softc {int /*<<< orphan*/  dev; struct tegra_gpio_irqsrc* isrcs; int /*<<< orphan*/  mem_res; } ;
struct tegra_gpio_irqsrc {int /*<<< orphan*/  isrc; } ;
struct tegra_gpio_irq_cookie {int bank_num; struct tegra_gpio_softc* sc; } ;
struct TYPE_2__ {struct trapframe* td_intr_frame; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 scalar_t__ GPIO_INT_ENB ; 
 scalar_t__ GPIO_INT_STA ; 
 int GPIO_PINS_IN_REG ; 
 scalar_t__ GPIO_REGNUM (int) ; 
 int GPIO_REGS_IN_BANK ; 
 int bus_read_4 (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ intr_isrc_dispatch (int /*<<< orphan*/ *,struct trapframe*) ; 
 int /*<<< orphan*/  tegra_gpio_isrc_eoi (struct tegra_gpio_softc*,struct tegra_gpio_irqsrc*) ; 
 scalar_t__ tegra_gpio_isrc_is_level (struct tegra_gpio_irqsrc*) ; 
 int /*<<< orphan*/  tegra_gpio_isrc_mask (struct tegra_gpio_softc*,struct tegra_gpio_irqsrc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tegra_gpio_intr(void *arg)
{
	u_int irq, i, j, val, basepin;
	struct tegra_gpio_softc *sc;
	struct trapframe *tf;
	struct tegra_gpio_irqsrc *tgi;
	struct tegra_gpio_irq_cookie *cookie;

	cookie = (struct tegra_gpio_irq_cookie *)arg;
	sc = cookie->sc;
	tf = curthread->td_intr_frame;

	for (i = 0; i < GPIO_REGS_IN_BANK; i++) {
		basepin  = cookie->bank_num * GPIO_REGS_IN_BANK *
		    GPIO_PINS_IN_REG + i * GPIO_PINS_IN_REG;

		val = bus_read_4(sc->mem_res, GPIO_INT_STA +
		    GPIO_REGNUM(basepin));
		val &= bus_read_4(sc->mem_res, GPIO_INT_ENB +
		    GPIO_REGNUM(basepin));
		/* Interrupt handling */
		for (j = 0; j < GPIO_PINS_IN_REG; j++) {
			if ((val & (1 << j)) == 0)
				continue;
			irq = basepin + j;
			tgi = &sc->isrcs[irq];
			if (!tegra_gpio_isrc_is_level(tgi))
				tegra_gpio_isrc_eoi(sc, tgi);
			if (intr_isrc_dispatch(&tgi->isrc, tf) != 0) {
				tegra_gpio_isrc_mask(sc, tgi, 0);
				if (tegra_gpio_isrc_is_level(tgi))
					tegra_gpio_isrc_eoi(sc, tgi);
				device_printf(sc->dev,
				    "Stray irq %u disabled\n", irq);
			}

		}
	}

	return (FILTER_HANDLED);
}