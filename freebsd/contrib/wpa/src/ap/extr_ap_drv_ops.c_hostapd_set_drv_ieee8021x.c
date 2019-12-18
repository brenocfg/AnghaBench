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
struct wpa_bss_params {char const* ifname; int enabled; int wpa; int wpa_pairwise; int /*<<< orphan*/  ieee80211w; int /*<<< orphan*/  rsn_preauth; int /*<<< orphan*/  wpa_key_mgmt; int /*<<< orphan*/  wpa_group; int /*<<< orphan*/  ieee802_1x; } ;
struct hostapd_data {TYPE_1__* conf; } ;
typedef  int /*<<< orphan*/  params ;
struct TYPE_2__ {int wpa; int wpa_pairwise; int rsn_pairwise; int /*<<< orphan*/  ieee80211w; int /*<<< orphan*/  rsn_preauth; int /*<<< orphan*/  wpa_key_mgmt; int /*<<< orphan*/  wpa_group; int /*<<< orphan*/  ieee802_1x; } ;

/* Variables and functions */
 int WPA_PROTO_RSN ; 
 int WPA_PROTO_WPA ; 
 int hostapd_set_ieee8021x (struct hostapd_data*,struct wpa_bss_params*) ; 
 int /*<<< orphan*/  os_memset (struct wpa_bss_params*,int /*<<< orphan*/ ,int) ; 

int hostapd_set_drv_ieee8021x(struct hostapd_data *hapd, const char *ifname,
			      int enabled)
{
	struct wpa_bss_params params;
	os_memset(&params, 0, sizeof(params));
	params.ifname = ifname;
	params.enabled = enabled;
	if (enabled) {
		params.wpa = hapd->conf->wpa;
		params.ieee802_1x = hapd->conf->ieee802_1x;
		params.wpa_group = hapd->conf->wpa_group;
		if ((hapd->conf->wpa & (WPA_PROTO_WPA | WPA_PROTO_RSN)) ==
		    (WPA_PROTO_WPA | WPA_PROTO_RSN))
			params.wpa_pairwise = hapd->conf->wpa_pairwise |
				hapd->conf->rsn_pairwise;
		else if (hapd->conf->wpa & WPA_PROTO_RSN)
			params.wpa_pairwise = hapd->conf->rsn_pairwise;
		else if (hapd->conf->wpa & WPA_PROTO_WPA)
			params.wpa_pairwise = hapd->conf->wpa_pairwise;
		params.wpa_key_mgmt = hapd->conf->wpa_key_mgmt;
		params.rsn_preauth = hapd->conf->rsn_preauth;
#ifdef CONFIG_IEEE80211W
		params.ieee80211w = hapd->conf->ieee80211w;
#endif /* CONFIG_IEEE80211W */
	}
	return hostapd_set_ieee8021x(hapd, &params);
}