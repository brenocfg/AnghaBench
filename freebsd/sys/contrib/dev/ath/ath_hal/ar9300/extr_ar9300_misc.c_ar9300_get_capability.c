#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct ath_hal_9300 {int ah_sta_id1_defaults; int ah_misc_mode; int ah_enterprise_mode; int ah_proc_phy_err; int /*<<< orphan*/  ah_rifs_enabled; } ;
struct TYPE_4__ {int /*<<< orphan*/  ath_hal_crdc_enable; int /*<<< orphan*/  ath_hal_desc_tpc; } ;
struct ath_hal {TYPE_1__ ah_config; } ;
struct ar9300_ani_state {int ofdm_noise_immunity_level; int firstep_level; int spur_immunity_level; int /*<<< orphan*/  ofdm_weak_sig_detect_off; } ;
struct TYPE_5__ {int halNumAntCfg2Ghz; int halNumAntCfg5Ghz; int hal_rx_stbc_support; int hal_tx_stbc_support; int halLDPCSupport; int halTxChainMask; int halRxChainMask; int halApmEnable; int hal_pcie_lcr_offset; int /*<<< orphan*/  hal_pcie_lcr_extsync_en; int /*<<< orphan*/  halTsfAddSupport; int /*<<< orphan*/  halTkipMicTxRxKeySupport; } ;
struct TYPE_6__ {int /*<<< orphan*/  ah_macRev; int /*<<< orphan*/  ah_macVersion; TYPE_2__ ah_caps; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;
typedef  int HAL_CAPABILITY_TYPE ;
typedef  TYPE_2__ HAL_CAPABILITIES ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int AH_ENT_RTSCTS_DELIM_WAR ; 
 struct ar9300_ani_state* AH_NULL ; 
 TYPE_3__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int AR_ENT_OTP_MIN_PKT_SIZE_DISABLE ; 
 int AR_PCU_MIC_NEW_LOC_ENA ; 
 int AR_PCU_TXOP_TBTT_LIMIT_ENA ; 
 int AR_PCU_TX_ADD_TSF ; 
 int /*<<< orphan*/  AR_PHY_CCK_DETECT ; 
 int AR_PHY_CCK_DETECT_BB_ENABLE_ANT_FAST_DIV ; 
 int /*<<< orphan*/  AR_SREV_APHRODITE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_SREV_AR9580_10 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_SREV_AR9580_10_OR_LATER (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_SREV_HORNET (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_SREV_POSEIDON (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_SREV_REVISION_AR9580_10 ; 
 int /*<<< orphan*/  AR_SREV_SCORPION (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_SREV_VERSION_OSPREY ; 
 int /*<<< orphan*/  AR_SREV_WASP (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_SREV_WASP_10 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_SREV_WASP_11 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_STA_ID1 ; 
 int AR_STA_ID1_ADHOC ; 
 int AR_STA_ID1_CRPT_MIC_ENABLE ; 
 int AR_STA_ID1_MCAST_KSRCH ; 
 int /*<<< orphan*/  EEP_OL_PWRCTRL ; 
#define  HAL_CAP_4ADDR_AGGR 180 
#define  HAL_CAP_ANT_CFG_2GHZ 179 
#define  HAL_CAP_ANT_CFG_5GHZ 178 
#define  HAL_CAP_BB_DFS_HANG 177 
#define  HAL_CAP_BB_PANIC_WATCHDOG 176 
#define  HAL_CAP_BB_RIFS_HANG 175 
#define  HAL_CAP_BB_RX_CLEAR_STUCK_HANG 174 
#define  HAL_CAP_CIPHER 173 
#define  HAL_CAP_CRDC 172 
#define  HAL_CAP_DIVERSITY 171 
#define  HAL_CAP_DS 170 
#define  HAL_CAP_DYNAMIC_SMPS 169 
#define  HAL_CAP_ENABLE_APM 168 
#define  HAL_CAP_ENFORCE_TXOP 167 
#define  HAL_CAP_ENTERPRISE_MODE 166 
#define  HAL_CAP_INTMIT 165 
#define  HAL_CAP_INTMIT_ENABLE 164 
#define  HAL_CAP_INTMIT_FIRSTEP_LEVEL 163 
#define  HAL_CAP_INTMIT_NOISE_IMMUNITY_LEVEL 162 
#define  HAL_CAP_INTMIT_OFDM_WEAK_SIGNAL_LEVEL 161 
#define  HAL_CAP_INTMIT_PRESENT 160 
#define  HAL_CAP_INTMIT_SPUR_IMMUNITY_LEVEL 159 
#define  HAL_CAP_LDPC 158 
#define  HAL_CAP_LDPCWAR 157 
#define  HAL_CAP_MAC_HANG 156 
#define  HAL_CAP_MAX_WEP_TKIP_HT20_TX_RATEKBPS 155 
#define  HAL_CAP_MAX_WEP_TKIP_HT40_TX_RATEKBPS 154 
#define  HAL_CAP_MCAST_KEYSRCH 153 
#define  HAL_CAP_OL_PWRCTRL 152 
#define  HAL_CAP_PCIE_LCR_EXTSYNC_EN 151 
#define  HAL_CAP_PCIE_LCR_OFFSET 150 
#define  HAL_CAP_PHYCOUNTERS 149 
#define  HAL_CAP_PHYDIAG 148 
#define  HAL_CAP_PHYRESTART_CLR_WAR 147 
#define  HAL_CAP_RFSILENT 146 
#define  HAL_CAP_RIFS_RX_ENABLED 145 
#define  HAL_CAP_RX_STBC 144 
#define  HAL_CAP_SMARTANTENNA 143 
#define  HAL_CAP_TKIP_MIC 142 
#define  HAL_CAP_TKIP_SPLIT 141 
#define  HAL_CAP_TOA_LOCATIONING 140 
#define  HAL_CAP_TPC 139 
#define  HAL_CAP_TRAFFIC_FAST_RECOVER 138 
#define  HAL_CAP_TS 137 
#define  HAL_CAP_TSF_ADJUST 136 
#define  HAL_CAP_TX_STBC 135 
#define  HAL_CAP_WME_TKIPMIC 134 
#define  HAL_CIPHER_AES_CCM 133 
#define  HAL_CIPHER_AES_OCB 132 
#define  HAL_CIPHER_CLR 131 
#define  HAL_CIPHER_MIC 130 
#define  HAL_CIPHER_TKIP 129 
#define  HAL_CIPHER_WEP 128 
 int /*<<< orphan*/  HAL_EINVAL ; 
 int /*<<< orphan*/  HAL_ENOTSUPP ; 
 int /*<<< orphan*/  HAL_ENXIO ; 
 int /*<<< orphan*/  HAL_OK ; 
 int HAL_PROCESS_ANI ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 struct ar9300_ani_state* ar9300_ani_get_current_state (struct ath_hal*) ; 
 int /*<<< orphan*/  ar9300_eeprom_get (struct ath_hal_9300*,int /*<<< orphan*/ ) ; 
 int ar9300_read_loc_timer (struct ath_hal*) ; 
 int /*<<< orphan*/  ath_hal_getcapability (struct ath_hal*,int,int,int*) ; 

HAL_STATUS
ar9300_get_capability(struct ath_hal *ah, HAL_CAPABILITY_TYPE type,
    u_int32_t capability, u_int32_t *result)
{
    struct ath_hal_9300 *ahp = AH9300(ah);
    const HAL_CAPABILITIES *p_cap = &AH_PRIVATE(ah)->ah_caps;
    struct ar9300_ani_state *ani;

    switch (type) {
    case HAL_CAP_CIPHER:            /* cipher handled in hardware */
        switch (capability) {
        case HAL_CIPHER_AES_CCM:
        case HAL_CIPHER_AES_OCB:
        case HAL_CIPHER_TKIP:
        case HAL_CIPHER_WEP:
        case HAL_CIPHER_MIC:
        case HAL_CIPHER_CLR:
            return HAL_OK;
        default:
            return HAL_ENOTSUPP;
        }
    case HAL_CAP_TKIP_MIC:          /* handle TKIP MIC in hardware */
        switch (capability) {
        case 0:         /* hardware capability */
            return HAL_OK;
        case 1:
            return (ahp->ah_sta_id1_defaults &
                    AR_STA_ID1_CRPT_MIC_ENABLE) ?  HAL_OK : HAL_ENXIO;
        default:
            return HAL_ENOTSUPP;
        }
    case HAL_CAP_TKIP_SPLIT:        /* hardware TKIP uses split keys */
        switch (capability) {
        case 0: /* hardware capability */
            return p_cap->halTkipMicTxRxKeySupport ? HAL_ENXIO : HAL_OK;
        case 1: /* current setting */
            return (ahp->ah_misc_mode & AR_PCU_MIC_NEW_LOC_ENA) ?
                HAL_ENXIO : HAL_OK;
        default:
            return HAL_ENOTSUPP;
        }
    case HAL_CAP_WME_TKIPMIC:
        /* hardware can do TKIP MIC when WMM is turned on */
        return HAL_OK;
    case HAL_CAP_PHYCOUNTERS:       /* hardware PHY error counters */
        return HAL_OK;
    case HAL_CAP_DIVERSITY:         /* hardware supports fast diversity */
        switch (capability) {
        case 0:                 /* hardware capability */
            return HAL_OK;
        case 1:                 /* current setting */
            return (OS_REG_READ(ah, AR_PHY_CCK_DETECT) &
                            AR_PHY_CCK_DETECT_BB_ENABLE_ANT_FAST_DIV) ?
                            HAL_OK : HAL_ENXIO;
        }
        return HAL_EINVAL;
    case HAL_CAP_TPC:
        switch (capability) {
        case 0:                 /* hardware capability */
            return HAL_OK;
        case 1:
            return ah->ah_config.ath_hal_desc_tpc ?
                               HAL_OK : HAL_ENXIO;
        }
        return HAL_OK;
    case HAL_CAP_PHYDIAG:           /* radar pulse detection capability */
        return HAL_OK;
    case HAL_CAP_MCAST_KEYSRCH:     /* multicast frame keycache search */
        switch (capability) {
        case 0:                 /* hardware capability */
            return HAL_OK;
        case 1:
            if (OS_REG_READ(ah, AR_STA_ID1) & AR_STA_ID1_ADHOC) {
                /*
                 * Owl and Merlin have problems in mcast key search.
                 * Disable this cap. in Ad-hoc mode. see Bug 25776 and
                 * 26802
                 */
                return HAL_ENXIO;
            } else {
                return (ahp->ah_sta_id1_defaults &
                        AR_STA_ID1_MCAST_KSRCH) ? HAL_OK : HAL_ENXIO;
            }
        }
        return HAL_EINVAL;
    case HAL_CAP_TSF_ADJUST:        /* hardware has beacon tsf adjust */
        switch (capability) {
        case 0:                 /* hardware capability */
            return p_cap->halTsfAddSupport ? HAL_OK : HAL_ENOTSUPP;
        case 1:
            return (ahp->ah_misc_mode & AR_PCU_TX_ADD_TSF) ?
                HAL_OK : HAL_ENXIO;
        }
        return HAL_EINVAL;
    case HAL_CAP_RFSILENT:      /* rfsilent support  */
        if (capability == 3) {  /* rfkill interrupt */
            /*
             * XXX: Interrupt-based notification of RF Kill state
             *      changes not working yet. Report that this feature
             *      is not supported so that polling is used instead.
             */
            return (HAL_ENOTSUPP);
        }
        return ath_hal_getcapability(ah, type, capability, result);
    case HAL_CAP_4ADDR_AGGR:
        return HAL_OK;
    case HAL_CAP_BB_RIFS_HANG:
        return HAL_ENOTSUPP;
    case HAL_CAP_BB_DFS_HANG:
        return HAL_ENOTSUPP;
    case HAL_CAP_BB_RX_CLEAR_STUCK_HANG:
        /* Track chips that are known to have BB hangs related
         * to rx_clear stuck low.
         */
        return HAL_ENOTSUPP;
    case HAL_CAP_MAC_HANG:
        /* Track chips that are known to have MAC hangs.
         */
        return HAL_OK;
    case HAL_CAP_RIFS_RX_ENABLED:
        /* Is RIFS RX currently enabled */
        return (ahp->ah_rifs_enabled == AH_TRUE) ?  HAL_OK : HAL_ENOTSUPP;
#if 0
    case HAL_CAP_ANT_CFG_2GHZ:
        *result = p_cap->halNumAntCfg2Ghz;
        return HAL_OK;
    case HAL_CAP_ANT_CFG_5GHZ:
        *result = p_cap->halNumAntCfg5Ghz;
        return HAL_OK;
    case HAL_CAP_RX_STBC:
        *result = p_cap->hal_rx_stbc_support;
        return HAL_OK;
    case HAL_CAP_TX_STBC:
        *result = p_cap->hal_tx_stbc_support;
        return HAL_OK;
#endif
    case HAL_CAP_LDPC:
        *result = p_cap->halLDPCSupport;
        return HAL_OK;
    case HAL_CAP_DYNAMIC_SMPS:
        return HAL_OK;
    case HAL_CAP_DS:
        return (AR_SREV_HORNET(ah) || AR_SREV_POSEIDON(ah) || AR_SREV_APHRODITE(ah) ||
                (p_cap->halTxChainMask & 0x3) != 0x3 ||
                (p_cap->halRxChainMask & 0x3) != 0x3) ?
            HAL_ENOTSUPP : HAL_OK;
    case HAL_CAP_TS:
        return (AR_SREV_HORNET(ah) || AR_SREV_POSEIDON(ah) || AR_SREV_APHRODITE(ah) ||
                (p_cap->halTxChainMask & 0x7) != 0x7 ||
                (p_cap->halRxChainMask & 0x7) != 0x7) ?
            HAL_ENOTSUPP : HAL_OK;
    case HAL_CAP_OL_PWRCTRL:
        return (ar9300_eeprom_get(ahp, EEP_OL_PWRCTRL)) ?
            HAL_OK : HAL_ENOTSUPP;
    case HAL_CAP_CRDC:
#if ATH_SUPPORT_CRDC
        return (AR_SREV_WASP(ah) && 
                ah->ah_config.ath_hal_crdc_enable) ? 
                    HAL_OK : HAL_ENOTSUPP;
#else
        return HAL_ENOTSUPP;
#endif
#if 0
    case HAL_CAP_MAX_WEP_TKIP_HT20_TX_RATEKBPS:
        *result = (u_int32_t)(-1);
        return HAL_OK;
    case HAL_CAP_MAX_WEP_TKIP_HT40_TX_RATEKBPS:
        *result = (u_int32_t)(-1);
        return HAL_OK;
#endif
    case HAL_CAP_BB_PANIC_WATCHDOG:
        return HAL_OK;
    case HAL_CAP_PHYRESTART_CLR_WAR:
        if ((AH_PRIVATE((ah))->ah_macVersion == AR_SREV_VERSION_OSPREY) &&
            (AH_PRIVATE((ah))->ah_macRev < AR_SREV_REVISION_AR9580_10)) 
        {
            return HAL_OK;
        }
        else
        {
            return HAL_ENOTSUPP;
        }
    case HAL_CAP_ENTERPRISE_MODE:
        *result = ahp->ah_enterprise_mode >> 16;
        /*
         * WAR for EV 77658 - Add delimiters to first sub-frame when using
         * RTS/CTS with aggregation and non-enterprise Osprey.
         *
         * Bug fixed in AR9580/Peacock, Wasp1.1 and later
         */
        if ((ahp->ah_enterprise_mode & AR_ENT_OTP_MIN_PKT_SIZE_DISABLE) &&
                !AR_SREV_AR9580_10_OR_LATER(ah) && (!AR_SREV_WASP(ah) ||
                AR_SREV_WASP_10(ah))) {
            *result |= AH_ENT_RTSCTS_DELIM_WAR;
        }
        return HAL_OK;
    case HAL_CAP_LDPCWAR:
        /* WAR for RIFS+LDPC issue is required for all chips currently 
         * supported by ar9300 HAL.
         */
        return HAL_OK;    
    case HAL_CAP_ENABLE_APM:
        *result = p_cap->halApmEnable;
        return HAL_OK;
    case HAL_CAP_PCIE_LCR_EXTSYNC_EN:
        return (p_cap->hal_pcie_lcr_extsync_en == AH_TRUE) ? HAL_OK : HAL_ENOTSUPP;
    case HAL_CAP_PCIE_LCR_OFFSET:
        *result = p_cap->hal_pcie_lcr_offset;
        return HAL_OK;
    case HAL_CAP_SMARTANTENNA:
        /* FIXME A request is pending with h/w team to add feature bit in
         * caldata to detect if board has smart antenna or not, once added
         * we need to fix his piece of code to read and return value without
         * any compile flags
         */
#if UMAC_SUPPORT_SMARTANTENNA
        /* enable smart antenna for  Peacock, Wasp and scorpion 
           for future chips need to modify */
        if (AR_SREV_AR9580_10(ah) || (AR_SREV_WASP(ah)) || AR_SREV_SCORPION(ah)) {
            return HAL_OK;
        } else {
            return HAL_ENOTSUPP;
        }
#else
        return HAL_ENOTSUPP;
#endif

#ifdef ATH_TRAFFIC_FAST_RECOVER
    case HAL_CAP_TRAFFIC_FAST_RECOVER:
        if (AR_SREV_HORNET(ah) || AR_SREV_POSEIDON(ah) || AR_SREV_WASP_11(ah)) {
            return HAL_OK;
        } else {
            return HAL_ENOTSUPP;
        }
#endif

    /* FreeBSD ANI */
    case HAL_CAP_INTMIT:            /* interference mitigation */
            switch (capability) {
            case HAL_CAP_INTMIT_PRESENT:            /* hardware capability */
                    return HAL_OK;
            case HAL_CAP_INTMIT_ENABLE:
                    return (ahp->ah_proc_phy_err & HAL_PROCESS_ANI) ?
                            HAL_OK : HAL_ENXIO;
            case HAL_CAP_INTMIT_NOISE_IMMUNITY_LEVEL:
            case HAL_CAP_INTMIT_OFDM_WEAK_SIGNAL_LEVEL:
//            case HAL_CAP_INTMIT_CCK_WEAK_SIGNAL_THR:
            case HAL_CAP_INTMIT_FIRSTEP_LEVEL:
            case HAL_CAP_INTMIT_SPUR_IMMUNITY_LEVEL:
                    ani = ar9300_ani_get_current_state(ah);
                    if (ani == AH_NULL)
                            return HAL_ENXIO;
                    switch (capability) {
                    /* XXX AR9300 HAL has OFDM/CCK noise immunity level params? */
                    case 2: *result = ani->ofdm_noise_immunity_level; break;
                    case 3: *result = !ani->ofdm_weak_sig_detect_off; break;
 //                   case 4: *result = ani->cck_weak_sig_threshold; break;
                    case 5: *result = ani->firstep_level; break;
                    case 6: *result = ani->spur_immunity_level; break;
                    }
                    return HAL_OK;
            }
            return HAL_EINVAL;
    case HAL_CAP_ENFORCE_TXOP:
        if (capability == 0)
            return (HAL_OK);
        if (capability != 1)
            return (HAL_ENOTSUPP);
        (*result) = !! (ahp->ah_misc_mode & AR_PCU_TXOP_TBTT_LIMIT_ENA);
        return (HAL_OK);
    case HAL_CAP_TOA_LOCATIONING:
        if (capability == 0)
            return HAL_OK;
        if (capability == 2) {
            *result = ar9300_read_loc_timer(ah);
            return (HAL_OK);
        }
        return HAL_ENOTSUPP;
    default:
        return ath_hal_getcapability(ah, type, capability, result);
    }
}