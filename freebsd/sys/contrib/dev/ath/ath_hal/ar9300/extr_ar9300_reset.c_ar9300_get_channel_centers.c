#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_channel {int dummy; } ;
struct ath_hal_9300 {scalar_t__ ah_ext_prot_spacing; } ;
struct ath_hal {int dummy; } ;
typedef  int int8_t ;
struct TYPE_6__ {scalar_t__ synth_center; scalar_t__ ext_center; scalar_t__ ctl_center; } ;
struct TYPE_5__ {scalar_t__ channel; } ;
typedef  TYPE_1__ HAL_CHANNEL_INTERNAL ;
typedef  TYPE_2__ CHAN_CENTERS ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  HALASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ HAL_HT_EXTPROTSPACING_20 ; 
 int HT40_CHANNEL_CENTER_SHIFT ; 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_HT40 (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40U (struct ieee80211_channel const*) ; 
 TYPE_1__* ath_hal_checkchannel (struct ath_hal*,struct ieee80211_channel const*) ; 

void
ar9300_get_channel_centers(struct ath_hal *ah, const struct ieee80211_channel *chan,
    CHAN_CENTERS *centers)
{
    int8_t      extoff;
    struct ath_hal_9300 *ahp = AH9300(ah);
    HAL_CHANNEL_INTERNAL *ichan = ath_hal_checkchannel(ah, chan);

    if (!IEEE80211_IS_CHAN_HT40(chan)) {
        centers->ctl_center = centers->ext_center =
        centers->synth_center = ichan->channel;
        return;
    }

    HALASSERT(IEEE80211_IS_CHAN_HT40(chan));

    /*
     * In 20/40 phy mode, the center frequency is
     * "between" the primary and extension channels.
     */
    if (IEEE80211_IS_CHAN_HT40U(chan)) {
        centers->synth_center = ichan->channel + HT40_CHANNEL_CENTER_SHIFT;
        extoff = 1;
    } else {
        centers->synth_center = ichan->channel - HT40_CHANNEL_CENTER_SHIFT;
        extoff = -1;
    }

    centers->ctl_center =
        centers->synth_center - (extoff * HT40_CHANNEL_CENTER_SHIFT);
    centers->ext_center =
        centers->synth_center +
        (extoff * ((ahp->ah_ext_prot_spacing == HAL_HT_EXTPROTSPACING_20) ?
            HT40_CHANNEL_CENTER_SHIFT : 15));
}