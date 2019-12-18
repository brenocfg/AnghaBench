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
struct rk_usb2phy_softc {scalar_t__ phy_supply; } ;
struct phynode {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int ERANGE ; 
 intptr_t RK3399_USBPHY_HOST ; 
 struct rk_usb2phy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  phynode_get_device (struct phynode*) ; 
 intptr_t phynode_get_id (struct phynode*) ; 
 int regulator_disable (scalar_t__) ; 
 int regulator_enable (scalar_t__) ; 

__attribute__((used)) static int
rk_usb2phy_enable(struct phynode *phynode, bool enable)
{
	struct rk_usb2phy_softc *sc;
	device_t dev;
	intptr_t phy;
	int error;

	dev = phynode_get_device(phynode);
	phy = phynode_get_id(phynode);
	sc = device_get_softc(dev);

	if (phy != RK3399_USBPHY_HOST)
		return (ERANGE);

	if (sc->phy_supply) {
		if (enable)
			error = regulator_enable(sc->phy_supply);
		else
			error = regulator_disable(sc->phy_supply);
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