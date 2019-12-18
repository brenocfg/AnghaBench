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
struct phynode {int dummy; } ;
struct awusb3phy_softc {int mode; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int PHY_USB_MODE_HOST ; 
 struct awusb3phy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phynode_get_device (struct phynode*) ; 
 intptr_t phynode_get_id (struct phynode*) ; 

__attribute__((used)) static int
awusb3phy_set_mode(struct phynode *phynode, int mode)
{
	device_t dev;
	intptr_t phy;
	struct awusb3phy_softc *sc;

	dev = phynode_get_device(phynode);
	phy = phynode_get_id(phynode);
	sc = device_get_softc(dev);

	if (mode != PHY_USB_MODE_HOST)
		return (EINVAL);

	sc->mode = mode;

	return (0);
}