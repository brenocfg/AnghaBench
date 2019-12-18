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
struct dtsec_softc {int /*<<< orphan*/  sc_mdio; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MIIBUS_WRITEREG (int /*<<< orphan*/ ,int,int,int) ; 
 struct dtsec_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
dtsec_miibus_writereg(device_t dev, int phy, int reg, int value)
{

	struct dtsec_softc *sc;

	sc = device_get_softc(dev);

	return (MIIBUS_WRITEREG(sc->sc_mdio, phy, reg, value));
}