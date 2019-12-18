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
typedef  int u_int32_t ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {scalar_t__ ah_ext_prot_spacing; } ;
typedef  int /*<<< orphan*/  HAL_HT_MACMODE ;

/* Variables and functions */
 int /*<<< orphan*/  AR_CST ; 
 int AR_CST_TIMEOUT_LIMIT_S ; 
 int /*<<< orphan*/  AR_GTXTO ; 
 int AR_GTXTO_TIMEOUT_LIMIT_S ; 
 int /*<<< orphan*/  AR_PHY_FRAME_CTL ; 
 int /*<<< orphan*/  AR_PHY_FRAME_CTL_CF_OVERLAP_WINDOW ; 
 int AR_PHY_GC_DYN2040_EN ; 
 int AR_PHY_GC_DYN2040_EXT_CH ; 
 int AR_PHY_GC_DYN2040_PRI_CH ; 
 int AR_PHY_GC_ENABLE_DAC_FIFO ; 
 int AR_PHY_GC_GF_DETECT_EN ; 
 int AR_PHY_GC_HT_EN ; 
 int AR_PHY_GC_SHORT_GI_40 ; 
 int AR_PHY_GC_SINGLE_HT_LTF1 ; 
 int /*<<< orphan*/  AR_PHY_GEN_CTRL ; 
 int /*<<< orphan*/  AR_PHY_MODE ; 
 int AR_PHY_MS_HALF_RATE ; 
 int AR_PHY_MS_QUARTER_RATE ; 
 scalar_t__ HAL_HT_EXTPROTSPACING_25 ; 
 scalar_t__ IEEE80211_IS_CHAN_HALF (struct ieee80211_channel*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (struct ieee80211_channel*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40U (struct ieee80211_channel*) ; 
 scalar_t__ IEEE80211_IS_CHAN_QUARTER (struct ieee80211_channel*) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ahp ; 
 int /*<<< orphan*/  ar9300_set_11n_mac2040 (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_set_ifs_timing (struct ath_hal*,struct ieee80211_channel*) ; 

__attribute__((used)) static void
ar9300_set_11n_regs(struct ath_hal *ah, struct ieee80211_channel *chan,
    HAL_HT_MACMODE macmode)
{
    u_int32_t phymode;
//    struct ath_hal_9300 *ahp = AH9300(ah);
    u_int32_t enable_dac_fifo;

    /* XXX */
    enable_dac_fifo =
        OS_REG_READ(ah, AR_PHY_GEN_CTRL) & AR_PHY_GC_ENABLE_DAC_FIFO;

    /* Enable 11n HT, 20 MHz */
    phymode =
        AR_PHY_GC_HT_EN | AR_PHY_GC_SINGLE_HT_LTF1 | AR_PHY_GC_SHORT_GI_40
        | enable_dac_fifo;
    /* Configure baseband for dynamic 20/40 operation */
    if (IEEE80211_IS_CHAN_HT40(chan)) {
        phymode |= AR_PHY_GC_DYN2040_EN;
        /* Configure control (primary) channel at +-10MHz */
        if (IEEE80211_IS_CHAN_HT40U(chan)) {
            phymode |= AR_PHY_GC_DYN2040_PRI_CH;
        }

#if 0
        /* Configure 20/25 spacing */
        if (ahp->ah_ext_prot_spacing == HAL_HT_EXTPROTSPACING_25) {
            phymode |= AR_PHY_GC_DYN2040_EXT_CH;
        }
#endif
    }

    /* make sure we preserve INI settings */
    phymode |= OS_REG_READ(ah, AR_PHY_GEN_CTRL);

    /* EV 62881/64991 - turn off Green Field detection for Maverick STA beta */
    phymode &= ~AR_PHY_GC_GF_DETECT_EN;

    OS_REG_WRITE(ah, AR_PHY_GEN_CTRL, phymode);

    /* Set IFS timing for half/quarter rates */
    if (IEEE80211_IS_CHAN_HALF(chan) || IEEE80211_IS_CHAN_QUARTER(chan)) {
        u_int32_t modeselect = OS_REG_READ(ah, AR_PHY_MODE);

        if (IEEE80211_IS_CHAN_HALF(chan)) {
            modeselect |= AR_PHY_MS_HALF_RATE;
        } else if (IEEE80211_IS_CHAN_QUARTER(chan)) {
            modeselect |= AR_PHY_MS_QUARTER_RATE;
        }
        OS_REG_WRITE(ah, AR_PHY_MODE, modeselect);

        ar9300_set_ifs_timing(ah, chan);
        OS_REG_RMW_FIELD(
            ah, AR_PHY_FRAME_CTL, AR_PHY_FRAME_CTL_CF_OVERLAP_WINDOW, 0x3);
    }

    /* Configure MAC for 20/40 operation */
    ar9300_set_11n_mac2040(ah, macmode);

    /* global transmit timeout (25 TUs default)*/
    /* XXX - put this elsewhere??? */
    OS_REG_WRITE(ah, AR_GTXTO, 25 << AR_GTXTO_TIMEOUT_LIMIT_S);

    /* carrier sense timeout */
    OS_REG_WRITE(ah, AR_CST, 0xF << AR_CST_TIMEOUT_LIMIT_S);
}