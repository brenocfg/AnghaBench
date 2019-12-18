#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct alc_softc {int alc_flags; int alc_rev; TYPE_1__* alc_ident; int /*<<< orphan*/  alc_dev; } ;
struct TYPE_2__ {scalar_t__ deviceid; } ;

/* Variables and functions */
 int ALC_FLAG_AR816X_FAMILY ; 
 int /*<<< orphan*/  ALC_IDLE_STATUS ; 
 int /*<<< orphan*/  ALC_MASTER_CFG ; 
 int /*<<< orphan*/  ALC_MBOX_RD0_PROD_IDX ; 
 int /*<<< orphan*/  ALC_MISC ; 
 int /*<<< orphan*/  ALC_MISC3 ; 
 int /*<<< orphan*/  ALC_PM_CFG ; 
 int ALC_RESET_TIMEOUT ; 
 int /*<<< orphan*/  ALC_SERDES_LOCK ; 
 scalar_t__ AR816X_REV (int) ; 
 scalar_t__ AR816X_REV_A1 ; 
 int CSR_READ_4 (struct alc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct alc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ DEVICEID_ATHEROS_AR8151_V2 ; 
 scalar_t__ DEVICEID_ATHEROS_AR8152_B ; 
 int IDLE_STATUS_RXMAC ; 
 int IDLE_STATUS_RXQ ; 
 int IDLE_STATUS_TXMAC ; 
 int IDLE_STATUS_TXQ ; 
 int MASTER_CLK_SEL_DIS ; 
 int MASTER_OOB_DIS_OFF ; 
 int MASTER_RESET ; 
 int MISC3_25M_BY_SW ; 
 int MISC3_25M_NOTO_INTNL ; 
 int MISC_INTNLOSC_OPEN ; 
 int MISC_ISO_ENB ; 
 int PM_CFG_ASPM_L0S_ENB ; 
 int PM_CFG_ASPM_L1_ENB ; 
 int SERDES_MAC_CLK_SLOWDOWN ; 
 int SERDES_PHY_CLK_SLOWDOWN ; 
 int /*<<< orphan*/  alc_osc_reset (struct alc_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
alc_reset(struct alc_softc *sc)
{
	uint32_t pmcfg, reg;
	int i;

	pmcfg = 0;
	if ((sc->alc_flags & ALC_FLAG_AR816X_FAMILY) != 0) {
		/* Reset workaround. */
		CSR_WRITE_4(sc, ALC_MBOX_RD0_PROD_IDX, 1);
		if (AR816X_REV(sc->alc_rev) <= AR816X_REV_A1 &&
		    (sc->alc_rev & 0x01) != 0) {
			/* Disable L0s/L1s before reset. */
			pmcfg = CSR_READ_4(sc, ALC_PM_CFG);
			if ((pmcfg & (PM_CFG_ASPM_L0S_ENB | PM_CFG_ASPM_L1_ENB))
			    != 0) {
				pmcfg &= ~(PM_CFG_ASPM_L0S_ENB |
				    PM_CFG_ASPM_L1_ENB);
				CSR_WRITE_4(sc, ALC_PM_CFG, pmcfg);
			}
		}
	}
	reg = CSR_READ_4(sc, ALC_MASTER_CFG);
	reg |= MASTER_OOB_DIS_OFF | MASTER_RESET;
	CSR_WRITE_4(sc, ALC_MASTER_CFG, reg);

	if ((sc->alc_flags & ALC_FLAG_AR816X_FAMILY) != 0) {
		for (i = ALC_RESET_TIMEOUT; i > 0; i--) {
			DELAY(10);
			if (CSR_READ_4(sc, ALC_MBOX_RD0_PROD_IDX) == 0)
				break;
		}
		if (i == 0)
			device_printf(sc->alc_dev, "MAC reset timeout!\n");
	}
	for (i = ALC_RESET_TIMEOUT; i > 0; i--) {
		DELAY(10);
		if ((CSR_READ_4(sc, ALC_MASTER_CFG) & MASTER_RESET) == 0)
			break;
	}
	if (i == 0)
		device_printf(sc->alc_dev, "master reset timeout!\n");

	for (i = ALC_RESET_TIMEOUT; i > 0; i--) {
		reg = CSR_READ_4(sc, ALC_IDLE_STATUS);
		if ((reg & (IDLE_STATUS_RXMAC | IDLE_STATUS_TXMAC |
		    IDLE_STATUS_RXQ | IDLE_STATUS_TXQ)) == 0)
			break;
		DELAY(10);
	}
	if (i == 0)
		device_printf(sc->alc_dev, "reset timeout(0x%08x)!\n", reg);

	if ((sc->alc_flags & ALC_FLAG_AR816X_FAMILY) != 0) {
		if (AR816X_REV(sc->alc_rev) <= AR816X_REV_A1 &&
		    (sc->alc_rev & 0x01) != 0) {
			reg = CSR_READ_4(sc, ALC_MASTER_CFG);
			reg |= MASTER_CLK_SEL_DIS;
			CSR_WRITE_4(sc, ALC_MASTER_CFG, reg);
			/* Restore L0s/L1s config. */
			if ((pmcfg & (PM_CFG_ASPM_L0S_ENB | PM_CFG_ASPM_L1_ENB))
			    != 0)
				CSR_WRITE_4(sc, ALC_PM_CFG, pmcfg);
		}

		alc_osc_reset(sc);
		reg = CSR_READ_4(sc, ALC_MISC3);
		reg &= ~MISC3_25M_BY_SW;
		reg |= MISC3_25M_NOTO_INTNL;
		CSR_WRITE_4(sc, ALC_MISC3, reg);
		reg = CSR_READ_4(sc, ALC_MISC);
		reg &= ~MISC_INTNLOSC_OPEN;
		if (AR816X_REV(sc->alc_rev) <= AR816X_REV_A1)
			reg &= ~MISC_ISO_ENB;
		CSR_WRITE_4(sc, ALC_MISC, reg);
		DELAY(20);
	}
	if ((sc->alc_flags & ALC_FLAG_AR816X_FAMILY) != 0 ||
	    sc->alc_ident->deviceid == DEVICEID_ATHEROS_AR8152_B ||
	    sc->alc_ident->deviceid == DEVICEID_ATHEROS_AR8151_V2)
		CSR_WRITE_4(sc, ALC_SERDES_LOCK,
		    CSR_READ_4(sc, ALC_SERDES_LOCK) | SERDES_MAC_CLK_SLOWDOWN |
		    SERDES_PHY_CLK_SLOWDOWN);
}