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
struct alc_softc {int alc_flags; } ;

/* Variables and functions */
 int ALC_FLAG_AR816X_FAMILY ; 
 int /*<<< orphan*/  ALC_PM_CFG ; 
 int CSR_READ_4 (struct alc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct alc_softc*,int /*<<< orphan*/ ,int) ; 
 int PM_CFG_ASPM_L0S_ENB ; 
 int PM_CFG_ASPM_L1_ENB ; 
 int PM_CFG_CLK_SWH_L1 ; 
 int PM_CFG_L1_ENTRY_TIMER_MASK ; 
 int PM_CFG_MAC_ASPM_CHK ; 
 int PM_CFG_SERDES_BUDS_RX_L1_ENB ; 
 int PM_CFG_SERDES_L1_ENB ; 
 int PM_CFG_SERDES_PD_EX_L1 ; 
 int PM_CFG_SERDES_PLL_L1_ENB ; 

__attribute__((used)) static void
alc_disable_l0s_l1(struct alc_softc *sc)
{
	uint32_t pmcfg;

	if ((sc->alc_flags & ALC_FLAG_AR816X_FAMILY) == 0) {
		/* Another magic from vendor. */
		pmcfg = CSR_READ_4(sc, ALC_PM_CFG);
		pmcfg &= ~(PM_CFG_L1_ENTRY_TIMER_MASK | PM_CFG_CLK_SWH_L1 |
		    PM_CFG_ASPM_L0S_ENB | PM_CFG_ASPM_L1_ENB |
		    PM_CFG_MAC_ASPM_CHK | PM_CFG_SERDES_PD_EX_L1);
		pmcfg |= PM_CFG_SERDES_BUDS_RX_L1_ENB |
		    PM_CFG_SERDES_PLL_L1_ENB | PM_CFG_SERDES_L1_ENB;
		CSR_WRITE_4(sc, ALC_PM_CFG, pmcfg);
	}
}