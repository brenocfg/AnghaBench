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
struct rk_usb2phy_softc {int mode; } ;
struct phynode {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ERANGE ; 
 intptr_t RK3399_USBPHY_HOST ; 
 struct rk_usb2phy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phynode_get_device (struct phynode*) ; 
 intptr_t phynode_get_id (struct phynode*) ; 

__attribute__((used)) static int
rk_usb2phy_set_mode(struct phynode *phynode, int mode)
{
	struct rk_usb2phy_softc *sc;
	intptr_t phy;
	device_t dev;

	dev = phynode_get_device(phynode);
	phy = phynode_get_id(phynode);
	sc = device_get_softc(dev);

	if (phy != RK3399_USBPHY_HOST)
		return (ERANGE);

	sc->mode = mode;

	return (0);
}