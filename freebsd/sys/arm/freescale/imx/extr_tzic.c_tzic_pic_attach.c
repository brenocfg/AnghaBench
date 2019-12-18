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
typedef  size_t u_int ;
struct tzic_softc {int /*<<< orphan*/  dev; TYPE_1__* isrcs; } ;
struct intr_pic {int dummy; } ;
struct TYPE_2__ {size_t irq; int /*<<< orphan*/  isrc; } ;

/* Variables and functions */
 int ENXIO ; 
 intptr_t OF_xref_from_node (int /*<<< orphan*/ ) ; 
 size_t TZIC_NIRQS ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int intr_isrc_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,size_t) ; 
 int intr_pic_claim_root (int /*<<< orphan*/ ,intptr_t,int /*<<< orphan*/ ,struct tzic_softc*,int /*<<< orphan*/ ) ; 
 struct intr_pic* intr_pic_register (int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tzic_intr ; 

__attribute__((used)) static int
tzic_pic_attach(struct tzic_softc *sc)
{
	struct intr_pic *pic;
	const char *name;
	intptr_t xref;
	int error;
	u_int irq;

	name = device_get_nameunit(sc->dev);
	for (irq = 0; irq < TZIC_NIRQS; irq++) {
		sc->isrcs[irq].irq = irq;
		error = intr_isrc_register(&sc->isrcs[irq].isrc,
		    sc->dev, 0, "%s,%u", name, irq);
		if (error != 0)
			return (error);
	}

	xref = OF_xref_from_node(ofw_bus_get_node(sc->dev));
	pic = intr_pic_register(sc->dev, xref);
	if (pic == NULL)
		return (ENXIO);

	return (intr_pic_claim_root(sc->dev, xref, tzic_intr, sc, 0));
}