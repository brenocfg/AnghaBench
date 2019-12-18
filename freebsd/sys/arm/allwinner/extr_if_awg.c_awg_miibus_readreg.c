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
struct awg_softc {int mdc_div_ratio_m; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  EMAC_MII_CMD ; 
 int /*<<< orphan*/  EMAC_MII_DATA ; 
 int MDC_DIV_RATIO_M_SHIFT ; 
 int MII_BUSY ; 
 int MII_BUSY_RETRY ; 
 int PHY_ADDR_SHIFT ; 
 int PHY_REG_ADDR_SHIFT ; 
 int RD4 (struct awg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct awg_softc*,int /*<<< orphan*/ ,int) ; 
 struct awg_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int
awg_miibus_readreg(device_t dev, int phy, int reg)
{
	struct awg_softc *sc;
	int retry, val;

	sc = device_get_softc(dev);
	val = 0;

	WR4(sc, EMAC_MII_CMD,
	    (sc->mdc_div_ratio_m << MDC_DIV_RATIO_M_SHIFT) |
	    (phy << PHY_ADDR_SHIFT) |
	    (reg << PHY_REG_ADDR_SHIFT) |
	    MII_BUSY);
	for (retry = MII_BUSY_RETRY; retry > 0; retry--) {
		if ((RD4(sc, EMAC_MII_CMD) & MII_BUSY) == 0) {
			val = RD4(sc, EMAC_MII_DATA);
			break;
		}
		DELAY(10);
	}

	if (retry == 0)
		device_printf(dev, "phy read timeout, phy=%d reg=%d\n",
		    phy, reg);

	return (val);
}