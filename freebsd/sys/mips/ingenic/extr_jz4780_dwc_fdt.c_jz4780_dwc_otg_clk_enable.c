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
struct jz4780_dwc_otg_softc {int /*<<< orphan*/  phy_clk; int /*<<< orphan*/  otg_clk; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int clk_set_freq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct jz4780_dwc_otg_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int
jz4780_dwc_otg_clk_enable(device_t dev)
{
	struct jz4780_dwc_otg_softc *sc;
	int err;

	sc = device_get_softc(dev);

	/* Configure and enable phy clock */
	err = clk_get_by_ofw_name(dev, 0, "otg_phy", &sc->phy_clk);
	if (err != 0) {
		device_printf(dev, "unable to lookup %s clock\n", "otg_phy");
		return (err);
	}
	err = clk_set_freq(sc->phy_clk, 48000000, 0);
	if (err != 0) {
		device_printf(dev, "unable to set %s clock to 48 kHZ\n",
		    "otg_phy");
		return (err);
	}
	err = clk_enable(sc->phy_clk);
	if (err != 0) {
		device_printf(dev, "unable to enable %s clock\n", "otg_phy");
		return (err);
	}

	/* Configure and enable otg1 clock */
	err = clk_get_by_ofw_name(dev, 0, "otg1", &sc->otg_clk);
	if (err != 0) {
		device_printf(dev, "unable to lookup %s clock\n", "otg1");
		return (err);
	}
	err = clk_enable(sc->phy_clk);
	if (err != 0) {
		device_printf(dev, "unable to enable %s clock\n", "otg1");
		return (err);
	}

	return (0);
}