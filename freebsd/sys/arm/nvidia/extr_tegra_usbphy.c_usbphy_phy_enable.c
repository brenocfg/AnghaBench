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
struct usbphy_softc {scalar_t__ ifc_type; int /*<<< orphan*/  dev; } ;
struct phynode {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ USB_IFC_TYPE_UTMI ; 
 struct usbphy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  phynode_get_device (struct phynode*) ; 
 int usbphy_utmi_disable (struct usbphy_softc*) ; 
 int usbphy_utmi_enable (struct usbphy_softc*) ; 

__attribute__((used)) static int
usbphy_phy_enable(struct phynode *phy, bool enable)
{
	device_t dev;
	struct usbphy_softc *sc;
	int rv = 0;

	dev = phynode_get_device(phy);
	sc = device_get_softc(dev);

	if (sc->ifc_type != USB_IFC_TYPE_UTMI) {
			device_printf(sc->dev,
			    "Only UTMI interface is supported.\n");
			return (ENXIO);
	}
	if (enable)
		rv = usbphy_utmi_enable(sc);
	else
		rv = usbphy_utmi_disable(sc);

	return (rv);
}