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
struct alc_softc {int alc_rev; int alc_flags; TYPE_1__* alc_ifp; } ;
struct TYPE_2__ {int if_drv_flags; } ;

/* Variables and functions */
 int ALC_FLAG_LINK ; 
 int /*<<< orphan*/  ALC_PM_CFG ; 
 scalar_t__ AR816X_REV (int) ; 
 scalar_t__ AR816X_REV_A1 ; 
 int CSR_READ_4 (struct alc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct alc_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_DRV_RUNNING ; 
 int PM_CFG_ASPM_L0S_ENB ; 
 int PM_CFG_ASPM_L1_ENB ; 
 int PM_CFG_CLK_SWH_L1 ; 
 int PM_CFG_HOTRST ; 
 int PM_CFG_L1_ENTRY_TIMER_816X_DEFAULT ; 
 int PM_CFG_L1_ENTRY_TIMER_816X_MASK ; 
 int PM_CFG_LCKDET_TIMER_DEFAULT ; 
 int PM_CFG_LCKDET_TIMER_MASK ; 
 int PM_CFG_MAC_ASPM_CHK ; 
 int PM_CFG_PCIE_RECV ; 
 int PM_CFG_PM_REQ_TIMER_816X_DEFAULT ; 
 int PM_CFG_PM_REQ_TIMER_MASK ; 
 int PM_CFG_RX_L1_AFTER_L0S ; 
 int PM_CFG_SA_DLY_ENB ; 
 int PM_CFG_SERDES_BUDS_RX_L1_ENB ; 
 int PM_CFG_SERDES_L1_ENB ; 
 int PM_CFG_SERDES_PD_EX_L1 ; 
 int PM_CFG_SERDES_PLL_L1_ENB ; 
 int PM_CFG_TX_L1_AFTER_L0S ; 

__attribute__((used)) static void
alc_aspm_816x(struct alc_softc *sc, int init)
{
	uint32_t pmcfg;

	pmcfg = CSR_READ_4(sc, ALC_PM_CFG);
	pmcfg &= ~PM_CFG_L1_ENTRY_TIMER_816X_MASK;
	pmcfg |= PM_CFG_L1_ENTRY_TIMER_816X_DEFAULT;
	pmcfg &= ~PM_CFG_PM_REQ_TIMER_MASK;
	pmcfg |= PM_CFG_PM_REQ_TIMER_816X_DEFAULT;
	pmcfg &= ~PM_CFG_LCKDET_TIMER_MASK;
	pmcfg |= PM_CFG_LCKDET_TIMER_DEFAULT;
	pmcfg |= PM_CFG_SERDES_PD_EX_L1 | PM_CFG_CLK_SWH_L1 | PM_CFG_PCIE_RECV;
	pmcfg &= ~(PM_CFG_RX_L1_AFTER_L0S | PM_CFG_TX_L1_AFTER_L0S |
	    PM_CFG_ASPM_L1_ENB | PM_CFG_ASPM_L0S_ENB |
	    PM_CFG_SERDES_L1_ENB | PM_CFG_SERDES_PLL_L1_ENB |
	    PM_CFG_SERDES_BUDS_RX_L1_ENB | PM_CFG_SA_DLY_ENB |
	    PM_CFG_MAC_ASPM_CHK | PM_CFG_HOTRST);
	if (AR816X_REV(sc->alc_rev) <= AR816X_REV_A1 &&
	    (sc->alc_rev & 0x01) != 0)
		pmcfg |= PM_CFG_SERDES_L1_ENB | PM_CFG_SERDES_PLL_L1_ENB;
	if ((sc->alc_flags & ALC_FLAG_LINK) != 0) {
		/* Link up, enable both L0s, L1s. */
		pmcfg |= PM_CFG_ASPM_L0S_ENB | PM_CFG_ASPM_L1_ENB |
		    PM_CFG_MAC_ASPM_CHK;
	} else {
		if (init != 0)
			pmcfg |= PM_CFG_ASPM_L0S_ENB | PM_CFG_ASPM_L1_ENB |
			    PM_CFG_MAC_ASPM_CHK;
		else if ((sc->alc_ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
			pmcfg |= PM_CFG_ASPM_L1_ENB | PM_CFG_MAC_ASPM_CHK;
	}
	CSR_WRITE_4(sc, ALC_PM_CFG, pmcfg);
}