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
struct TYPE_2__ {void* dev; } ;
struct dc_softc {int pitch_align; int /*<<< orphan*/ * mem_res; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/ * hwreset_dc; int /*<<< orphan*/ * clk_dc; int /*<<< orphan*/ * clk_parent; int /*<<< orphan*/ * irq_ih; void* dev; TYPE_1__ tegra_crtc; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  void* device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  LOCK_DESTROY (struct dc_softc*) ; 
 int /*<<< orphan*/  LOCK_INIT (struct dc_softc*) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TEGRA_DRM_DEREGISTER_CLIENT (int /*<<< orphan*/ ,void*) ; 
 int TEGRA_DRM_REGISTER_CLIENT (int /*<<< orphan*/ ,void*) ; 
 void* bus_alloc_resource_any (void*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (void*) ; 
 int /*<<< orphan*/  bus_release_resource (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (void*) ; 
 struct dc_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*) ; 
 int enable_fdt_resources (struct dc_softc*) ; 
 int get_fdt_resources (struct dc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwreset_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_get_node (void*) ; 

__attribute__((used)) static int
dc_attach(device_t dev)
{
	struct dc_softc *sc;
	phandle_t node;
	int rid, rv;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->tegra_crtc.dev = dev;

	node = ofw_bus_get_node(sc->dev);
	LOCK_INIT(sc);

	rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "Cannot allocate memory resources\n");
		goto fail;
	}

	rid = 0;
	sc->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid, RF_ACTIVE);
	if (sc->irq_res == NULL) {
		device_printf(dev, "Cannot allocate IRQ resources\n");
		goto fail;
	}

	rv = get_fdt_resources(sc, node);
	if (rv != 0) {
		device_printf(dev, "Cannot parse FDT resources\n");
		goto fail;
	}
	rv = enable_fdt_resources(sc);
	if (rv != 0) {
		device_printf(dev, "Cannot enable FDT resources\n");
		goto fail;
	}

	/*
	 * Tegra124
	 *  -  64 for RGB modes
	 *  - 128 for YUV planar modes
	 *  - 256 for block linear modes
	 */
	sc->pitch_align = 256;

	rv = TEGRA_DRM_REGISTER_CLIENT(device_get_parent(sc->dev), sc->dev);
	if (rv != 0) {
		device_printf(dev, "Cannot register DRM device\n");
		goto fail;
	}

	return (bus_generic_attach(dev));

fail:
	TEGRA_DRM_DEREGISTER_CLIENT(device_get_parent(sc->dev), sc->dev);
	if (sc->irq_ih != NULL)
		bus_teardown_intr(dev, sc->irq_res, sc->irq_ih);
	if (sc->clk_parent != NULL)
		clk_release(sc->clk_parent);
	if (sc->clk_dc != NULL)
		clk_release(sc->clk_dc);
	if (sc->hwreset_dc != NULL)
		hwreset_release(sc->hwreset_dc);
	if (sc->irq_res != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->irq_res);
	if (sc->mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->mem_res);
	LOCK_DESTROY(sc);

	return (ENXIO);
}