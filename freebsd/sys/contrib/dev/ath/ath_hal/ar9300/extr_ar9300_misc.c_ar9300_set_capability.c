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
struct ath_hal_9300 {int ah_misc_mode; int rx_buf_size; int /*<<< orphan*/  ah_sta_id1_defaults; } ;
struct TYPE_4__ {int ath_hal_desc_tpc; } ;
struct ath_hal {TYPE_1__ ah_config; } ;
struct TYPE_5__ {int /*<<< orphan*/  halTsfAddSupport; int /*<<< orphan*/  halTkipMicTxRxKeySupport; } ;
struct TYPE_6__ {int ah_diagreg; TYPE_2__ ah_caps; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;
typedef  int HAL_CAPABILITY_TYPE ;
typedef  TYPE_2__ HAL_CAPABILITIES ;
typedef  int /*<<< orphan*/  HAL_BOOL ;
typedef  int /*<<< orphan*/  HAL_ANI_CMD ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_FALSE ; 
 TYPE_3__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_DATABUF ; 
 int AR_DATABUF_MASK ; 
 int /*<<< orphan*/  AR_DIAG_SW ; 
 int AR_PCU_MIC_NEW_LOC_ENA ; 
 int /*<<< orphan*/  AR_PCU_MISC ; 
 int AR_PCU_TXOP_TBTT_LIMIT_ENA ; 
 int AR_PCU_TX_ADD_TSF ; 
 int /*<<< orphan*/  AR_PHY_CCK_DETECT ; 
 int AR_PHY_CCK_DETECT_BB_ENABLE_ANT_FAST_DIV ; 
 int /*<<< orphan*/  AR_STA_ID1_CRPT_MIC_ENABLE ; 
 int /*<<< orphan*/  AR_STA_ID1_MCAST_KSRCH ; 
#define  HAL_ANI_CCK_WEAK_SIGNAL_THR 145 
#define  HAL_ANI_FIRSTEP_LEVEL 144 
#define  HAL_ANI_MODE 143 
#define  HAL_ANI_NOISE_IMMUNITY_LEVEL 142 
#define  HAL_ANI_OFDM_WEAK_SIGNAL_DETECTION 141 
#define  HAL_ANI_PRESENT 140 
#define  HAL_ANI_SPUR_IMMUNITY_LEVEL 139 
#define  HAL_CAP_DIAG 138 
#define  HAL_CAP_DIVERSITY 137 
#define  HAL_CAP_ENFORCE_TXOP 136 
#define  HAL_CAP_INTMIT 135 
#define  HAL_CAP_MCAST_KEYSRCH 134 
#define  HAL_CAP_RXBUFSIZE 133 
#define  HAL_CAP_TKIP_MIC 132 
#define  HAL_CAP_TKIP_SPLIT 131 
#define  HAL_CAP_TOA_LOCATIONING 130 
#define  HAL_CAP_TPC 129 
#define  HAL_CAP_TSF_ADJUST 128 
 int N (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OS_REG_CLR_BIT (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar9300_ani_control (struct ath_hal*,int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  ar9300_update_loc_ctl_reg (struct ath_hal*,int) ; 
 int /*<<< orphan*/  ath_hal_setcapability (struct ath_hal*,int,int,int,int /*<<< orphan*/ *) ; 

HAL_BOOL
ar9300_set_capability(struct ath_hal *ah, HAL_CAPABILITY_TYPE type,
        u_int32_t capability, u_int32_t setting, HAL_STATUS *status)
{
    struct ath_hal_9300 *ahp = AH9300(ah);
    const HAL_CAPABILITIES *p_cap = &AH_PRIVATE(ah)->ah_caps;
    u_int32_t v;

    switch (type) {
    case HAL_CAP_TKIP_SPLIT:        /* hardware TKIP uses split keys */
        if (! p_cap->halTkipMicTxRxKeySupport)
            return AH_FALSE;

        if (setting)
            ahp->ah_misc_mode &= ~AR_PCU_MIC_NEW_LOC_ENA;
        else
            ahp->ah_misc_mode |= AR_PCU_MIC_NEW_LOC_ENA;

        OS_REG_WRITE(ah, AR_PCU_MISC, ahp->ah_misc_mode);
        return AH_TRUE;

    case HAL_CAP_TKIP_MIC:          /* handle TKIP MIC in hardware */
        if (setting) {
            ahp->ah_sta_id1_defaults |= AR_STA_ID1_CRPT_MIC_ENABLE;
        } else {
            ahp->ah_sta_id1_defaults &= ~AR_STA_ID1_CRPT_MIC_ENABLE;
        }
        return AH_TRUE;
    case HAL_CAP_DIVERSITY:
        v = OS_REG_READ(ah, AR_PHY_CCK_DETECT);
        if (setting) {
            v |= AR_PHY_CCK_DETECT_BB_ENABLE_ANT_FAST_DIV;
        } else {
            v &= ~AR_PHY_CCK_DETECT_BB_ENABLE_ANT_FAST_DIV;
        }
        OS_REG_WRITE(ah, AR_PHY_CCK_DETECT, v);
        return AH_TRUE;
    case HAL_CAP_DIAG:              /* hardware diagnostic support */
        /*
         * NB: could split this up into virtual capabilities,
         *     (e.g. 1 => ACK, 2 => CTS, etc.) but it hardly
         *     seems worth the additional complexity.
         */
#ifdef AH_DEBUG
        AH_PRIVATE(ah)->ah_diagreg = setting;
#else
        AH_PRIVATE(ah)->ah_diagreg = setting & 0x6;     /* ACK+CTS */
#endif
        OS_REG_WRITE(ah, AR_DIAG_SW, AH_PRIVATE(ah)->ah_diagreg);
        return AH_TRUE;
    case HAL_CAP_TPC:
        ah->ah_config.ath_hal_desc_tpc = (setting != 0);
        return AH_TRUE;
    case HAL_CAP_MCAST_KEYSRCH:     /* multicast frame keycache search */
        if (setting) {
            ahp->ah_sta_id1_defaults |= AR_STA_ID1_MCAST_KSRCH;
        } else {
            ahp->ah_sta_id1_defaults &= ~AR_STA_ID1_MCAST_KSRCH;
        }
        return AH_TRUE;
    case HAL_CAP_TSF_ADJUST:        /* hardware has beacon tsf adjust */
        if (p_cap->halTsfAddSupport) {
            if (setting) {
                ahp->ah_misc_mode |= AR_PCU_TX_ADD_TSF;
            } else {
                ahp->ah_misc_mode &= ~AR_PCU_TX_ADD_TSF;
            }
            return AH_TRUE;
        }
        return AH_FALSE;

    /* FreeBSD interrupt mitigation / ANI */
    case HAL_CAP_INTMIT: {          /* interference mitigation */
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
#define N(a)    (sizeof(a) / sizeof(a[0]))
            return capability < N(cmds) ?
                    ar9300_ani_control(ah, cmds[capability], setting) :
                    AH_FALSE;
#undef N
    }

    case HAL_CAP_RXBUFSIZE:         /* set MAC receive buffer size */
        ahp->rx_buf_size = setting & AR_DATABUF_MASK;
        OS_REG_WRITE(ah, AR_DATABUF, ahp->rx_buf_size);
        return AH_TRUE;

    case HAL_CAP_ENFORCE_TXOP:
        if (capability != 1)
            return AH_FALSE;
        if (setting) {
            ahp->ah_misc_mode |= AR_PCU_TXOP_TBTT_LIMIT_ENA;
            OS_REG_SET_BIT(ah, AR_PCU_MISC, AR_PCU_TXOP_TBTT_LIMIT_ENA);
        } else {
            ahp->ah_misc_mode &= ~AR_PCU_TXOP_TBTT_LIMIT_ENA;
            OS_REG_CLR_BIT(ah, AR_PCU_MISC, AR_PCU_TXOP_TBTT_LIMIT_ENA);
        }
        return AH_TRUE;

    case HAL_CAP_TOA_LOCATIONING:
        if (capability == 0)
            return AH_TRUE;
        if (capability == 1) {
            ar9300_update_loc_ctl_reg(ah, setting);
            return AH_TRUE;
        }
        return AH_FALSE;
        /* fall thru... */
    default:
        return ath_hal_setcapability(ah, type, capability, setting, status);
    }
}