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
struct ieee80211_channel {int dummy; } ;
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_BT_COEX_STOMP_ALL ; 
 int /*<<< orphan*/  ath_btcoex_mci_update_wlan_channels (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_hal_btcoex_set_weights (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ath_btcoex_mci_enable(struct ath_softc *sc,
    const struct ieee80211_channel *chan)
{

	/*
	 * Always reconfigure stomp-all for now, so wlan wins.
	 *
	 * The default weights still don't allow beacons to win,
	 * so unless you set net.wlan.X.bmiss_max to something higher,
	 * net80211 will disconnect you during a HCI INQUIRY command.
	 *
	 * The longer-term solution is to dynamically adjust whether
	 * bmiss happens based on bluetooth requirements, and look at
	 * making the individual stomp bits configurable.
	 */
	ath_hal_btcoex_set_weights(sc->sc_ah, HAL_BT_COEX_STOMP_ALL);

	/*
	 * update wlan channels so the firmware knows what channels it
	 * can/can't use.
	 */
	ath_btcoex_mci_update_wlan_channels(sc);

	return (0);
}