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
struct miiproxy_softc {int /*<<< orphan*/ * mdio; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MDIO_READREG (int /*<<< orphan*/ *,int,int) ; 
 struct miiproxy_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
miiproxy_readreg(device_t dev, int phy, int reg)
{
	struct miiproxy_softc *sc = device_get_softc(dev);

	if (sc->mdio != NULL)
		return (MDIO_READREG(sc->mdio, phy, reg));
	return (-1);
}