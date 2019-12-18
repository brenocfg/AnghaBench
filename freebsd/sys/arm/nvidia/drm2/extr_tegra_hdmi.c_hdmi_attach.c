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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct hdmi_softc {int audio_freq; int audio_chans; int hdmi_mode; int /*<<< orphan*/ * mem_res; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/ * supply_vdd; int /*<<< orphan*/ * supply_pll; int /*<<< orphan*/ * supply_hdmi; int /*<<< orphan*/ * hwreset_hdmi; int /*<<< orphan*/ * clk_hdmi; int /*<<< orphan*/ * clk_parent; int /*<<< orphan*/ * irq_ih; int /*<<< orphan*/  dev; int /*<<< orphan*/  n_tmds_configs; int /*<<< orphan*/  tmds_config; int /*<<< orphan*/  audio_src_type; TYPE_1__ output; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SOURCE_SELECT_AUTO ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TEGRA_DRM_DEREGISTER_CLIENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TEGRA_DRM_REGISTER_CLIENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct hdmi_softc*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct hdmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int enable_fdt_resources (struct hdmi_softc*) ; 
 int get_fdt_resources (struct hdmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_intr ; 
 int /*<<< orphan*/  hwreset_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra124_tmds_config ; 

__attribute__((used)) static int
hdmi_attach(device_t dev)
{
	struct hdmi_softc *sc;
	phandle_t node;
	int rid, rv;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->output.dev = sc->dev;
	node = ofw_bus_get_node(sc->dev);

	sc->audio_src_type = SOURCE_SELECT_AUTO;
	sc->audio_freq = 44100;
	sc->audio_chans = 2;
	sc->hdmi_mode = false;

	sc->tmds_config = tegra124_tmds_config;
	sc->n_tmds_configs = nitems(tegra124_tmds_config);

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

	rv = bus_setup_intr(dev, sc->irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, hdmi_intr, sc, &sc->irq_ih);
	if (rv != 0) {
		device_printf(dev,
		    "WARNING: unable to register interrupt handler\n");
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
	if (sc->clk_hdmi != NULL)
		clk_release(sc->clk_hdmi);
	if (sc->hwreset_hdmi != NULL)
		hwreset_release(sc->hwreset_hdmi);
	if (sc->supply_hdmi != NULL)
		regulator_release(sc->supply_hdmi);
	if (sc->supply_pll != NULL)
		regulator_release(sc->supply_pll);
	if (sc->supply_vdd != NULL)
		regulator_release(sc->supply_vdd);
	if (sc->irq_res != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->irq_res);
	if (sc->mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->mem_res);
	return (ENXIO);
}