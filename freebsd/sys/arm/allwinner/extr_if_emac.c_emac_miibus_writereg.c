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
struct emac_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_MAC_MADR ; 
 int /*<<< orphan*/  EMAC_MAC_MCMD ; 
 int /*<<< orphan*/  EMAC_MAC_MWTD ; 
 int /*<<< orphan*/  EMAC_WRITE_REG (struct emac_softc*,int /*<<< orphan*/ ,int) ; 
 struct emac_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  emac_miibus_iowait (struct emac_softc*) ; 

__attribute__((used)) static int
emac_miibus_writereg(device_t dev, int phy, int reg, int data)
{
	struct emac_softc *sc;

	sc = device_get_softc(dev);

	/* Issue phy address and reg */
	EMAC_WRITE_REG(sc, EMAC_MAC_MADR, (phy << 8) | reg);
	/* Write data */
	EMAC_WRITE_REG(sc, EMAC_MAC_MWTD, data);
	/* Pull up the phy io line */
	EMAC_WRITE_REG(sc, EMAC_MAC_MCMD, 0x1);
	if (!emac_miibus_iowait(sc)) {
		device_printf(dev, "timeout waiting for mii write\n");
		return (0);
	}
	/* Push down the phy io line */
	EMAC_WRITE_REG(sc, EMAC_MAC_MCMD, 0x0);

	return (0);
}