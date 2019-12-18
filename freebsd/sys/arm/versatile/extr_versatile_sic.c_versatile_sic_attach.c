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
typedef  size_t uint32_t ;
struct versatile_sic_softc {int /*<<< orphan*/  dev; struct versatile_sic_irqsrc* isrcs; int /*<<< orphan*/  intrh; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/ * mem_res; int /*<<< orphan*/  mtx; } ;
struct versatile_sic_irqsrc {size_t irq; int /*<<< orphan*/  isrc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SIC_ENCLR ; 
 size_t SIC_NIRQS ; 
 int /*<<< orphan*/  SIC_WRITE_4 (struct versatile_sic_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct versatile_sic_softc*,int /*<<< orphan*/ *) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct versatile_sic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int intr_isrc_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,size_t) ; 
 int /*<<< orphan*/  intr_pic_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  versatile_sic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  versatile_sic_filter ; 

__attribute__((used)) static int
versatile_sic_attach(device_t dev)
{
	struct		versatile_sic_softc *sc = device_get_softc(dev);
	int		rid, error;
	uint32_t	irq;
	const char	*name;
	struct		versatile_sic_irqsrc *isrcs;

	sc->dev = dev;
	mtx_init(&sc->mtx, device_get_nameunit(dev), "sic",
	    MTX_SPIN);

	/* Request memory resources */
	rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "Error: could not allocate memory resources\n");
		return (ENXIO);
	}

	/* Request memory resources */
	rid = 0;
	sc->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (sc->irq_res == NULL) {
		device_printf(dev, "could not allocate IRQ resources\n");
		versatile_sic_detach(dev);
		return (ENXIO);
	}

	if ((bus_setup_intr(dev, sc->irq_res, INTR_TYPE_MISC,
	    versatile_sic_filter, NULL, sc, &sc->intrh))) {
		device_printf(dev,
		    "unable to register interrupt handler\n");
		versatile_sic_detach(dev);
		return (ENXIO);
	}

	/* Disable all interrupts on SIC */
	SIC_WRITE_4(sc, SIC_ENCLR, 0xffffffff);

	/* PIC attachment */
	isrcs = sc->isrcs;
	name = device_get_nameunit(sc->dev);
	for (irq = 0; irq < SIC_NIRQS; irq++) {
		isrcs[irq].irq = irq;
		error = intr_isrc_register(&isrcs[irq].isrc, sc->dev,
		    0, "%s,%u", name, irq);
		if (error != 0)
			return (error);
	}

	intr_pic_register(dev, OF_xref_from_node(ofw_bus_get_node(dev)));

	return (0);
}