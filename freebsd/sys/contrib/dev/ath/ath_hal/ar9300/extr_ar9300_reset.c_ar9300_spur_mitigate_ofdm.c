#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int8_t ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal_9300 {int dummy; } ;
struct ath_hal {int dummy; } ;
struct TYPE_4__ {int channel; } ;
typedef  TYPE_1__ HAL_CHANNEL_INTERNAL ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHY_CHAN_SPUR_MASK ; 
 int /*<<< orphan*/  AR_PHY_CHAN_SPUR_MASK_CF_CHAN_MASK_A ; 
 int /*<<< orphan*/  AR_PHY_CHAN_SPUR_MASK_CF_CHAN_MASK_IDX_A ; 
 int /*<<< orphan*/  AR_PHY_GC_DYN2040_PRI_CH ; 
 int /*<<< orphan*/  AR_PHY_GEN_CTRL ; 
 int /*<<< orphan*/  AR_PHY_MODE ; 
 int /*<<< orphan*/  AR_PHY_MODE_DYNAMIC ; 
 int /*<<< orphan*/  AR_PHY_PILOT_SPUR_MASK ; 
 int /*<<< orphan*/  AR_PHY_PILOT_SPUR_MASK_CF_PILOT_MASK_A ; 
 int /*<<< orphan*/  AR_PHY_PILOT_SPUR_MASK_CF_PILOT_MASK_IDX_A ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_EXT ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_EXT_SPUR_SUBCHANNEL_SD ; 
 int /*<<< orphan*/  AR_PHY_SPUR_MASK_A ; 
 int /*<<< orphan*/  AR_PHY_SPUR_MASK_A_CF_PUNC_MASK_A ; 
 int /*<<< orphan*/  AR_PHY_SPUR_MASK_A_CF_PUNC_MASK_IDX_A ; 
 int /*<<< orphan*/  AR_PHY_SPUR_REG ; 
 int /*<<< orphan*/  AR_PHY_SPUR_REG_ENABLE_MASK_PPM ; 
 int /*<<< orphan*/  AR_PHY_SPUR_REG_ENABLE_NF_RSSI_SPUR_MIT ; 
 int /*<<< orphan*/  AR_PHY_SPUR_REG_EN_VIT_SPUR_RSSI ; 
 int /*<<< orphan*/  AR_PHY_SPUR_REG_MASK_RATE_CNTL ; 
 int /*<<< orphan*/  AR_PHY_SPUR_REG_SPUR_RSSI_THRESH ; 
 int /*<<< orphan*/  AR_PHY_TIMING11 ; 
 int /*<<< orphan*/  AR_PHY_TIMING11_SPUR_DELTA_PHASE ; 
 int /*<<< orphan*/  AR_PHY_TIMING11_SPUR_FREQ_SD ; 
 int /*<<< orphan*/  AR_PHY_TIMING11_USE_SPUR_FILTER_IN_AGC ; 
 int /*<<< orphan*/  AR_PHY_TIMING11_USE_SPUR_FILTER_IN_SELFCOR ; 
 int /*<<< orphan*/  AR_PHY_TIMING4 ; 
 int /*<<< orphan*/  AR_PHY_TIMING4_ENABLE_CHAN_MASK ; 
 int /*<<< orphan*/  AR_PHY_TIMING4_ENABLE_PILOT_MASK ; 
 int /*<<< orphan*/  AR_PHY_TIMING4_ENABLE_SPUR_FILTER ; 
 int /*<<< orphan*/  AR_PHY_TIMING4_ENABLE_SPUR_RSSI ; 
 int /*<<< orphan*/  AR_SREV_WASP (struct ath_hal*) ; 
 int FBIN2FREQ (scalar_t__,int) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (struct ieee80211_channel*) ; 
 scalar_t__ IS_CHAN_5GHZ (TYPE_1__*) ; 
 int OS_REG_READ_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int abs (int) ; 
 scalar_t__* ar9300_eeprom_get_spur_chans_ptr (struct ath_hal*,int) ; 
 TYPE_1__* ath_hal_checkchannel (struct ath_hal*,struct ieee80211_channel*) ; 

