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
typedef  size_t uint32_t ;
struct bcm_gpio_softc {int /*<<< orphan*/  sc_dev; TYPE_1__* sc_isrcs; } ;
struct TYPE_2__ {size_t bgi_irq; int /*<<< orphan*/  bgi_isrc; int /*<<< orphan*/  bgi_mode; int /*<<< orphan*/  bgi_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_GPIO_MASK (size_t) ; 
 size_t BCM_GPIO_PINS ; 
 int ENXIO ; 
 int /*<<< orphan*/  GPIO_INTR_CONFORM ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int intr_isrc_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,size_t) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcm_gpio_pic_attach(struct bcm_gpio_softc *sc)
{
	int error;
	uint32_t irq;
	const char *name;

	name = device_get_nameunit(sc->sc_dev);
	for (irq = 0; irq < BCM_GPIO_PINS; irq++) {
		sc->sc_isrcs[irq].bgi_irq = irq;
		sc->sc_isrcs[irq].bgi_mask = BCM_GPIO_MASK(irq);
		sc->sc_isrcs[irq].bgi_mode = GPIO_INTR_CONFORM;

		error = intr_isrc_register(&sc->sc_isrcs[irq].bgi_isrc,
		    sc->sc_dev, 0, "%s,%u", name, irq);
		if (error != 0)
			return (error); /* XXX deregister ISRCs */
	}
	if (intr_pic_register(sc->sc_dev,
	    OF_xref_from_node(ofw_bus_get_node(sc->sc_dev))) == NULL)
		return (ENXIO);

	return (0);
}