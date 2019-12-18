#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
typedef  void* int16_t ;
struct TYPE_7__ {void** priv_nf; } ;
struct TYPE_8__ {TYPE_1__ base; void*** nf_cal_buffer; } ;
struct TYPE_11__ {TYPE_2__ nf_cal_hist; } ;
struct TYPE_9__ {int /*<<< orphan*/ ** nf_cal_buffer; } ;
struct TYPE_10__ {TYPE_3__ nf_cal_hist; } ;
typedef  TYPE_2__ HAL_NFCAL_HIST_FULL ;
typedef  TYPE_3__ HAL_CHAN_NFCAL_HIST ;
typedef  TYPE_4__ HAL_CHANNEL_INTERNAL ;

/* Variables and functions */
 TYPE_6__* AH_PRIVATE (struct ath_hal*) ; 
 int HAL_NF_CAL_HIST_LEN_FULL ; 
 int HAL_NUM_NF_READINGS ; 
 void* ar9300_limit_nf_range (struct ath_hal*,int /*<<< orphan*/ ) ; 

__attribute__((used)) inline static void
ar9300_reset_nf_hist_buff(struct ath_hal *ah, HAL_CHANNEL_INTERNAL *ichan)
{
    HAL_CHAN_NFCAL_HIST *h = &ichan->nf_cal_hist;
    HAL_NFCAL_HIST_FULL *home = &AH_PRIVATE(ah)->nf_cal_hist;
    int i;
    
    /* 
     * Copy the value for the channel in question into the home-channel
     * NF history buffer.  The channel NF is probably a value filled in by
     * a prior background channel scan, but if no scan has been done then
     * it is the nominal noise floor filled in by ath_hal_init_NF_buffer
     * for this chip and the channel's band.
     * Replicate this channel NF into all entries of the home-channel NF
     * history buffer.
     * If the channel NF was filled in by a channel scan, it has not had
     * bounds limits applied to it yet - do so now.  It is important to
     * apply bounds limits to the priv_nf value that gets loaded into the
     * WLAN chip's min_cca_pwr register field.  It is also necessary to
     * apply bounds limits to the nf_cal_buffer[] elements.  Since we are
     * replicating a single NF reading into all nf_cal_buffer elements,
     * if the single reading were above the CW_INT threshold, the CW_INT
     * check in ar9300_get_nf would immediately conclude that CW interference
     * is present, even though we're not supposed to set CW_INT unless
     * NF values are _consistently_ above the CW_INT threshold.
     * Applying the bounds limits to the nf_cal_buffer contents fixes this
     * problem.
     */
    for (i = 0; i < HAL_NUM_NF_READINGS; i ++) {
        int j;
        int16_t nf;
        /*
         * No need to set curr_index, since it already has a value in
         * the range [0..HAL_NF_CAL_HIST_LEN_FULL), and all nf_cal_buffer
         * values will be the same.
         */
        nf = ar9300_limit_nf_range(ah, h->nf_cal_buffer[0][i]);
        for (j = 0; j < HAL_NF_CAL_HIST_LEN_FULL; j++) {
            home->nf_cal_buffer[j][i] = nf;
        }
        AH_PRIVATE(ah)->nf_cal_hist.base.priv_nf[i] = nf;
    }
}