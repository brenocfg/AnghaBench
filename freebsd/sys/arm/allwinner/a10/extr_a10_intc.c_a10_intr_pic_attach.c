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
struct intr_pic {int dummy; } ;
struct a10_aintc_softc {int /*<<< orphan*/  sc_dev; TYPE_1__* isrcs; } ;
struct TYPE_2__ {size_t irq; int /*<<< orphan*/  isrc; } ;

/* Variables and functions */
 size_t A10_INTR_MAX_NIRQS ; 
 int ENXIO ; 
 intptr_t OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a10_intr ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int intr_isrc_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,size_t) ; 
 int intr_pic_claim_root (int /*<<< orphan*/ ,intptr_t,int /*<<< orphan*/ ,struct a10_aintc_softc*,int /*<<< orphan*/ ) ; 
 struct intr_pic* intr_pic_register (int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
a10_intr_pic_attach(struct a10_aintc_softc *sc)
{
	struct intr_pic *pic;
	int error;
	uint32_t irq;
	const char *name;
	intptr_t xref;

	name = device_get_nameunit(sc->sc_dev);
	for (irq = 0; irq < A10_INTR_MAX_NIRQS; irq++) {
		sc->isrcs[irq].irq = irq;

		error = intr_isrc_register(&sc->isrcs[irq].isrc,
		    sc->sc_dev, 0, "%s,%u", name, irq);
		if (error != 0)
			return (error);
	}

	xref = OF_xref_from_node(ofw_bus_get_node(sc->sc_dev));
	pic = intr_pic_register(sc->sc_dev, xref);
	if (pic == NULL)
		return (ENXIO);

	return (intr_pic_claim_root(sc->sc_dev, xref, a10_intr, sc, 0));
}