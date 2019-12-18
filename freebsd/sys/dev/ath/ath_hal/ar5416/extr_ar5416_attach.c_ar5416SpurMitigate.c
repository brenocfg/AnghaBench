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
typedef  int uint16_t ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  mask_p ;
typedef  int /*<<< orphan*/  mask_m ;
typedef  int int8_t ;
typedef  scalar_t__ HAL_BOOL ;

/* Variables and functions */
 int AR5416_EEPROM_MODAL_SPURS ; 
 int AR5416_SPUR_RSSI_THRESH ; 
 int AR_NO_SPUR ; 
 int const AR_PHY_BIN_MASK2_1 ; 
 int const AR_PHY_BIN_MASK2_2 ; 
 int const AR_PHY_BIN_MASK2_3 ; 
 int const AR_PHY_BIN_MASK2_4 ; 
 int const AR_PHY_BIN_MASK_1 ; 
 int const AR_PHY_BIN_MASK_2 ; 
 int const AR_PHY_BIN_MASK_3 ; 
#define  AR_PHY_CHANNEL_MASK_01_30 135 
#define  AR_PHY_CHANNEL_MASK_31_60 134 
 int const AR_PHY_MASK2_M_00_15 ; 
 int const AR_PHY_MASK2_M_16_30 ; 
 int const AR_PHY_MASK2_M_31_45 ; 
 int const AR_PHY_MASK2_P_15_01 ; 
 int const AR_PHY_MASK2_P_30_16 ; 
 int const AR_PHY_MASK2_P_45_31 ; 
 int const AR_PHY_MASK2_P_61_45 ; 
 int const AR_PHY_MASK_CTL ; 
#define  AR_PHY_PILOT_MASK_01_30 133 
#define  AR_PHY_PILOT_MASK_31_60 132 
 int const AR_PHY_SPUR_REG ; 
 int AR_PHY_SPUR_REG_ENABLE_MASK_PPM ; 
 int AR_PHY_SPUR_REG_ENABLE_VIT_SPUR_RSSI ; 
 int AR_PHY_SPUR_REG_MASK_RATE_CNTL ; 
 int AR_PHY_SPUR_REG_MASK_RATE_SELECT ; 
 int AR_PHY_SPUR_REG_SPUR_RSSI_THRESH ; 
#define  AR_PHY_TIMING10 131 
 int const AR_PHY_TIMING11 ; 
 int AR_PHY_TIMING11_SPUR_DELTA_PHASE ; 
 int AR_PHY_TIMING11_SPUR_FREQ_SD ; 
 int AR_PHY_TIMING11_USE_SPUR_IN_AGC ; 
