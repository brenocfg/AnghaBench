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
typedef  int /*<<< orphan*/  u_int8_t ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal_9300 {int /*<<< orphan*/  ah_diversity_control; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;
typedef  int /*<<< orphan*/  HAL_ANT_SETTING ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 

HAL_BOOL
ar9300_set_antenna_switch(struct ath_hal *ah,
    HAL_ANT_SETTING settings, const struct ieee80211_channel *chan,
    u_int8_t *tx_chainmask, u_int8_t *rx_chainmask, u_int8_t *antenna_cfgd)
{
    struct ath_hal_9300 *ahp = AH9300(ah);

    /*
     * Owl does not support diversity or changing antennas.
     *
     * Instead this API and function are defined differently for AR9300.
     * To support Tablet PC's, this interface allows the system
     * to dramatically reduce the TX power on a particular chain.
     *
     * Based on the value of (redefined) diversity_control, the
     * reset code will decrease power on chain 0 or chain 1/2.
     *
     * Based on the value of bit 0 of antenna_switch_swap,
     * the mapping between OID call and chain is defined as:
     *  0:  map A -> 0, B -> 1;
     *  1:  map A -> 1, B -> 0;
     *
     * NOTE:
     *   The devices that use this OID should use a tx_chain_mask and
     *   tx_chain_select_legacy setting of 5 or 3 if ANTENNA_FIXED_B is
     *   used in order to ensure an active transmit antenna.  This
     *   API will allow the host to turn off the only transmitting
     *   antenna to ensure the antenna closest to the user's body is
     *   powered-down.
     */
    /*
     * Set antenna control for use during reset sequence by
     * ar9300_decrease_chain_power()
     */
    ahp->ah_diversity_control = settings;

    return AH_TRUE;
}