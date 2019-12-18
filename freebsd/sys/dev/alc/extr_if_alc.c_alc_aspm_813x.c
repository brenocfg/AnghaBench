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
typedef  int /*<<< orphan*/  uint16_t ;
struct alc_softc {int alc_flags; scalar_t__ alc_rev; TYPE_1__* alc_ident; scalar_t__ alc_expcap; } ;
struct TYPE_2__ {int deviceid; } ;

/* Variables and functions */
 int ALC_FLAG_APS ; 
 int ALC_FLAG_L0S ; 
 int ALC_FLAG_L1S ; 
 int ALC_FLAG_LINK ; 
 int ALC_FLAG_PCIE ; 
 int /*<<< orphan*/  ALC_PM_CFG ; 
 scalar_t__ ATHEROS_AR8152_B_V10 ; 
 int /*<<< orphan*/  CSR_READ_2 (struct alc_softc*,scalar_t__) ; 
 int CSR_READ_4 (struct alc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct alc_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct alc_softc*,int /*<<< orphan*/ ,int) ; 
#define  DEVICEID_ATHEROS_AR8151_V2 130 
#define  DEVICEID_ATHEROS_AR8152_B 129 
#define  DEVICEID_ATHEROS_AR8152_B2 128 
 int IFM_1000_T ; 
 int IFM_100_TX ; 
 int /*<<< orphan*/  PCIEM_LINK_CTL_EXTENDED_SYNC ; 
 scalar_t__ PCIER_LINK_CTL ; 
 int PM_CFG_ASPM_L0S_ENB ; 
 int PM_CFG_ASPM_L1_ENB ; 
 int PM_CFG_CLK_SWH_L1 ; 
 int PM_CFG_EN_BUFS_RX_L0S ; 
 int PM_CFG_HOTRST ; 
 int PM_CFG_L1_ENTRY_TIMER_DEFAULT ; 
 int PM_CFG_L1_ENTRY_TIMER_MASK ; 
 int PM_CFG_L1_ENTRY_TIMER_SHIFT ; 
 int PM_CFG_LCKDET_TIMER_DEFAULT ; 
 int PM_CFG_LCKDET_TIMER_MASK ; 
 int PM_CFG_LCKDET_TIMER_SHIFT ; 
 int PM_CFG_MAC_ASPM_CHK ; 
 int PM_CFG_PCIE_RECV ; 
 int PM_CFG_PM_REQ_TIMER_DEFAULT ; 
 int PM_CFG_PM_REQ_TIMER_MASK ; 
 int PM_CFG_PM_REQ_TIMER_SHIFT ; 
 int PM_CFG_SA_DLY_ENB ; 
 int PM_CFG_SERDES_BUDS_RX_L1_ENB ; 
 int PM_CFG_SERDES_L1_ENB ; 
 int PM_CFG_SERDES_PD_EX_L1 ; 
 int PM_CFG_SERDES_PLL_L1_ENB ; 

