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
struct mv_ap806_sei_softc {int /*<<< orphan*/ * mem_res; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/ * irq_ih; int /*<<< orphan*/  dev; TYPE_1__* isrcs; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int irq; int /*<<< orphan*/  isrc; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GICP_SEMR0 ; 
 int /*<<< orphan*/  GICP_SEMR1 ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MV_AP806_SEI_LOCK_DESTROY (struct mv_ap806_sei_softc*) ; 
 int /*<<< orphan*/  MV_AP806_SEI_LOCK_INIT (struct mv_ap806_sei_softc*) ; 
 int MV_AP806_SEI_MAX_NIRQS ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  WR4 (struct mv_ap806_sei_softc*,int /*<<< orphan*/ ,int) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mv_ap806_sei_softc*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct mv_ap806_sei_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int intr_isrc_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv_ap806_sei_intr ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv_ap806_sei_attach(device_t dev)
{
	struct mv_ap806_sei_softc *sc;
	phandle_t xref, node;
	uint32_t irq;
	const char *name;
	int rv, rid;

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(dev);
	MV_AP806_SEI_LOCK_INIT(sc);

	/* Allocate resources. */
	rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "Cannot allocate memory resources\n");
		rv = ENXIO;
		goto fail;
	}

	rid = 0;
	sc->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid, RF_ACTIVE);
	if (sc->irq_res == NULL) {
		device_printf(dev, "Cannot allocate IRQ resources\n");
		rv = ENXIO;
		goto fail;
	}

	/* Mask all interrupts) */
	WR4(sc, GICP_SEMR0, 0xFFFFFFFF);
	WR4(sc, GICP_SEMR1, 0xFFFFFFFF);

	/* Create all interrupt sources */
	sc->isrcs = malloc(sizeof(*sc->isrcs) * MV_AP806_SEI_MAX_NIRQS,
	    M_DEVBUF, M_WAITOK | M_ZERO);
	name = device_get_nameunit(sc->dev);
	for (irq = 0; irq < MV_AP806_SEI_MAX_NIRQS; irq++) {
		sc->isrcs[irq].irq = irq;
		rv = intr_isrc_register(&sc->isrcs[irq].isrc,
		    sc->dev, 0, "%s,%u", name, irq);
		if (rv != 0)
			goto fail; /* XXX deregister ISRCs */
	}
	xref = OF_xref_from_node(node);;
	if (intr_pic_register(dev, xref) == NULL) {
		device_printf(dev, "Cannot register SEI\n");
		rv = ENXIO;
		goto fail;
	}
	if (bus_setup_intr(dev, sc->irq_res,INTR_TYPE_MISC | INTR_MPSAFE,
	    mv_ap806_sei_intr, NULL, sc, &sc->irq_ih)) {
		device_printf(dev,
		    "Unable to register interrupt handler\n");
		rv = ENXIO;
		goto fail;
	}
	
	OF_device_register_xref(xref, dev);
	return (0);

fail:
	if (sc->irq_ih != NULL)
		bus_teardown_intr(dev, sc->irq_res, sc->irq_ih);
	if (sc->irq_res != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->irq_res);
	if (sc->mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->mem_res);
	MV_AP806_SEI_LOCK_DESTROY(sc);
	return (ENXIO);
}