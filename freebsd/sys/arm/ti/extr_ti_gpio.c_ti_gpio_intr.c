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
typedef  size_t u_int ;
struct trapframe {int dummy; } ;
struct ti_gpio_softc {size_t sc_maxpin; int /*<<< orphan*/  sc_dev; struct ti_gpio_irqsrc* sc_isrcs; } ;
struct ti_gpio_irqsrc {int tgi_mask; int /*<<< orphan*/  tgi_isrc; } ;
struct TYPE_2__ {struct trapframe* td_intr_frame; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ intr_isrc_dispatch (int /*<<< orphan*/ *,struct trapframe*) ; 
 int ti_gpio_intr_status (struct ti_gpio_softc*) ; 
 int /*<<< orphan*/  ti_gpio_isrc_eoi (struct ti_gpio_softc*,struct ti_gpio_irqsrc*) ; 
 scalar_t__ ti_gpio_isrc_is_level (struct ti_gpio_irqsrc*) ; 
 int /*<<< orphan*/  ti_gpio_isrc_mask (struct ti_gpio_softc*,struct ti_gpio_irqsrc*) ; 

__attribute__((used)) static int
ti_gpio_intr(void *arg)
{
	u_int irq;
	uint32_t reg;
	struct ti_gpio_softc *sc;
	struct trapframe *tf;
	struct ti_gpio_irqsrc *tgi;

	sc = (struct ti_gpio_softc *)arg;
	tf = curthread->td_intr_frame;

	reg = ti_gpio_intr_status(sc);
	for (irq = 0; irq < sc->sc_maxpin; irq++) {
		tgi = &sc->sc_isrcs[irq];
		if ((reg & tgi->tgi_mask) == 0)
			continue;
		if (!ti_gpio_isrc_is_level(tgi))
			ti_gpio_isrc_eoi(sc, tgi);
		if (intr_isrc_dispatch(&tgi->tgi_isrc, tf) != 0) {
			ti_gpio_isrc_mask(sc, tgi);
			if (ti_gpio_isrc_is_level(tgi))
				ti_gpio_isrc_eoi(sc, tgi);
			device_printf(sc->sc_dev, "Stray irq %u disabled\n",
			    irq);
		}
	}
	return (FILTER_HANDLED);
}