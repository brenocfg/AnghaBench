#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct intr_irqsrc {int dummy; } ;
struct beripic_softc {int nirqs; int mips_hard_irq_idx; int /*<<< orphan*/ * ih; TYPE_2__* hirq; int /*<<< orphan*/ * res; int /*<<< orphan*/  dev; TYPE_1__* irqs; } ;
struct beri_pic_isrc {scalar_t__ mips_hard_irq; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int irq; struct beripic_softc* sc; } ;
struct TYPE_3__ {int irq; struct intr_irqsrc isrc; } ;

/* Variables and functions */
 size_t BP_CFG ; 
 int BP_NUM_HARD_IRQS ; 
 int BP_NUM_IRQS ; 
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_CLK ; 
 intptr_t OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beri_pic_intr ; 
 int /*<<< orphan*/  beri_pic_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct beripic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int intr_isrc_register (struct intr_irqsrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intr_pic_deregister (int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
beripic_attach(device_t dev)
{
	struct beripic_softc *sc;
	struct beri_pic_isrc *pic_isrc;
	const char *name;
	struct intr_irqsrc *isrc;
	intptr_t xref;
	uint32_t unit;
	int err;
	int i;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, beri_pic_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	xref = OF_xref_from_node(ofw_bus_get_node(dev));
	name = device_get_nameunit(dev);
	unit = device_get_unit(dev);
	sc->nirqs = BP_NUM_IRQS;

	for (i = 0; i < sc->nirqs; i++) {
		sc->irqs[i].irq = i;
		isrc = &sc->irqs[i].isrc;

		/* Assign mips hard irq number. */
		pic_isrc = (struct beri_pic_isrc *)isrc;
		pic_isrc->mips_hard_irq = sc->mips_hard_irq_idx++;
		/* Last IRQ is used for IPIs. */
		if (sc->mips_hard_irq_idx >= (BP_NUM_HARD_IRQS - 1)) {
			sc->mips_hard_irq_idx = 0;
		}

		err = intr_isrc_register(isrc, sc->dev,
		    0, "pic%d,%d", unit, i);
		bus_write_8(sc->res[BP_CFG], i * 8, 0);
	}

	/*
	 * Now, when everything is initialized, it's right time to
	 * register interrupt controller to interrupt framefork.
	 */
	if (intr_pic_register(dev, xref) == NULL) {
		device_printf(dev, "could not register PIC\n");
		return (ENXIO);
	}

	/* Last IRQ is used for IPIs. */
	for (i = 0; i < (BP_NUM_HARD_IRQS - 1); i++) {
		sc->hirq[i].sc = sc;
		sc->hirq[i].irq = i;
		if (bus_setup_intr(dev, sc->res[4+i], INTR_TYPE_CLK,
		    beri_pic_intr, NULL, &sc->hirq[i], sc->ih[i])) {
			device_printf(dev, "could not setup irq handler\n");
			intr_pic_deregister(dev, xref);
			return (ENXIO);
		}
	}

	return (0);
}