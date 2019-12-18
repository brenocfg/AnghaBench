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
struct bcm_vchiq_softc {int regs_offset; int /*<<< orphan*/  lock; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/  intr_hl; int /*<<< orphan*/ * mem_res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  cell ;
struct TYPE_2__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ UPSTREAM_DTB ; 
 int /*<<< orphan*/  bcm_vchiq_intr ; 
 struct bcm_vchiq_softc* bcm_vchiq_sc ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bcm_vchiq_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compat_data ; 
 struct bcm_vchiq_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_cache_line_size ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchiq_core_initialize () ; 
 int /*<<< orphan*/  vchiq_init () ; 

__attribute__((used)) static int
bcm_vchiq_attach(device_t dev)
{
	struct bcm_vchiq_softc *sc = device_get_softc(dev);
	phandle_t node;
	pcell_t cell;
	int rid = 0;

	if (bcm_vchiq_sc != NULL)
		return (EINVAL);

	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "could not allocate memory resource\n");
		return (ENXIO);
	}

	sc->bst = rman_get_bustag(sc->mem_res);
	sc->bsh = rman_get_bushandle(sc->mem_res);

	rid = 0;
	sc->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid, RF_ACTIVE);
	if (sc->irq_res == NULL) {
		device_printf(dev, "could not allocate interrupt resource\n");
		return (ENXIO);
	}

	if (ofw_bus_search_compatible(dev, compat_data)->ocd_data == UPSTREAM_DTB)
		sc->regs_offset = -0x40;

	node = ofw_bus_get_node(dev);
	if ((OF_getencprop(node, "cache-line-size", &cell, sizeof(cell))) > 0)
		g_cache_line_size = cell;

	vchiq_core_initialize();

	/* Setup and enable the timer */
	if (bus_setup_intr(dev, sc->irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
			NULL, bcm_vchiq_intr, sc,
			&sc->intr_hl) != 0) {
		bus_release_resource(dev, SYS_RES_IRQ, rid,
			sc->irq_res);
		device_printf(dev, "Unable to setup the clock irq handler.\n");
		return (ENXIO);
	}

	mtx_init(&sc->lock, "vchiq", 0, MTX_DEF);
	bcm_vchiq_sc = sc;

	vchiq_init();

	bus_generic_probe(dev);
	bus_generic_attach(dev);

	return (0);
}