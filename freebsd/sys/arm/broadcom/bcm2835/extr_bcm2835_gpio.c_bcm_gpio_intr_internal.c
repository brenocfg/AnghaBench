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
typedef  int u_int ;
struct bcm_gpio_softc {int /*<<< orphan*/  sc_dev; struct bcm_gpio_irqsrc* sc_isrcs; } ;
struct bcm_gpio_irqsrc {int bgi_mask; int /*<<< orphan*/  bgi_isrc; } ;
struct TYPE_2__ {int /*<<< orphan*/  td_intr_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_GPIO_GPEDS (int) ; 
 int BCM_GPIO_PINS_PER_BANK ; 
 int BCM_GPIO_READ (struct bcm_gpio_softc*,int /*<<< orphan*/ ) ; 
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  bcm_gpio_isrc_eoi (struct bcm_gpio_softc*,struct bcm_gpio_irqsrc*) ; 
 scalar_t__ bcm_gpio_isrc_is_level (struct bcm_gpio_irqsrc*) ; 
 int /*<<< orphan*/  bcm_gpio_isrc_mask (struct bcm_gpio_softc*,struct bcm_gpio_irqsrc*) ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int ffs (int) ; 
 scalar_t__ intr_isrc_dispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcm_gpio_intr_internal(struct bcm_gpio_softc *sc, uint32_t bank)
{
	u_int irq;
	struct bcm_gpio_irqsrc *bgi;
	uint32_t reg;

	/* Do not care of spurious interrupt on GPIO. */
	reg = BCM_GPIO_READ(sc, BCM_GPIO_GPEDS(bank));
	while (reg != 0) {
		irq = BCM_GPIO_PINS_PER_BANK * bank + ffs(reg) - 1;
		bgi = sc->sc_isrcs + irq;
		if (!bcm_gpio_isrc_is_level(bgi))
			bcm_gpio_isrc_eoi(sc, bgi);
		if (intr_isrc_dispatch(&bgi->bgi_isrc,
		    curthread->td_intr_frame) != 0) {
			bcm_gpio_isrc_mask(sc, bgi);
			if (bcm_gpio_isrc_is_level(bgi))
				bcm_gpio_isrc_eoi(sc, bgi);
			device_printf(sc->sc_dev, "Stray irq %u disabled\n",
			    irq);
		}
		reg &= ~bgi->bgi_mask;
	}
	return (FILTER_HANDLED);
}