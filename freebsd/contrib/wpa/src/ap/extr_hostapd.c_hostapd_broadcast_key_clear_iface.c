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
struct hostapd_data {TYPE_1__* conf; int /*<<< orphan*/  drv_priv; } ;
struct TYPE_2__ {scalar_t__ ieee80211w; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int NUM_WEP_KEYS ; 
 int /*<<< orphan*/  WPA_ALG_NONE ; 
 scalar_t__ hostapd_drv_set_key (char const*,struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*,int) ; 

__attribute__((used)) static void hostapd_broadcast_key_clear_iface(struct hostapd_data *hapd,
					      const char *ifname)
{
	int i;

	if (!ifname || !hapd->drv_priv)
		return;
	for (i = 0; i < NUM_WEP_KEYS; i++) {
		if (hostapd_drv_set_key(ifname, hapd, WPA_ALG_NONE, NULL, i,
					0, NULL, 0, NULL, 0)) {
			wpa_printf(MSG_DEBUG, "Failed to clear default "
				   "encryption keys (ifname=%s keyidx=%d)",
				   ifname, i);
		}
	}
#ifdef CONFIG_IEEE80211W
	if (hapd->conf->ieee80211w) {
		for (i = NUM_WEP_KEYS; i < NUM_WEP_KEYS + 2; i++) {
			if (hostapd_drv_set_key(ifname, hapd, WPA_ALG_NONE,
						NULL, i, 0, NULL,
						0, NULL, 0)) {
				wpa_printf(MSG_DEBUG, "Failed to clear "
					   "default mgmt encryption keys "
					   "(ifname=%s keyidx=%d)", ifname, i);
			}
		}
	}
#endif /* CONFIG_IEEE80211W */
}