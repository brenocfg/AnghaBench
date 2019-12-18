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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/ * sc_mem_res; scalar_t__ sc_mem_rid; int /*<<< orphan*/  sc_get_i2c_dev; int /*<<< orphan*/  sc_dev; } ;
struct imx_hdmi_softc {scalar_t__ i2c_xref; TYPE_1__ base; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  i2c_xref ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IOMUXC_GPR3 ; 
 int /*<<< orphan*/  IOMUXC_GPR3_HDMI_IPU1_DI0 ; 
 int /*<<< orphan*/  IOMUXC_GPR3_HDMI_MASK ; 
 int OF_getencprop (scalar_t__,char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_intrhook_oneshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct imx_hdmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  imx_ccm_hdmi_enable () ; 
 int /*<<< orphan*/  imx_hdmi_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_hdmi_get_i2c_dev ; 
 int /*<<< orphan*/  imx_hdmi_init ; 
 int /*<<< orphan*/  imx_iomux_gpr_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_iomux_gpr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imx_hdmi_attach(device_t dev)
{
	struct imx_hdmi_softc *sc;
	int err;
	uint32_t gpr3;
	phandle_t node, i2c_xref;

	sc = device_get_softc(dev);
	sc->base.sc_dev = dev;
	sc->base.sc_get_i2c_dev = imx_hdmi_get_i2c_dev;
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
	if (OF_getencprop(node, "ddc-i2c-bus", &i2c_xref, sizeof(i2c_xref)) == -1)
		sc->i2c_xref = 0;
	else
		sc->i2c_xref = i2c_xref;

	imx_ccm_hdmi_enable();

	gpr3 = imx_iomux_gpr_get(IOMUXC_GPR3);
	gpr3 &= ~(IOMUXC_GPR3_HDMI_MASK);
	gpr3 |= IOMUXC_GPR3_HDMI_IPU1_DI0;
	imx_iomux_gpr_set(IOMUXC_GPR3, gpr3);

	/* Further HDMI init requires interrupts for i2c transfers. */
	config_intrhook_oneshot(imx_hdmi_init, dev);
	return (0);

out:
	imx_hdmi_detach(dev);

	return (err);
}