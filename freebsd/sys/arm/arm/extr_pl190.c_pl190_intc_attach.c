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
struct pl190_intc_softc {int /*<<< orphan*/  dev; struct pl190_intc_irqsrc* isrcs; int /*<<< orphan*/ * intc_res; int /*<<< orphan*/  mtx; } ;
struct pl190_intc_irqsrc {int irq; int /*<<< orphan*/  isrc; } ;
struct intr_pic {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTC_VIC_READ_4 (struct pl190_intc_softc*,scalar_t__) ; 
 int /*<<< orphan*/  INTC_VIC_WRITE_4 (struct pl190_intc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  VICINTENCLEAR ; 
 int /*<<< orphan*/  VICINTSELECT ; 
 scalar_t__ VICPERIPHID ; 
 scalar_t__ VICPRIMECELLID ; 
 int VIC_NIRQS ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct pl190_intc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int intr_isrc_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int) ; 
 int intr_pic_claim_root (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pl190_intc_softc*,int /*<<< orphan*/ ) ; 
 struct intr_pic* intr_pic_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl190_intc_intr ; 

__attribute__((used)) static int
pl190_intc_attach(device_t dev)
{
	struct		pl190_intc_softc *sc;
	uint32_t	id;
	int		i, rid;
	struct		pl190_intc_irqsrc *isrcs;
	struct intr_pic *pic;
	int		error;
	uint32_t	irq;
	const char	*name;
	phandle_t	xref;

	sc = device_get_softc(dev);
	sc->dev = dev;
	mtx_init(&sc->mtx, device_get_nameunit(dev), "pl190",
	    MTX_SPIN);

	/* Request memory resources */
	rid = 0;
	sc->intc_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->intc_res == NULL) {
		device_printf(dev, "Error: could not allocate memory resources\n");
		return (ENXIO);
	}

	/*
	 * All interrupts should use IRQ line
	 */
	INTC_VIC_WRITE_4(sc, VICINTSELECT, 0x00000000);
	/* Disable all interrupts */
	INTC_VIC_WRITE_4(sc, VICINTENCLEAR, 0xffffffff);

	id = 0;
	for (i = 3; i >= 0; i--) {
		id = (id << 8) |
		     (INTC_VIC_READ_4(sc, VICPERIPHID + i*4) & 0xff);
	}

	device_printf(dev, "Peripheral ID: %08x\n", id);

	id = 0;
	for (i = 3; i >= 0; i--) {
		id = (id << 8) |
		     (INTC_VIC_READ_4(sc, VICPRIMECELLID + i*4) & 0xff);
	}

	device_printf(dev, "PrimeCell ID: %08x\n", id);

	/* PIC attachment */
	isrcs = sc->isrcs;
	name = device_get_nameunit(sc->dev);
	for (irq = 0; irq < VIC_NIRQS; irq++) {
		isrcs[irq].irq = irq;
		error = intr_isrc_register(&isrcs[irq].isrc, sc->dev,
		    0, "%s,%u", name, irq);
		if (error != 0)
			return (error);
	}

	xref = OF_xref_from_node(ofw_bus_get_node(sc->dev));
	pic = intr_pic_register(sc->dev, xref);
	if (pic == NULL)
		return (ENXIO);

	return (intr_pic_claim_root(sc->dev, xref, pl190_intc_intr, sc, 0));
}