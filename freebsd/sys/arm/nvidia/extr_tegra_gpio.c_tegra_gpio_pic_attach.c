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
struct tegra_gpio_softc {int gpio_npins; int /*<<< orphan*/  dev; TYPE_1__* isrcs; } ;
struct TYPE_2__ {size_t irq; int /*<<< orphan*/  isrc; scalar_t__ cfgreg; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int intr_isrc_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,size_t) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tegra_gpio_pic_attach(struct tegra_gpio_softc *sc)
{
	int error;
	uint32_t irq;
	const char *name;

	sc->isrcs = malloc(sizeof(*sc->isrcs) * sc->gpio_npins, M_DEVBUF,
	    M_WAITOK | M_ZERO);

	name = device_get_nameunit(sc->dev);
	for (irq = 0; irq < sc->gpio_npins; irq++) {
		sc->isrcs[irq].irq = irq;
		sc->isrcs[irq].cfgreg = 0;
		error = intr_isrc_register(&sc->isrcs[irq].isrc,
		    sc->dev, 0, "%s,%u", name, irq);
		if (error != 0)
			return (error); /* XXX deregister ISRCs */
	}
	if (intr_pic_register(sc->dev,
	    OF_xref_from_node(ofw_bus_get_node(sc->dev))) == NULL)
		return (ENXIO);

	return (0);
}