__attribute__((used)) static void
alc_aspm_813x(struct alc_softc *sc, int media)
{
	uint32_t pmcfg;
	uint16_t linkcfg;

	if ((sc->alc_flags & ALC_FLAG_LINK) == 0)
		return;

	pmcfg = CSR_READ_4(sc, ALC_PM_CFG);
	if ((sc->alc_flags & (ALC_FLAG_APS | ALC_FLAG_PCIE)) ==
	    (ALC_FLAG_APS | ALC_FLAG_PCIE))
		linkcfg = CSR_READ_2(sc, sc->alc_expcap +
		    PCIER_LINK_CTL);
	else
		linkcfg = 0;
	pmcfg &= ~PM_CFG_SERDES_PD_EX_L1;
	pmcfg &= ~(PM_CFG_L1_ENTRY_TIMER_MASK | PM_CFG_LCKDET_TIMER_MASK);
	pmcfg |= PM_CFG_MAC_ASPM_CHK;
	pmcfg |= (PM_CFG_LCKDET_TIMER_DEFAULT << PM_CFG_LCKDET_TIMER_SHIFT);
	pmcfg &= ~(PM_CFG_ASPM_L1_ENB | PM_CFG_ASPM_L0S_ENB);

	if ((sc->alc_flags & ALC_FLAG_APS) != 0) {
		/* Disable extended sync except AR8152 B v1.0 */
		linkcfg &= ~PCIEM_LINK_CTL_EXTENDED_SYNC;
		if (sc->alc_ident->deviceid == DEVICEID_ATHEROS_AR8152_B &&
		    sc->alc_rev == ATHEROS_AR8152_B_V10)
			linkcfg |= PCIEM_LINK_CTL_EXTENDED_SYNC;
		CSR_WRITE_2(sc, sc->alc_expcap + PCIER_LINK_CTL,
		    linkcfg);
		pmcfg &= ~(PM_CFG_EN_BUFS_RX_L0S | PM_CFG_SA_DLY_ENB |
		    PM_CFG_HOTRST);
		pmcfg |= (PM_CFG_L1_ENTRY_TIMER_DEFAULT <<
		    PM_CFG_L1_ENTRY_TIMER_SHIFT);
		pmcfg &= ~PM_CFG_PM_REQ_TIMER_MASK;
		pmcfg |= (PM_CFG_PM_REQ_TIMER_DEFAULT <<
		    PM_CFG_PM_REQ_TIMER_SHIFT);
		pmcfg |= PM_CFG_SERDES_PD_EX_L1 | PM_CFG_PCIE_RECV;
	}

	if ((sc->alc_flags & ALC_FLAG_LINK) != 0) {
		if ((sc->alc_flags & ALC_FLAG_L0S) != 0)
			pmcfg |= PM_CFG_ASPM_L0S_ENB;
		if ((sc->alc_flags & ALC_FLAG_L1S) != 0)
			pmcfg |= PM_CFG_ASPM_L1_ENB;
		if ((sc->alc_flags & ALC_FLAG_APS) != 0) {
			if (sc->alc_ident->deviceid ==
			    DEVICEID_ATHEROS_AR8152_B)
				pmcfg &= ~PM_CFG_ASPM_L0S_ENB;
			pmcfg &= ~(PM_CFG_SERDES_L1_ENB |
			    PM_CFG_SERDES_PLL_L1_ENB |
			    PM_CFG_SERDES_BUDS_RX_L1_ENB);
			pmcfg |= PM_CFG_CLK_SWH_L1;
			if (media == IFM_100_TX || media == IFM_1000_T) {
				pmcfg &= ~PM_CFG_L1_ENTRY_TIMER_MASK;
				switch (sc->alc_ident->deviceid) {
				case DEVICEID_ATHEROS_AR8152_B:
					pmcfg |= (7 <<
					    PM_CFG_L1_ENTRY_TIMER_SHIFT);
					break;
				case DEVICEID_ATHEROS_AR8152_B2:
				case DEVICEID_ATHEROS_AR8151_V2:
					pmcfg |= (4 <<
					    PM_CFG_L1_ENTRY_TIMER_SHIFT);
					break;
				default:
					pmcfg |= (15 <<
					    PM_CFG_L1_ENTRY_TIMER_SHIFT);
					break;
				}
			}
		} else {
			pmcfg |= PM_CFG_SERDES_L1_ENB |
			    PM_CFG_SERDES_PLL_L1_ENB |
			    PM_CFG_SERDES_BUDS_RX_L1_ENB;
			pmcfg &= ~(PM_CFG_CLK_SWH_L1 |
			    PM_CFG_ASPM_L1_ENB | PM_CFG_ASPM_L0S_ENB);
		}
	} else {
		pmcfg &= ~(PM_CFG_SERDES_BUDS_RX_L1_ENB | PM_CFG_SERDES_L1_ENB |
		    PM_CFG_SERDES_PLL_L1_ENB);
		pmcfg |= PM_CFG_CLK_SWH_L1;
		if ((sc->alc_flags & ALC_FLAG_L1S) != 0)
			pmcfg |= PM_CFG_ASPM_L1_ENB;
	}
	CSR_WRITE_4(sc, ALC_PM_CFG, pmcfg);
}