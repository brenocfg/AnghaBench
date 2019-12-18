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
struct usb_nop_xceiv_softc {scalar_t__ clk_freq; scalar_t__ vcc_supply; int /*<<< orphan*/  clk; } ;
struct phynode {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_SET_ROUND_ANY ; 
 int ENXIO ; 
 int ERANGE ; 
 int clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_set_freq (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct usb_nop_xceiv_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  phynode_get_device (struct phynode*) ; 
 intptr_t phynode_get_id (struct phynode*) ; 
 int regulator_disable (scalar_t__) ; 
 int regulator_enable (scalar_t__) ; 

__attribute__((used)) static int
usb_nop_xceiv_phy_enable(struct phynode *phynode, bool enable)
{
	struct usb_nop_xceiv_softc *sc;
	device_t dev;
	intptr_t phy;
	int error;

	dev = phynode_get_device(phynode);
	phy = phynode_get_id(phynode);
	sc = device_get_softc(dev);

	if (phy != 0)
		return (ERANGE);

	/* Enable the phy clock */
	if (sc->clk_freq != 0) {
		if (enable) {
			error = clk_set_freq(sc->clk, sc->clk_freq,
			  CLK_SET_ROUND_ANY);
			if (error != 0) {
				device_printf(dev, "Cannot set clock to %dMhz\n",
				  sc->clk_freq);
				goto fail;
			}

			error = clk_enable(sc->clk);
		} else
			error = clk_disable(sc->clk);

		if (error != 0) {
			device_printf(dev, "Cannot %sable the clock\n",
			    enable ? "En" : "Dis");
			goto fail;
		}
	}
	if (sc->vcc_supply) {
		if (enable)
			error = regulator_enable(sc->vcc_supply);
		else
			error = regulator_disable(sc->vcc_supply);
		if (error != 0) {
			device_printf(dev, "Cannot %sable the regulator\n",
			    enable ? "En" : "Dis");
			goto fail;
		}
	}

	return (0);

fail:
	return (ENXIO);
}