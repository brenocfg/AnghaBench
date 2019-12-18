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
struct xae_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MDIO_CTRL_INITIATE ; 
 int MDIO_CTRL_TX_OP_WRITE ; 
 int MDIO_TX_PHYAD_S ; 
 int MDIO_TX_REGAD_S ; 
 int /*<<< orphan*/  WRITE4 (struct xae_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XAE_MDIO_CTRL ; 
 int /*<<< orphan*/  XAE_MDIO_WRITE ; 
 struct xae_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ mdio_wait (struct xae_softc*) ; 

__attribute__((used)) static int
xae_miibus_write_reg(device_t dev, int phy, int reg, int val)
{
	struct xae_softc *sc;
	uint32_t mii;

	sc = device_get_softc(dev);

	if (mdio_wait(sc))
		return (1);

	mii = MDIO_CTRL_TX_OP_WRITE | MDIO_CTRL_INITIATE;
	mii |= (reg << MDIO_TX_REGAD_S);
	mii |= (phy << MDIO_TX_PHYAD_S);

	WRITE4(sc, XAE_MDIO_WRITE, val);
	WRITE4(sc, XAE_MDIO_CTRL, mii);

	if (mdio_wait(sc))
		return (1);

	return (0);
}