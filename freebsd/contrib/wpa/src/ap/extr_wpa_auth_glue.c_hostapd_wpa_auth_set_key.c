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
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {int last_tk_alg; int last_tk_key_idx; size_t last_tk_len; int /*<<< orphan*/  last_tk; } ;
struct hostapd_data {int last_igtk_alg; int last_igtk_key_idx; size_t last_igtk_len; int last_gtk_alg; int last_gtk_key_idx; size_t last_gtk_len; int /*<<< orphan*/  last_gtk; int /*<<< orphan*/  last_igtk; TYPE_1__* conf; } ;
typedef  enum wpa_alg { ____Placeholder_wpa_alg } wpa_alg ;
struct TYPE_2__ {char* iface; int /*<<< orphan*/  vlan; } ;

/* Variables and functions */
 int WPA_ALG_BIP_CMAC_256 ; 
 int WPA_ALG_BIP_GMAC_128 ; 
 int WPA_ALG_BIP_GMAC_256 ; 
 int WPA_ALG_IGTK ; 
 struct sta_info* ap_get_sta (struct hostapd_data*,int /*<<< orphan*/  const*) ; 
 int hostapd_drv_set_key (char const*,struct hostapd_data*,int,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 char* hostapd_get_vlan_id_ifname (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_broadcast_ether_addr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int hostapd_wpa_auth_set_key(void *ctx, int vlan_id, enum wpa_alg alg,
				    const u8 *addr, int idx, u8 *key,
				    size_t key_len)
{
	struct hostapd_data *hapd = ctx;
	const char *ifname = hapd->conf->iface;

	if (vlan_id > 0) {
		ifname = hostapd_get_vlan_id_ifname(hapd->conf->vlan, vlan_id);
		if (ifname == NULL)
			return -1;
	}

#ifdef CONFIG_TESTING_OPTIONS
	if (addr && !is_broadcast_ether_addr(addr)) {
		struct sta_info *sta;

		sta = ap_get_sta(hapd, addr);
		if (sta) {
			sta->last_tk_alg = alg;
			sta->last_tk_key_idx = idx;
			if (key)
				os_memcpy(sta->last_tk, key, key_len);
			sta->last_tk_len = key_len;
		}
#ifdef CONFIG_IEEE80211W
	} else if (alg == WPA_ALG_IGTK ||
		   alg == WPA_ALG_BIP_GMAC_128 ||
		   alg == WPA_ALG_BIP_GMAC_256 ||
		   alg == WPA_ALG_BIP_CMAC_256) {
		hapd->last_igtk_alg = alg;
		hapd->last_igtk_key_idx = idx;
		if (key)
			os_memcpy(hapd->last_igtk, key, key_len);
		hapd->last_igtk_len = key_len;
#endif /* CONFIG_IEEE80211W */
	} else {
		hapd->last_gtk_alg = alg;
		hapd->last_gtk_key_idx = idx;
		if (key)
			os_memcpy(hapd->last_gtk, key, key_len);
		hapd->last_gtk_len = key_len;
	}
#endif /* CONFIG_TESTING_OPTIONS */
	return hostapd_drv_set_key(ifname, hapd, alg, addr, idx, 1, NULL, 0,
				   key, key_len);
}