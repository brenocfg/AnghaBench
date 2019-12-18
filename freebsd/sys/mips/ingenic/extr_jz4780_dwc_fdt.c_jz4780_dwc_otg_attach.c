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
typedef  int uint32_t ;
struct resource {int dummy; } ;
struct TYPE_3__ {int sc_phy_bits; int /*<<< orphan*/  sc_phy_type; } ;
struct TYPE_4__ {TYPE_1__ sc_otg; } ;
struct jz4780_dwc_otg_softc {scalar_t__ phy_clk; scalar_t__ otg_clk; TYPE_2__ base; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_OTG_PHY_UTMI ; 
 int /*<<< orphan*/  JZ_DWC2_GUSBCFG ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_read_4 (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  bus_write_4 (struct resource*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_release (scalar_t__) ; 
 struct jz4780_dwc_otg_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int dwc_otg_attach (int /*<<< orphan*/ ) ; 
 int jz4780_dwc_otg_clk_enable (int /*<<< orphan*/ ) ; 
 int jz4780_otg_enable () ; 

__attribute__((used)) static int
jz4780_dwc_otg_attach(device_t dev)
{
	struct jz4780_dwc_otg_softc *sc;
	struct resource *res;
	int err, rid;

	sc = device_get_softc(dev);

	err = jz4780_dwc_otg_clk_enable(dev);
	if (err != 0)
		goto fail;

	err = jz4780_otg_enable();
	if (err != 0) {
		device_printf(dev, "CGU failed to enable OTG\n");
		goto fail;
	}

	/* Voodoo: Switch off VBUS overcurrent detection in OTG PHY */
	res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (res != NULL) {
		uint32_t reg;

		reg = bus_read_4(res, JZ_DWC2_GUSBCFG);
		reg |= 0xc;
		bus_write_4(res, JZ_DWC2_GUSBCFG, reg);
		bus_release_resource(dev, SYS_RES_MEMORY, rid, res);
	}

	sc->base.sc_otg.sc_phy_type = DWC_OTG_PHY_UTMI;
	sc->base.sc_otg.sc_phy_bits = 16;

	err = dwc_otg_attach(dev);
	if (err != 0)
		goto fail;

	return (0);
fail:
	if (sc->otg_clk)
		clk_release(sc->otg_clk);
	if (sc->phy_clk)
		clk_release(sc->phy_clk);
	return (err);
}