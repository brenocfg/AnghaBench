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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ sc_reg_shift; int /*<<< orphan*/ * sc_mem_res; scalar_t__ sc_mem_rid; int /*<<< orphan*/  sc_get_i2c_dev; int /*<<< orphan*/  sc_dev; } ;
struct dwc_hdmi_fdt_softc {int /*<<< orphan*/  clk_ahb; int /*<<< orphan*/  clk_hdmi; TYPE_1__ base; scalar_t__ i2c_xref; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  i2c_xref ;
typedef  int /*<<< orphan*/  freq ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_SET_ROUND_DOWN ; 
 int ENXIO ; 
 int OF_getencprop (scalar_t__,char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ clk_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int clk_set_freq (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct dwc_hdmi_fdt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dwc_hdmi_fdt_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_hdmi_fdt_get_i2c_dev ; 
 int dwc_hdmi_init (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dwc_hdmi_fdt_attach(device_t dev)
{
	struct dwc_hdmi_fdt_softc *sc;
	phandle_t node, i2c_xref;
	uint32_t freq;
	int err;

	sc = device_get_softc(dev);
	sc->base.sc_dev = dev;
	sc->base.sc_get_i2c_dev = dwc_hdmi_fdt_get_i2c_dev;
	err = 0;

	/* Allocate memory resources. */
	sc->base.sc_mem_rid = 0;
	sc->base.sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &sc->base.sc_mem_rid, RF_ACTIVE);
	if (sc->base.sc_mem_res == NULL) {
		device_printf(dev, "Cannot allocate memory resources\n");
		err = ENXIO;
		goto out;
	}

	node = ofw_bus_get_node(dev);
	if (OF_getencprop(node, "ddc", &i2c_xref, sizeof(i2c_xref)) == -1)
		sc->i2c_xref = 0;
	else
		sc->i2c_xref = i2c_xref;

	if (OF_getencprop(node, "reg-shift", &sc->base.sc_reg_shift,
	    sizeof(sc->base.sc_reg_shift)) <= 0)
		sc->base.sc_reg_shift = 0;

	if (clk_get_by_ofw_name(dev, 0, "hdmi", &sc->clk_hdmi) != 0 ||
	    clk_get_by_ofw_name(dev, 0, "ahb", &sc->clk_ahb) != 0) {
		device_printf(dev, "Cannot get clocks\n");
		err = ENXIO;
		goto out;
	}
	if (OF_getencprop(node, "clock-frequency", &freq, sizeof(freq)) > 0) {
		err = clk_set_freq(sc->clk_hdmi, freq, CLK_SET_ROUND_DOWN);
		if (err != 0) {
			device_printf(dev,
			    "Cannot set HDMI clock frequency to %u Hz\n", freq);
			goto out;
		}
	} else
		device_printf(dev, "HDMI clock frequency not specified\n");
	if (clk_enable(sc->clk_hdmi) != 0) {
		device_printf(dev, "Cannot enable HDMI clock\n");
		err = ENXIO;
		goto out;
	}
	if (clk_enable(sc->clk_ahb) != 0) {
		device_printf(dev, "Cannot enable AHB clock\n");
		err = ENXIO;
		goto out;
	}

	return (dwc_hdmi_init(dev));

out:

	dwc_hdmi_fdt_detach(dev);

	return (err);
}