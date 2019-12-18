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
struct et_softc {int /*<<< orphan*/  ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CSR_READ_4 (struct et_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct et_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ET_MII_ADDR ; 
 int ET_MII_ADDR_PHY_MASK ; 
 int ET_MII_ADDR_PHY_SHIFT ; 
 int ET_MII_ADDR_REG_MASK ; 
 int ET_MII_ADDR_REG_SHIFT ; 
 int /*<<< orphan*/  ET_MII_CMD ; 
 int ET_MII_CMD_READ ; 
 int /*<<< orphan*/  ET_MII_IND ; 
 int ET_MII_IND_BUSY ; 
 int ET_MII_IND_INVALID ; 
 int /*<<< orphan*/  ET_MII_STAT ; 
 int ET_MII_STAT_VALUE_MASK ; 
 int NRETRY ; 
 struct et_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int
et_miibus_readreg(device_t dev, int phy, int reg)
{
	struct et_softc *sc;
	uint32_t val;
	int i, ret;

	sc = device_get_softc(dev);
	/* Stop any pending operations */
	CSR_WRITE_4(sc, ET_MII_CMD, 0);

	val = (phy << ET_MII_ADDR_PHY_SHIFT) & ET_MII_ADDR_PHY_MASK;
	val |= (reg << ET_MII_ADDR_REG_SHIFT) & ET_MII_ADDR_REG_MASK;
	CSR_WRITE_4(sc, ET_MII_ADDR, val);

	/* Start reading */
	CSR_WRITE_4(sc, ET_MII_CMD, ET_MII_CMD_READ);

#define NRETRY	50

	for (i = 0; i < NRETRY; ++i) {
		val = CSR_READ_4(sc, ET_MII_IND);
		if ((val & (ET_MII_IND_BUSY | ET_MII_IND_INVALID)) == 0)
			break;
		DELAY(50);
	}
	if (i == NRETRY) {
		if_printf(sc->ifp,
			  "read phy %d, reg %d timed out\n", phy, reg);
		ret = 0;
		goto back;
	}

#undef NRETRY

	val = CSR_READ_4(sc, ET_MII_STAT);
	ret = val & ET_MII_STAT_VALUE_MASK;

back:
	/* Make sure that the current operation is stopped */
	CSR_WRITE_4(sc, ET_MII_CMD, 0);
	return (ret);
}