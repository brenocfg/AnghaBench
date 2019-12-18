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
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal_9300 {int ah_rx_chainmask; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  nf_buf ;
typedef  scalar_t__ int16_t ;
struct TYPE_8__ {int curr_index; } ;
struct TYPE_9__ {scalar_t__** nf_cal_buffer; TYPE_1__ base; } ;
struct TYPE_11__ {TYPE_2__ nf_cal_hist; struct ieee80211_channel* ah_curchan; } ;
struct TYPE_10__ {TYPE_2__ nf_cal_hist; } ;
typedef  TYPE_2__ HAL_NFCAL_HIST_FULL ;
typedef  TYPE_3__ HAL_CHANNEL_INTERNAL ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 TYPE_3__* AH_NULL ; 
 TYPE_6__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  HALASSERT (TYPE_3__*) ; 
 int HAL_NF_CAL_HIST_LEN_FULL ; 
 int HAL_NF_CAL_HIST_LEN_SMALL ; 
 int HAL_NUM_NF_READINGS ; 
 int /*<<< orphan*/  OS_MEMZERO (scalar_t__*,int) ; 
 TYPE_3__* ath_hal_checkchannel (struct ath_hal*,struct ieee80211_channel*) ; 

void ar9300_chain_noise_floor(struct ath_hal *ah, int16_t *nf_buf,
    struct ieee80211_channel *chan, int is_scan)
{
    struct ath_hal_9300 *ahp = AH9300(ah);
    int i, nf_hist_len, recent_nf_index = 0;
    HAL_NFCAL_HIST_FULL *h;
    u_int8_t rx_chainmask = ahp->ah_rx_chainmask | (ahp->ah_rx_chainmask << 3);
    HAL_CHANNEL_INTERNAL *ichan = ath_hal_checkchannel(ah, chan); 
    HALASSERT(ichan);

#ifdef ATH_NF_PER_CHAN
    /* Fill 0 if valid internal channel is not found */
    if (ichan == AH_NULL) {
        OS_MEMZERO(nf_buf, sizeof(nf_buf[0])*HAL_NUM_NF_READINGS);
        return;
    }
    h = &ichan->nf_cal_hist;
    nf_hist_len = HAL_NF_CAL_HIST_LEN_FULL;
#else
    /*
     * If a scan is not in progress, then the most recent value goes
     * into ahpriv->nf_cal_hist.  If a scan is in progress, then
     * the most recent value goes into ichan->nf_cal_hist.
     * Thus, return the value from ahpriv->nf_cal_hist if there's
     * no scan, and if the specified channel is the current channel.
     * Otherwise, return the noise floor from ichan->nf_cal_hist.
     */
    if ((!is_scan) && chan == AH_PRIVATE(ah)->ah_curchan) {
        h = &AH_PRIVATE(ah)->nf_cal_hist;
        nf_hist_len = HAL_NF_CAL_HIST_LEN_FULL;
    } else {
        /* Fill 0 if valid internal channel is not found */
        if (ichan == AH_NULL) {
            OS_MEMZERO(nf_buf, sizeof(nf_buf[0])*HAL_NUM_NF_READINGS);
            return;
        }
       /*
        * It is okay to treat a HAL_NFCAL_HIST_SMALL struct as if it were a
        * HAL_NFCAL_HIST_FULL struct, as long as only the index 0 of the
        * nf_cal_buffer is used (nf_cal_buffer[0][0:HAL_NUM_NF_READINGS-1])
        */
        h = (HAL_NFCAL_HIST_FULL *) &ichan->nf_cal_hist;
        nf_hist_len = HAL_NF_CAL_HIST_LEN_SMALL;
    }
#endif
    /* Get most recently updated values from nf cal history buffer */
    recent_nf_index =
        (h->base.curr_index) ? h->base.curr_index - 1 : nf_hist_len - 1;

    for (i = 0; i < HAL_NUM_NF_READINGS; i++) {
        /* Fill 0 for unsupported chains */
        if (!(rx_chainmask & (1 << i))) {
            nf_buf[i] = 0;
            continue;
        }
        nf_buf[i] = h->nf_cal_buffer[recent_nf_index][i];
    }
}