__attribute__((used)) static void
ar9300_spur_mitigate_ofdm(struct ath_hal *ah, struct ieee80211_channel *chan)
{ 
    int synth_freq;
    int range = 10;
    int freq_offset = 0;
    int spur_freq_sd = 0;
    int spur_subchannel_sd = 0;
    int spur_delta_phase = 0;
    int mask_index = 0;
    int i;
    int mode;
    u_int8_t* spur_chans_ptr;
    struct ath_hal_9300 *ahp;
    ahp = AH9300(ah);
    HAL_CHANNEL_INTERNAL *ichan = ath_hal_checkchannel(ah, chan);

    if (IS_CHAN_5GHZ(ichan)) {
        spur_chans_ptr = ar9300_eeprom_get_spur_chans_ptr(ah, 0);
        mode = 0;
    } else {
        spur_chans_ptr = ar9300_eeprom_get_spur_chans_ptr(ah, 1);
        mode = 1;
    }

    if (IEEE80211_IS_CHAN_HT40(chan)) {
        range = 19;
        if (OS_REG_READ_FIELD(ah, AR_PHY_GEN_CTRL, AR_PHY_GC_DYN2040_PRI_CH)
            == 0x0)
        {
            synth_freq = ichan->channel - 10;
        } else {
            synth_freq = ichan->channel + 10;
        }
    } else {
        range = 10;
        synth_freq = ichan->channel;
    }

    /* Clean all spur register fields */
    OS_REG_RMW_FIELD(ah, AR_PHY_TIMING4, AR_PHY_TIMING4_ENABLE_SPUR_FILTER, 0);
    OS_REG_RMW_FIELD(ah, AR_PHY_TIMING11, AR_PHY_TIMING11_SPUR_FREQ_SD, 0);
    OS_REG_RMW_FIELD(ah, AR_PHY_TIMING11, AR_PHY_TIMING11_SPUR_DELTA_PHASE, 0);
    OS_REG_RMW_FIELD(ah,
        AR_PHY_SFCORR_EXT, AR_PHY_SFCORR_EXT_SPUR_SUBCHANNEL_SD, 0);
    OS_REG_RMW_FIELD(ah,
        AR_PHY_TIMING11, AR_PHY_TIMING11_USE_SPUR_FILTER_IN_AGC, 0);
    OS_REG_RMW_FIELD(ah,
        AR_PHY_TIMING11, AR_PHY_TIMING11_USE_SPUR_FILTER_IN_SELFCOR, 0);
    OS_REG_RMW_FIELD(ah, AR_PHY_TIMING4, AR_PHY_TIMING4_ENABLE_SPUR_RSSI, 0);
    OS_REG_RMW_FIELD(ah, AR_PHY_SPUR_REG, AR_PHY_SPUR_REG_EN_VIT_SPUR_RSSI, 0);
    OS_REG_RMW_FIELD(ah,
        AR_PHY_SPUR_REG, AR_PHY_SPUR_REG_ENABLE_NF_RSSI_SPUR_MIT, 0);
    OS_REG_RMW_FIELD(ah, AR_PHY_SPUR_REG, AR_PHY_SPUR_REG_ENABLE_MASK_PPM, 0);
    OS_REG_RMW_FIELD(ah, AR_PHY_TIMING4, AR_PHY_TIMING4_ENABLE_PILOT_MASK, 0);
    OS_REG_RMW_FIELD(ah, AR_PHY_TIMING4, AR_PHY_TIMING4_ENABLE_CHAN_MASK, 0);
    OS_REG_RMW_FIELD(ah,
        AR_PHY_PILOT_SPUR_MASK, AR_PHY_PILOT_SPUR_MASK_CF_PILOT_MASK_IDX_A, 0);
    OS_REG_RMW_FIELD(ah,
        AR_PHY_SPUR_MASK_A, AR_PHY_SPUR_MASK_A_CF_PUNC_MASK_IDX_A, 0);
    OS_REG_RMW_FIELD(ah,
        AR_PHY_CHAN_SPUR_MASK, AR_PHY_CHAN_SPUR_MASK_CF_CHAN_MASK_IDX_A, 0);
    OS_REG_RMW_FIELD(ah,
        AR_PHY_PILOT_SPUR_MASK, AR_PHY_PILOT_SPUR_MASK_CF_PILOT_MASK_A, 0);
    OS_REG_RMW_FIELD(ah,
        AR_PHY_CHAN_SPUR_MASK, AR_PHY_CHAN_SPUR_MASK_CF_CHAN_MASK_A, 0);
    OS_REG_RMW_FIELD(ah,
        AR_PHY_SPUR_MASK_A, AR_PHY_SPUR_MASK_A_CF_PUNC_MASK_A, 0);
    OS_REG_RMW_FIELD(ah, AR_PHY_SPUR_REG, AR_PHY_SPUR_REG_MASK_RATE_CNTL, 0);

    i = 0;
    while (spur_chans_ptr[i] && i < 5) {
        freq_offset = FBIN2FREQ(spur_chans_ptr[i], mode) - synth_freq;
        if (abs(freq_offset) < range) {
            /*
            printf(
                "Spur Mitigation for OFDM: Synth Frequency = %d, "
                "Spur Frequency = %d\n",
                synth_freq, FBIN2FREQ(spur_chans_ptr[i], mode));
             */
            if (IEEE80211_IS_CHAN_HT40(chan)) {
                if (freq_offset < 0) {
                    if (OS_REG_READ_FIELD(
                        ah, AR_PHY_GEN_CTRL, AR_PHY_GC_DYN2040_PRI_CH) == 0x0)
                    {
                        spur_subchannel_sd = 1;
                    } else {
                        spur_subchannel_sd = 0;
                    }
                    spur_freq_sd = ((freq_offset + 10) << 9) / 11;
                } else {
                    if (OS_REG_READ_FIELD(ah,
                        AR_PHY_GEN_CTRL, AR_PHY_GC_DYN2040_PRI_CH) == 0x0)
                    {
                        spur_subchannel_sd = 0;
                    } else {
                        spur_subchannel_sd = 1;
                    }
                    spur_freq_sd = ((freq_offset - 10) << 9) / 11;
                }
                spur_delta_phase = (freq_offset << 17) / 5;
            } else {
                spur_subchannel_sd = 0;
                spur_freq_sd = (freq_offset << 9) / 11;
                spur_delta_phase = (freq_offset << 18) / 5;
            }
            spur_freq_sd = spur_freq_sd & 0x3ff;
            spur_delta_phase = spur_delta_phase & 0xfffff;
            /*
            printf(
                "spur_subchannel_sd = %d, spur_freq_sd = 0x%x, "
                "spur_delta_phase = 0x%x\n", spur_subchannel_sd,
                spur_freq_sd, spur_delta_phase);
             */

            /* OFDM Spur mitigation */
            OS_REG_RMW_FIELD(ah,
                AR_PHY_TIMING4, AR_PHY_TIMING4_ENABLE_SPUR_FILTER, 0x1);
            OS_REG_RMW_FIELD(ah,
                AR_PHY_TIMING11, AR_PHY_TIMING11_SPUR_FREQ_SD, spur_freq_sd);
            OS_REG_RMW_FIELD(ah,
                AR_PHY_TIMING11, AR_PHY_TIMING11_SPUR_DELTA_PHASE,
                spur_delta_phase);
            OS_REG_RMW_FIELD(ah,
                AR_PHY_SFCORR_EXT, AR_PHY_SFCORR_EXT_SPUR_SUBCHANNEL_SD,
                spur_subchannel_sd);
            OS_REG_RMW_FIELD(ah,
                AR_PHY_TIMING11, AR_PHY_TIMING11_USE_SPUR_FILTER_IN_AGC, 0x1);
            OS_REG_RMW_FIELD(ah,
                AR_PHY_TIMING11, AR_PHY_TIMING11_USE_SPUR_FILTER_IN_SELFCOR,
                0x1);
            OS_REG_RMW_FIELD(ah,
                AR_PHY_TIMING4, AR_PHY_TIMING4_ENABLE_SPUR_RSSI, 0x1);
            OS_REG_RMW_FIELD(ah,
                AR_PHY_SPUR_REG, AR_PHY_SPUR_REG_SPUR_RSSI_THRESH, 34);
            OS_REG_RMW_FIELD(ah,
                AR_PHY_SPUR_REG, AR_PHY_SPUR_REG_EN_VIT_SPUR_RSSI, 1);

            /*
             * Do not subtract spur power from noise floor for wasp.
             * This causes the maximum client test (on Veriwave) to fail
             * when run on spur channel (2464 MHz).
             * Refer to ev#82746 and ev#82744.
             */
            if (!AR_SREV_WASP(ah) && (OS_REG_READ_FIELD(ah, AR_PHY_MODE,
                                           AR_PHY_MODE_DYNAMIC) == 0x1)) {
                OS_REG_RMW_FIELD(ah, AR_PHY_SPUR_REG,
                    AR_PHY_SPUR_REG_ENABLE_NF_RSSI_SPUR_MIT, 1);
            }

            mask_index = (freq_offset << 4) / 5;
            if (mask_index < 0) {
                mask_index = mask_index - 1;
            }
            mask_index = mask_index & 0x7f;
            /*printf("Bin 0x%x\n", mask_index);*/

            OS_REG_RMW_FIELD(ah,
                AR_PHY_SPUR_REG, AR_PHY_SPUR_REG_ENABLE_MASK_PPM, 0x1);
            OS_REG_RMW_FIELD(ah,
                AR_PHY_TIMING4, AR_PHY_TIMING4_ENABLE_PILOT_MASK, 0x1);
            OS_REG_RMW_FIELD(ah,
                AR_PHY_TIMING4, AR_PHY_TIMING4_ENABLE_CHAN_MASK, 0x1);
            OS_REG_RMW_FIELD(ah,
                AR_PHY_PILOT_SPUR_MASK,
                AR_PHY_PILOT_SPUR_MASK_CF_PILOT_MASK_IDX_A, mask_index);
            OS_REG_RMW_FIELD(ah,
                AR_PHY_SPUR_MASK_A, AR_PHY_SPUR_MASK_A_CF_PUNC_MASK_IDX_A,
                mask_index);
            OS_REG_RMW_FIELD(ah,
                AR_PHY_CHAN_SPUR_MASK,
                AR_PHY_CHAN_SPUR_MASK_CF_CHAN_MASK_IDX_A, mask_index);
            OS_REG_RMW_FIELD(ah,
                AR_PHY_PILOT_SPUR_MASK, AR_PHY_PILOT_SPUR_MASK_CF_PILOT_MASK_A,
                0xc);
            OS_REG_RMW_FIELD(ah,
                AR_PHY_CHAN_SPUR_MASK, AR_PHY_CHAN_SPUR_MASK_CF_CHAN_MASK_A,
                0xc);
            OS_REG_RMW_FIELD(ah,
                AR_PHY_SPUR_MASK_A, AR_PHY_SPUR_MASK_A_CF_PUNC_MASK_A, 0xa0);
            OS_REG_RMW_FIELD(ah,
                AR_PHY_SPUR_REG, AR_PHY_SPUR_REG_MASK_RATE_CNTL, 0xff);
            /*
            printf("BB_timing_control_4 = 0x%x\n",
                OS_REG_READ(ah, AR_PHY_TIMING4));
            printf("BB_timing_control_11 = 0x%x\n",
                OS_REG_READ(ah, AR_PHY_TIMING11));
            printf("BB_ext_chan_scorr_thr = 0x%x\n",
                OS_REG_READ(ah, AR_PHY_SFCORR_EXT));
            printf("BB_spur_mask_controls = 0x%x\n",
                OS_REG_READ(ah, AR_PHY_SPUR_REG));
            printf("BB_pilot_spur_mask = 0x%x\n",
                OS_REG_READ(ah, AR_PHY_PILOT_SPUR_MASK));
            printf("BB_chan_spur_mask = 0x%x\n",
                OS_REG_READ(ah, AR_PHY_CHAN_SPUR_MASK));
            printf("BB_vit_spur_mask_A = 0x%x\n",
                OS_REG_READ(ah, AR_PHY_SPUR_MASK_A));
             */
            break;
        }
        i++;
    }
}