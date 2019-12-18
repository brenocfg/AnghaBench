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
typedef  int u_int16_t ;
struct TYPE_2__ {int halLow5GhzChan; int halHigh5GhzChan; int halLow2GhzChan; int halHigh2GhzChan; } ;
struct ath_hal_private {TYPE_1__ ah_caps; } ;
struct ath_hal {int dummy; } ;
typedef  TYPE_1__ HAL_CAPABILITIES ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 struct ath_hal_private* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int IEEE80211_CHAN_2GHZ ; 
 int IEEE80211_CHAN_5GHZ ; 

HAL_BOOL
ar9300_get_channel_edges(struct ath_hal *ah,
    u_int16_t flags, u_int16_t *low, u_int16_t *high)
{
    struct ath_hal_private *ahpriv = AH_PRIVATE(ah);
    HAL_CAPABILITIES *p_cap = &ahpriv->ah_caps;

    if (flags & IEEE80211_CHAN_5GHZ) {
        *low = p_cap->halLow5GhzChan;
        *high = p_cap->halHigh5GhzChan;
        return AH_TRUE;
    }
    if ((flags & IEEE80211_CHAN_2GHZ)) {
        *low = p_cap->halLow2GhzChan;
        *high = p_cap->halHigh2GhzChan;

        return AH_TRUE;
    }
    return AH_FALSE;
}