#define  AR_PHY_TIMING7 130 
#define  AR_PHY_TIMING8 129 
#define  AR_PHY_TIMING9 128 
 int const AR_PHY_TIMING_CTRL4_CHAIN (int /*<<< orphan*/ ) ; 
 int AR_PHY_TIMING_CTRL4_ENABLE_CHAN_MASK ; 
 int AR_PHY_TIMING_CTRL4_ENABLE_PILOT_MASK ; 
 int AR_PHY_TIMING_CTRL4_ENABLE_SPUR_FILTER ; 
 int AR_PHY_TIMING_CTRL4_ENABLE_SPUR_RSSI ; 
 int const AR_PHY_VIT_MASK2_M_46_61 ; 
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  OS_MEMZERO (int*,int) ; 
 int OS_REG_READ (struct ath_hal*,int const) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int const,int) ; 
 int /*<<< orphan*/  OS_REG_WRITE_BUFFER_DISABLE (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_REG_WRITE_BUFFER_ENABLE (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_REG_WRITE_BUFFER_FLUSH (struct ath_hal*) ; 
 int SM (int,int) ; 
 size_t abs (int) ; 
 int ath_hal_getSpurChan (struct ath_hal*,int,scalar_t__) ; 
 int ath_hal_gethwchannel (struct ath_hal*,struct ieee80211_channel const*) ; 

__attribute__((used)) static void
ar5416SpurMitigate(struct ath_hal *ah, const struct ieee80211_channel *chan)
{
    uint16_t freq = ath_hal_gethwchannel(ah, chan);
    static const int pilot_mask_reg[4] = { AR_PHY_TIMING7, AR_PHY_TIMING8,
                AR_PHY_PILOT_MASK_01_30, AR_PHY_PILOT_MASK_31_60 };
    static const int chan_mask_reg[4] = { AR_PHY_TIMING9, AR_PHY_TIMING10,
                AR_PHY_CHANNEL_MASK_01_30, AR_PHY_CHANNEL_MASK_31_60 };
    static const int inc[4] = { 0, 100, 0, 0 };

    int bb_spur = AR_NO_SPUR;
    int bin, cur_bin;
    int spur_freq_sd;
    int spur_delta_phase;
    int denominator;
    int upper, lower, cur_vit_mask;
    int tmp, new;
    int i;

    int8_t mask_m[123];
    int8_t mask_p[123];
    int8_t mask_amt;
    int tmp_mask;
    int cur_bb_spur;
    HAL_BOOL is2GHz = IEEE80211_IS_CHAN_2GHZ(chan);

    OS_MEMZERO(mask_m, sizeof(mask_m));
    OS_MEMZERO(mask_p, sizeof(mask_p));

    /*
     * Need to verify range +/- 9.5 for static ht20, otherwise spur
     * is out-of-band and can be ignored.
     */
    /* XXX ath9k changes */
    for (i = 0; i < AR5416_EEPROM_MODAL_SPURS; i++) {
        cur_bb_spur = ath_hal_getSpurChan(ah, i, is2GHz);
        if (AR_NO_SPUR == cur_bb_spur)
            break;
        cur_bb_spur = cur_bb_spur - (freq * 10);
        if ((cur_bb_spur > -95) && (cur_bb_spur < 95)) {
            bb_spur = cur_bb_spur;
            break;
        }
    }
    if (AR_NO_SPUR == bb_spur)
        return;

    bin = bb_spur * 32;

    tmp = OS_REG_READ(ah, AR_PHY_TIMING_CTRL4_CHAIN(0));
    new = tmp | (AR_PHY_TIMING_CTRL4_ENABLE_SPUR_RSSI |
        AR_PHY_TIMING_CTRL4_ENABLE_SPUR_FILTER |
        AR_PHY_TIMING_CTRL4_ENABLE_CHAN_MASK |
        AR_PHY_TIMING_CTRL4_ENABLE_PILOT_MASK);

    OS_REG_WRITE_BUFFER_ENABLE(ah);

    OS_REG_WRITE(ah, AR_PHY_TIMING_CTRL4_CHAIN(0), new);

    new = (AR_PHY_SPUR_REG_MASK_RATE_CNTL |
        AR_PHY_SPUR_REG_ENABLE_MASK_PPM |
        AR_PHY_SPUR_REG_MASK_RATE_SELECT |
        AR_PHY_SPUR_REG_ENABLE_VIT_SPUR_RSSI |
        SM(AR5416_SPUR_RSSI_THRESH, AR_PHY_SPUR_REG_SPUR_RSSI_THRESH));
    OS_REG_WRITE(ah, AR_PHY_SPUR_REG, new);
    /*
     * Should offset bb_spur by +/- 10 MHz for dynamic 2040 MHz
     * config, no offset for HT20.
     * spur_delta_phase = bb_spur/40 * 2**21 for static ht20,
     * /80 for dyn2040.
     */
    spur_delta_phase = ((bb_spur * 524288) / 100) &
        AR_PHY_TIMING11_SPUR_DELTA_PHASE;
    /*
     * in 11A mode the denominator of spur_freq_sd should be 40 and
     * it should be 44 in 11G
     */
    denominator = IEEE80211_IS_CHAN_2GHZ(chan) ? 440 : 400;
    spur_freq_sd = ((bb_spur * 2048) / denominator) & 0x3ff;

    new = (AR_PHY_TIMING11_USE_SPUR_IN_AGC |
        SM(spur_freq_sd, AR_PHY_TIMING11_SPUR_FREQ_SD) |
        SM(spur_delta_phase, AR_PHY_TIMING11_SPUR_DELTA_PHASE));
    OS_REG_WRITE(ah, AR_PHY_TIMING11, new);


    /*
     * ============================================
     * pilot mask 1 [31:0] = +6..-26, no 0 bin
     * pilot mask 2 [19:0] = +26..+7
     *
     * channel mask 1 [31:0] = +6..-26, no 0 bin
     * channel mask 2 [19:0] = +26..+7
     */
    //cur_bin = -26;
    cur_bin = -6000;
    upper = bin + 100;
    lower = bin - 100;

    for (i = 0; i < 4; i++) {
        int pilot_mask = 0;
        int chan_mask  = 0;
        int bp         = 0;
        for (bp = 0; bp < 30; bp++) {
            if ((cur_bin > lower) && (cur_bin < upper)) {
                pilot_mask = pilot_mask | 0x1 << bp;
                chan_mask  = chan_mask | 0x1 << bp;
            }
            cur_bin += 100;
        }
        cur_bin += inc[i];
        OS_REG_WRITE(ah, pilot_mask_reg[i], pilot_mask);
        OS_REG_WRITE(ah, chan_mask_reg[i], chan_mask);
    }

    /* =================================================
     * viterbi mask 1 based on channel magnitude
     * four levels 0-3
     *  - mask (-27 to 27) (reg 64,0x9900 to 67,0x990c)
     *      [1 2 2 1] for -9.6 or [1 2 1] for +16
     *  - enable_mask_ppm, all bins move with freq
     *
     *  - mask_select,    8 bits for rates (reg 67,0x990c)
     *  - mask_rate_cntl, 8 bits for rates (reg 67,0x990c)
     *      choose which mask to use mask or mask2
     */

    /*
     * viterbi mask 2  2nd set for per data rate puncturing
     * four levels 0-3
     *  - mask_select, 8 bits for rates (reg 67)
     *  - mask (-27 to 27) (reg 98,0x9988 to 101,0x9994)
     *      [1 2 2 1] for -9.6 or [1 2 1] for +16
     */
    cur_vit_mask = 6100;
    upper        = bin + 120;
    lower        = bin - 120;

    for (i = 0; i < 123; i++) {
        if ((cur_vit_mask > lower) && (cur_vit_mask < upper)) {
            if ((abs(cur_vit_mask - bin)) < 75) {
                mask_amt = 1;
            } else {
                mask_amt = 0;
            }
            if (cur_vit_mask < 0) {
                mask_m[abs(cur_vit_mask / 100)] = mask_amt;
            } else {
                mask_p[cur_vit_mask / 100] = mask_amt;
            }
        }
        cur_vit_mask -= 100;
    }

    tmp_mask = (mask_m[46] << 30) | (mask_m[47] << 28)
          | (mask_m[48] << 26) | (mask_m[49] << 24)
          | (mask_m[50] << 22) | (mask_m[51] << 20)
          | (mask_m[52] << 18) | (mask_m[53] << 16)
          | (mask_m[54] << 14) | (mask_m[55] << 12)
          | (mask_m[56] << 10) | (mask_m[57] <<  8)
          | (mask_m[58] <<  6) | (mask_m[59] <<  4)
          | (mask_m[60] <<  2) | (mask_m[61] <<  0);
    OS_REG_WRITE(ah, AR_PHY_BIN_MASK_1, tmp_mask);
    OS_REG_WRITE(ah, AR_PHY_VIT_MASK2_M_46_61, tmp_mask);

    tmp_mask =             (mask_m[31] << 28)
          | (mask_m[32] << 26) | (mask_m[33] << 24)
          | (mask_m[34] << 22) | (mask_m[35] << 20)
          | (mask_m[36] << 18) | (mask_m[37] << 16)
          | (mask_m[48] << 14) | (mask_m[39] << 12)
          | (mask_m[40] << 10) | (mask_m[41] <<  8)
          | (mask_m[42] <<  6) | (mask_m[43] <<  4)
          | (mask_m[44] <<  2) | (mask_m[45] <<  0);
    OS_REG_WRITE(ah, AR_PHY_BIN_MASK_2, tmp_mask);
    OS_REG_WRITE(ah, AR_PHY_MASK2_M_31_45, tmp_mask);

    tmp_mask = (mask_m[16] << 30) | (mask_m[16] << 28)
          | (mask_m[18] << 26) | (mask_m[18] << 24)
          | (mask_m[20] << 22) | (mask_m[20] << 20)
          | (mask_m[22] << 18) | (mask_m[22] << 16)
          | (mask_m[24] << 14) | (mask_m[24] << 12)
          | (mask_m[25] << 10) | (mask_m[26] <<  8)
          | (mask_m[27] <<  6) | (mask_m[28] <<  4)
          | (mask_m[29] <<  2) | (mask_m[30] <<  0);
    OS_REG_WRITE(ah, AR_PHY_BIN_MASK_3, tmp_mask);
    OS_REG_WRITE(ah, AR_PHY_MASK2_M_16_30, tmp_mask);

    tmp_mask = (mask_m[ 0] << 30) | (mask_m[ 1] << 28)
          | (mask_m[ 2] << 26) | (mask_m[ 3] << 24)
          | (mask_m[ 4] << 22) | (mask_m[ 5] << 20)
          | (mask_m[ 6] << 18) | (mask_m[ 7] << 16)
          | (mask_m[ 8] << 14) | (mask_m[ 9] << 12)
          | (mask_m[10] << 10) | (mask_m[11] <<  8)
          | (mask_m[12] <<  6) | (mask_m[13] <<  4)
          | (mask_m[14] <<  2) | (mask_m[15] <<  0);
    OS_REG_WRITE(ah, AR_PHY_MASK_CTL, tmp_mask);
    OS_REG_WRITE(ah, AR_PHY_MASK2_M_00_15, tmp_mask);

    tmp_mask =             (mask_p[15] << 28)
          | (mask_p[14] << 26) | (mask_p[13] << 24)
          | (mask_p[12] << 22) | (mask_p[11] << 20)
          | (mask_p[10] << 18) | (mask_p[ 9] << 16)
          | (mask_p[ 8] << 14) | (mask_p[ 7] << 12)
          | (mask_p[ 6] << 10) | (mask_p[ 5] <<  8)
          | (mask_p[ 4] <<  6) | (mask_p[ 3] <<  4)
          | (mask_p[ 2] <<  2) | (mask_p[ 1] <<  0);
    OS_REG_WRITE(ah, AR_PHY_BIN_MASK2_1, tmp_mask);
    OS_REG_WRITE(ah, AR_PHY_MASK2_P_15_01, tmp_mask);

    tmp_mask =             (mask_p[30] << 28)
          | (mask_p[29] << 26) | (mask_p[28] << 24)
          | (mask_p[27] << 22) | (mask_p[26] << 20)
          | (mask_p[25] << 18) | (mask_p[24] << 16)
          | (mask_p[23] << 14) | (mask_p[22] << 12)
          | (mask_p[21] << 10) | (mask_p[20] <<  8)
          | (mask_p[19] <<  6) | (mask_p[18] <<  4)
          | (mask_p[17] <<  2) | (mask_p[16] <<  0);
    OS_REG_WRITE(ah, AR_PHY_BIN_MASK2_2, tmp_mask);
    OS_REG_WRITE(ah, AR_PHY_MASK2_P_30_16, tmp_mask);

    tmp_mask =             (mask_p[45] << 28)
          | (mask_p[44] << 26) | (mask_p[43] << 24)
          | (mask_p[42] << 22) | (mask_p[41] << 20)
          | (mask_p[40] << 18) | (mask_p[39] << 16)
          | (mask_p[38] << 14) | (mask_p[37] << 12)
          | (mask_p[36] << 10) | (mask_p[35] <<  8)
          | (mask_p[34] <<  6) | (mask_p[33] <<  4)
          | (mask_p[32] <<  2) | (mask_p[31] <<  0);
    OS_REG_WRITE(ah, AR_PHY_BIN_MASK2_3, tmp_mask);
    OS_REG_WRITE(ah, AR_PHY_MASK2_P_45_31, tmp_mask);

    tmp_mask = (mask_p[61] << 30) | (mask_p[60] << 28)
          | (mask_p[59] << 26) | (mask_p[58] << 24)
          | (mask_p[57] << 22) | (mask_p[56] << 20)
          | (mask_p[55] << 18) | (mask_p[54] << 16)
          | (mask_p[53] << 14) | (mask_p[52] << 12)
          | (mask_p[51] << 10) | (mask_p[50] <<  8)
          | (mask_p[49] <<  6) | (mask_p[48] <<  4)
          | (mask_p[47] <<  2) | (mask_p[46] <<  0);
    OS_REG_WRITE(ah, AR_PHY_BIN_MASK2_4, tmp_mask);
    OS_REG_WRITE(ah, AR_PHY_MASK2_P_61_45, tmp_mask);

    OS_REG_WRITE_BUFFER_FLUSH(ah);
    OS_REG_WRITE_BUFFER_DISABLE(ah);
}