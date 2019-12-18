#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int dummy; } ;
struct TYPE_3__ {scalar_t__ category; } ;
struct TYPE_4__ {TYPE_1__ action; } ;
struct ieee80211_mgmt {TYPE_2__ u; int /*<<< orphan*/  bssid; int /*<<< orphan*/  sa; int /*<<< orphan*/  da; } ;

/* Variables and functions */
 int IEEE80211_HDRLEN ; 
 scalar_t__ WLAN_ACTION_PUBLIC ; 
 int /*<<< orphan*/  wpas_p2p_rx_action (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  const*,size_t,int) ; 

__attribute__((used)) static void ap_public_action_rx(void *ctx, const u8 *buf, size_t len, int freq)
{
#ifdef CONFIG_P2P
	struct wpa_supplicant *wpa_s = ctx;
	const struct ieee80211_mgmt *mgmt;

	mgmt = (const struct ieee80211_mgmt *) buf;
	if (len < IEEE80211_HDRLEN + 1)
		return;
	if (mgmt->u.action.category != WLAN_ACTION_PUBLIC)
		return;
	wpas_p2p_rx_action(wpa_s, mgmt->da, mgmt->sa, mgmt->bssid,
			   mgmt->u.action.category,
			   buf + IEEE80211_HDRLEN + 1,
			   len - IEEE80211_HDRLEN - 1, freq);
#endif /* CONFIG_P2P */
}