#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct ath_hal_5212 {int ah_miscMode; int ah_diversity; int ah_tpcEnabled; int ah_txPowerIndexOffset; int ah_macTPC; int /*<<< orphan*/  (* ah_aniControl ) (struct ath_hal*,int /*<<< orphan*/  const,int) ;int /*<<< orphan*/  ah_staId1Defaults; int /*<<< orphan*/  ah_phyPowerOn; } ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  halTsfAddSupport; int /*<<< orphan*/  halTkipMicTxRxKeySupport; } ;
struct TYPE_4__ {int ah_diagreg; TYPE_1__ ah_caps; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;
typedef  int HAL_CAPABILITY_TYPE ;
typedef  TYPE_1__ HAL_CAPABILITIES ;
typedef  int /*<<< orphan*/  HAL_BOOL ;
typedef  int /*<<< orphan*/  HAL_ANI_CMD ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_FALSE ; 
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_DIAG_SW ; 
 int /*<<< orphan*/  AR_MISC_MODE ; 
 int AR_MISC_MODE_MIC_NEW_LOC_ENABLE ; 
 int AR_MISC_MODE_TX_ADD_TSF ; 
 int /*<<< orphan*/  AR_PHY_CCK_DETECT ; 
 int AR_PHY_CCK_DETECT_BB_ENABLE_ANT_FAST_DIV ; 
 int /*<<< orphan*/  AR_PHY_RESTART ; 
 int AR_PHY_RESTART_DIV_GC ; 
 int /*<<< orphan*/  AR_STA_ID1_CRPT_MIC_ENABLE ; 
 int /*<<< orphan*/  AR_STA_ID1_MCAST_KSRCH ; 
 int /*<<< orphan*/  AR_TPC ; 
 int AR_TPC_ACK ; 
 int AR_TPC_CTS ; 
#define  HAL_ANI_CCK_WEAK_SIGNAL_THR 145 
#define  HAL_ANI_FIRSTEP_LEVEL 144 
#define  HAL_ANI_MODE 143 
#define  HAL_ANI_NOISE_IMMUNITY_LEVEL 142 
#define  HAL_ANI_OFDM_WEAK_SIGNAL_DETECTION 141 
#define  HAL_ANI_PRESENT 140 
#define  HAL_ANI_SPUR_IMMUNITY_LEVEL 139 
#define  HAL_CAP_DIAG 138 
#define  HAL_CAP_DIVERSITY 137 
#define  HAL_CAP_INTMIT 136 
#define  HAL_CAP_MCAST_KEYSRCH 135 
#define  HAL_CAP_STRONG_DIV 134 
#define  HAL_CAP_TKIP_MIC 133 
#define  HAL_CAP_TKIP_SPLIT 132 
#define  HAL_CAP_TPC 131 
#define  HAL_CAP_TPC_ACK 130 
#define  HAL_CAP_TPC_CTS 129 
#define  HAL_CAP_TSF_ADJUST 128 
 int MS (int,int) ; 
 int N (int /*<<< orphan*/  const*) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int SM (int,int) ; 
 int /*<<< orphan*/  ath_hal_setcapability (struct ath_hal*,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ath_hal*,int /*<<< orphan*/  const,int) ; 

HAL_BOOL
ar5212SetCapability(struct ath_hal *ah, HAL_CAPABILITY_TYPE type,
	uint32_t capability, uint32_t setting, HAL_STATUS *status)
{
#define	N(a)	(sizeof(a)/sizeof(a[0]))
	struct ath_hal_5212 *ahp = AH5212(ah);
	const HAL_CAPABILITIES *pCap = &AH_PRIVATE(ah)->ah_caps;
	uint32_t v;

	switch (type) {
	case HAL_CAP_TKIP_MIC:		/* handle TKIP MIC in hardware */
		if (setting)
			ahp->ah_staId1Defaults |= AR_STA_ID1_CRPT_MIC_ENABLE;
		else
			ahp->ah_staId1Defaults &= ~AR_STA_ID1_CRPT_MIC_ENABLE;
		return AH_TRUE;
	case HAL_CAP_TKIP_SPLIT:	/* hardware TKIP uses split keys */
		if (!pCap->halTkipMicTxRxKeySupport)
			return AH_FALSE;
		/* NB: true =>'s use split key cache layout */
		if (setting)
			ahp->ah_miscMode &= ~AR_MISC_MODE_MIC_NEW_LOC_ENABLE;
		else
			ahp->ah_miscMode |= AR_MISC_MODE_MIC_NEW_LOC_ENABLE;
		/* NB: write here so keys can be setup w/o a reset */
		OS_REG_WRITE(ah, AR_MISC_MODE, OS_REG_READ(ah, AR_MISC_MODE) | ahp->ah_miscMode);
		return AH_TRUE;
	case HAL_CAP_DIVERSITY:
		switch (capability) {
		case 0:
			return AH_FALSE;
		case 1:	/* setting */
			if (ahp->ah_phyPowerOn) {
				if (capability == HAL_CAP_STRONG_DIV) {
					v = OS_REG_READ(ah, AR_PHY_CCK_DETECT);
					if (setting)
						v |= AR_PHY_CCK_DETECT_BB_ENABLE_ANT_FAST_DIV;
					else
						v &= ~AR_PHY_CCK_DETECT_BB_ENABLE_ANT_FAST_DIV;
					OS_REG_WRITE(ah, AR_PHY_CCK_DETECT, v);
				}
			}
			ahp->ah_diversity = (setting != 0);
			return AH_TRUE;

		case HAL_CAP_STRONG_DIV:
			if (! ahp->ah_phyPowerOn)
				return AH_FALSE;
			v = OS_REG_READ(ah, AR_PHY_RESTART);
			v &= ~AR_PHY_RESTART_DIV_GC;
			v |= SM(setting, AR_PHY_RESTART_DIV_GC);
			OS_REG_WRITE(ah, AR_PHY_RESTART, v);
			return AH_TRUE;
		default:
			return AH_FALSE;
		}
	case HAL_CAP_DIAG:		/* hardware diagnostic support */
		/*
		 * NB: could split this up into virtual capabilities,
		 *     (e.g. 1 => ACK, 2 => CTS, etc.) but it hardly
		 *     seems worth the additional complexity.
		 */
		AH_PRIVATE(ah)->ah_diagreg = setting;
		OS_REG_WRITE(ah, AR_DIAG_SW, AH_PRIVATE(ah)->ah_diagreg);
		return AH_TRUE;
	case HAL_CAP_TPC:
		ahp->ah_tpcEnabled = (setting != 0);
		return AH_TRUE;
	case HAL_CAP_MCAST_KEYSRCH:	/* multicast frame keycache search */
		if (setting)
			ahp->ah_staId1Defaults |= AR_STA_ID1_MCAST_KSRCH;
		else
			ahp->ah_staId1Defaults &= ~AR_STA_ID1_MCAST_KSRCH;
		return AH_TRUE;
	case HAL_CAP_TPC_ACK:
	case HAL_CAP_TPC_CTS:
		setting += ahp->ah_txPowerIndexOffset;
		if (setting > 63)
			setting = 63;
		if (type == HAL_CAP_TPC_ACK) {
			ahp->ah_macTPC &= AR_TPC_ACK;
			ahp->ah_macTPC |= MS(setting, AR_TPC_ACK);
		} else {
			ahp->ah_macTPC &= AR_TPC_CTS;
			ahp->ah_macTPC |= MS(setting, AR_TPC_CTS);
		}
		OS_REG_WRITE(ah, AR_TPC, ahp->ah_macTPC);
		return AH_TRUE;
	case HAL_CAP_INTMIT: {		/* interference mitigation */
		/* This maps the public ANI commands to the internal ANI commands */
		/* Private: HAL_ANI_CMD; Public: HAL_CAP_INTMIT_CMD */
		static const HAL_ANI_CMD cmds[] = {
			HAL_ANI_PRESENT,
			HAL_ANI_MODE,
			HAL_ANI_NOISE_IMMUNITY_LEVEL,
			HAL_ANI_OFDM_WEAK_SIGNAL_DETECTION,
			HAL_ANI_CCK_WEAK_SIGNAL_THR,
			HAL_ANI_FIRSTEP_LEVEL,
			HAL_ANI_SPUR_IMMUNITY_LEVEL,
		};
		return capability < N(cmds) ?
			AH5212(ah)->ah_aniControl(ah, cmds[capability], setting) :
			AH_FALSE;
	}
	case HAL_CAP_TSF_ADJUST:	/* hardware has beacon tsf adjust */
		if (pCap->halTsfAddSupport) {
			if (setting)
				ahp->ah_miscMode |= AR_MISC_MODE_TX_ADD_TSF;
			else
				ahp->ah_miscMode &= ~AR_MISC_MODE_TX_ADD_TSF;
			return AH_TRUE;
		}
		/* fall thru... */
	default:
		return ath_hal_setcapability(ah, type, capability,
				setting, status);
	}
#undef N
}