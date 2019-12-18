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
typedef  scalar_t__ uint32_t ;
struct ieee80211_node {scalar_t__* ni_mimo_rssi_ctl; int /*<<< orphan*/ * ni_mimo_noise_ctl; int /*<<< orphan*/  ni_mimo_chains; } ;
struct ieee80211_mimo_info {TYPE_1__* ch; } ;
typedef  int int32_t ;
struct TYPE_2__ {int* rssi; int /*<<< orphan*/ * noise; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_MAX_CHAINS ; 
 scalar_t__ IEEE80211_RSSI_DUMMY_MARKER ; 
 int IEEE80211_RSSI_GET (scalar_t__) ; 
 int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct ieee80211_mimo_info*,int) ; 

__attribute__((used)) static void
node_getmimoinfo(const struct ieee80211_node *ni,
	struct ieee80211_mimo_info *info)
{
	int i;
	uint32_t avgrssi;
	int32_t rssi;

	bzero(info, sizeof(*info));

	for (i = 0; i < MIN(IEEE80211_MAX_CHAINS, ni->ni_mimo_chains); i++) {
		/* Note: for now, just pri20 channel info */
		avgrssi = ni->ni_mimo_rssi_ctl[i];
		if (avgrssi == IEEE80211_RSSI_DUMMY_MARKER) {
			info->ch[i].rssi[0] = 0;
		} else {
			rssi = IEEE80211_RSSI_GET(avgrssi);
			info->ch[i].rssi[0] = rssi < 0 ? 0 : rssi > 127 ? 127 : rssi;
		}
		info->ch[i].noise[0] = ni->ni_mimo_noise_ctl[i];
	}

	/* XXX ext radios? */

	/* XXX EVM? */
}