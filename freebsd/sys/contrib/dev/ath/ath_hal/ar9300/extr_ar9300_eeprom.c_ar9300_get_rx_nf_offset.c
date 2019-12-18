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
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  nf_pwr ;
typedef  int /*<<< orphan*/  nf_cal ;
typedef  int int8_t ;
struct TYPE_4__ {int /*<<< orphan*/  channel; } ;
typedef  TYPE_1__ HAL_CHANNEL_INTERNAL ;

/* Variables and functions */
 TYPE_1__* AH_NULL ; 
 int NOISE_PWR_DBM_2_INT (int) ; 
 int OSPREY_MAX_CHAINS ; 
 int /*<<< orphan*/  OS_MEMZERO (int*,int) ; 
 int ar9300_noise_floor_cal_or_power_get (struct ath_hal*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* ath_hal_checkchannel (struct ath_hal*,struct ieee80211_channel*) ; 

int ar9300_get_rx_nf_offset(struct ath_hal *ah, struct ieee80211_channel *chan, int8_t *nf_pwr, int8_t *nf_cal) {
    HAL_CHANNEL_INTERNAL *ichan = ath_hal_checkchannel(ah, chan);
    int8_t rx_nf_pwr, rx_nf_cal;
    int i; 
    //HALASSERT(ichan);

    /* Fill 0 if valid internal channel is not found */
    if (ichan == AH_NULL) {
        OS_MEMZERO(nf_pwr, sizeof(nf_pwr[0])*OSPREY_MAX_CHAINS);
        OS_MEMZERO(nf_cal, sizeof(nf_cal[0])*OSPREY_MAX_CHAINS);
        return -1;
    }

    for (i = 0; i < OSPREY_MAX_CHAINS; i++) {
	    if ((rx_nf_pwr = ar9300_noise_floor_cal_or_power_get(ah, ichan->channel, i, 0)) == 1) {
	        nf_pwr[i] = 0;
	    } else {
	        //printk("%s: raw nf_pwr[%d] = %d\n", __func__, i, rx_nf_pwr);
            nf_pwr[i] = NOISE_PWR_DBM_2_INT(rx_nf_pwr);
	    }

	    if ((rx_nf_cal = ar9300_noise_floor_cal_or_power_get(ah, ichan->channel, i, 1)) == 1) {
	        nf_cal[i] = 0;
	    } else {
	        //printk("%s: raw nf_cal[%d] = %d\n", __func__, i, rx_nf_cal);
            nf_cal[i] = NOISE_PWR_DBM_2_INT(rx_nf_cal);
	    }
    }

    return 0;
}