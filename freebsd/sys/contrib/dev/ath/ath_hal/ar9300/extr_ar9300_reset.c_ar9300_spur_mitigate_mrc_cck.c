#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int8_t ;
typedef  int u_int32_t ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int channel; } ;
typedef  TYPE_1__ HAL_CHANNEL_INTERNAL ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_AGC_CONTROL ; 
 int /*<<< orphan*/  AR_PHY_AGC_CONTROL_YCOK_MAX ; 
 int /*<<< orphan*/  AR_PHY_CCK_SPUR_MIT ; 
 int /*<<< orphan*/  AR_PHY_CCK_SPUR_MIT_CCK_SPUR_FREQ ; 
 int /*<<< orphan*/  AR_PHY_CCK_SPUR_MIT_SPUR_FILTER_TYPE ; 
 int /*<<< orphan*/  AR_PHY_CCK_SPUR_MIT_SPUR_RSSI_THR ; 
 int /*<<< orphan*/  AR_PHY_CCK_SPUR_MIT_USE_CCK_SPUR_MIT ; 
 int /*<<< orphan*/  AR_PHY_GC_DYN2040_PRI_CH ; 
 int /*<<< orphan*/  AR_PHY_GEN_CTRL ; 
 scalar_t__ AR_SREV_HORNET (struct ath_hal*) ; 
 scalar_t__ AR_SREV_JUPITER (struct ath_hal*) ; 
 scalar_t__ AR_SREV_POSEIDON (struct ath_hal*) ; 
 scalar_t__ AR_SREV_SCORPION (struct ath_hal*) ; 
 scalar_t__ AR_SREV_WASP (struct ath_hal*) ; 
 int FBIN2FREQ (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAL_FREQ_BAND_2GHZ ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (struct ieee80211_channel*) ; 
 int OSPREY_EEPROM_MODAL_SPURS ; 
 int OS_REG_READ_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__* ar9300_eeprom_get_spur_chans_ptr (struct ath_hal*,int) ; 
 TYPE_1__* ath_hal_checkchannel (struct ath_hal*,struct ieee80211_channel*) ; 

__attribute__((used)) static void
ar9300_spur_mitigate_mrc_cck(struct ath_hal *ah, struct ieee80211_channel *chan)
{
    int i;
    /* spur_freq_for_osprey - hardcoded by Systems team for now. */
    u_int32_t spur_freq_for_osprey[4] = { 2420, 2440, 2464, 2480 };
    u_int32_t spur_freq_for_jupiter[2] = { 2440, 2464};
    int cur_bb_spur, negative = 0, cck_spur_freq;
    u_int8_t* spur_fbin_ptr = NULL;
    int synth_freq;
    int range = 10;
    int max_spurcounts = OSPREY_EEPROM_MODAL_SPURS; 
    HAL_CHANNEL_INTERNAL *ichan = ath_hal_checkchannel(ah, chan);

    /*
     * Need to verify range +/- 10 MHz in control channel, otherwise spur
     * is out-of-band and can be ignored.
     */
    if (AR_SREV_HORNET(ah) || AR_SREV_POSEIDON(ah) ||
        AR_SREV_WASP(ah)  || AR_SREV_SCORPION(ah)) {
        spur_fbin_ptr = ar9300_eeprom_get_spur_chans_ptr(ah, 1);
        if (spur_fbin_ptr[0] == 0) {
            return;      /* No spur in the mode */
        }
        if (IEEE80211_IS_CHAN_HT40(chan)) {
            range = 19;
            if (OS_REG_READ_FIELD(ah, AR_PHY_GEN_CTRL, AR_PHY_GC_DYN2040_PRI_CH)
                == 0x0)
            {
                synth_freq = ichan->channel + 10;
            } else {
                synth_freq = ichan->channel - 10;
            }
        } else {
            range = 10;
            synth_freq = ichan->channel;
        }
    } else if(AR_SREV_JUPITER(ah)) {
        range = 5;
        max_spurcounts = 2; /* Hardcoded by Jupiter Systems team for now. */
        synth_freq = ichan->channel;
    } else {
        range = 10;
        max_spurcounts = 4; /* Hardcoded by Osprey Systems team for now. */
        synth_freq = ichan->channel;
    }

    for (i = 0; i < max_spurcounts; i++) {
        negative = 0;

        if (AR_SREV_HORNET(ah) || AR_SREV_POSEIDON(ah) ||
            AR_SREV_WASP(ah) || AR_SREV_SCORPION(ah)) {
            cur_bb_spur = 
                FBIN2FREQ(spur_fbin_ptr[i], HAL_FREQ_BAND_2GHZ) - synth_freq;
        } else if(AR_SREV_JUPITER(ah)) {
            cur_bb_spur = spur_freq_for_jupiter[i] - synth_freq;
        } else {
            cur_bb_spur = spur_freq_for_osprey[i] - synth_freq;
        }
        
        if (cur_bb_spur < 0) {
            negative = 1;
            cur_bb_spur = -cur_bb_spur;
        }
        if (cur_bb_spur < range) {
            cck_spur_freq = (int)((cur_bb_spur << 19) / 11);
            if (negative == 1) {
                cck_spur_freq = -cck_spur_freq;
            }
            cck_spur_freq = cck_spur_freq & 0xfffff;
            /*OS_REG_WRITE_field(ah, BB_agc_control.ycok_max, 0x7);*/
            OS_REG_RMW_FIELD(ah,
                AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_YCOK_MAX, 0x7);
            /*OS_REG_WRITE_field(ah, BB_cck_spur_mit.spur_rssi_thr, 0x7f);*/
            OS_REG_RMW_FIELD(ah,
                AR_PHY_CCK_SPUR_MIT, AR_PHY_CCK_SPUR_MIT_SPUR_RSSI_THR, 0x7f);
            /*OS_REG_WRITE(ah, BB_cck_spur_mit.spur_filter_type, 0x2);*/
            OS_REG_RMW_FIELD(ah,
                AR_PHY_CCK_SPUR_MIT, AR_PHY_CCK_SPUR_MIT_SPUR_FILTER_TYPE, 0x2);
            /*OS_REG_WRITE(ah, BB_cck_spur_mit.use_cck_spur_mit, 0x1);*/
            OS_REG_RMW_FIELD(ah,
                AR_PHY_CCK_SPUR_MIT, AR_PHY_CCK_SPUR_MIT_USE_CCK_SPUR_MIT, 0x1);
            /*OS_REG_WRITE(ah, BB_cck_spur_mit.cck_spur_freq, cck_spur_freq);*/
            OS_REG_RMW_FIELD(ah,
                AR_PHY_CCK_SPUR_MIT, AR_PHY_CCK_SPUR_MIT_CCK_SPUR_FREQ,
                cck_spur_freq);
            return; 
        }
    }

    /*OS_REG_WRITE(ah, BB_agc_control.ycok_max, 0x5);*/
    OS_REG_RMW_FIELD(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_YCOK_MAX, 0x5);
    /*OS_REG_WRITE(ah, BB_cck_spur_mit.use_cck_spur_mit, 0x0);*/
    OS_REG_RMW_FIELD(ah,
        AR_PHY_CCK_SPUR_MIT, AR_PHY_CCK_SPUR_MIT_USE_CCK_SPUR_MIT, 0x0);
    /*OS_REG_WRITE(ah, BB_cck_spur_mit.cck_spur_freq, 0x0);*/
    OS_REG_RMW_FIELD(ah,
        AR_PHY_CCK_SPUR_MIT, AR_PHY_CCK_SPUR_MIT_CCK_SPUR_FREQ, 0x0);
}