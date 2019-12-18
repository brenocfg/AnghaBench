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
typedef  int uint32_t ;
struct cpswp_softc {int /*<<< orphan*/  phyaccess; int /*<<< orphan*/  swsc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MDIO_PHYACCESS_GO ; 
 int MDIO_PHYACCESS_WRITE ; 
 int /*<<< orphan*/  cpsw_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpswp_miibus_ready (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cpswp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
cpswp_miibus_writereg(device_t dev, int phy, int reg, int value)
{
	struct cpswp_softc *sc;
	uint32_t cmd;

	sc = device_get_softc(dev);
	if (!cpswp_miibus_ready(sc->swsc, sc->phyaccess)) {
		device_printf(dev, "MDIO not ready to write\n");
		return (0);
	}

	/* Set GO, WRITE, reg, phy, and value */
	cmd = MDIO_PHYACCESS_GO | MDIO_PHYACCESS_WRITE |
	    (reg & 0x1F) << 21 | (phy & 0x1F) << 16 | (value & 0xFFFF);
	cpsw_write_4(sc->swsc, sc->phyaccess, cmd);

	if (!cpswp_miibus_ready(sc->swsc, sc->phyaccess)) {
		device_printf(dev, "MDIO timed out during write\n");
		return (0);
	}

	return (0);
}