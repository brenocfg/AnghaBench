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
struct wpa_supplicant {TYPE_1__* conf; } ;
struct wpa_ssid {int dummy; } ;
struct wpa_driver_capa {int key_mgmt; } ;
struct TYPE_2__ {scalar_t__ pmf; } ;

/* Variables and functions */
 scalar_t__ NO_MGMT_FRAME_PROTECTION ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_FT ; 
 scalar_t__ wpa_config_set (struct wpa_ssid*,char*,char const*,int /*<<< orphan*/ ) ; 
 int wpa_drv_get_capa (struct wpa_supplicant*,struct wpa_driver_capa*) ; 

__attribute__((used)) static int interworking_set_hs20_params(struct wpa_supplicant *wpa_s,
					struct wpa_ssid *ssid)
{
	const char *key_mgmt = NULL;
#ifdef CONFIG_IEEE80211R
	int res;
	struct wpa_driver_capa capa;

	res = wpa_drv_get_capa(wpa_s, &capa);
	if (res == 0 && capa.key_mgmt & WPA_DRIVER_CAPA_KEY_MGMT_FT) {
		key_mgmt = wpa_s->conf->pmf != NO_MGMT_FRAME_PROTECTION ?
			"WPA-EAP WPA-EAP-SHA256 FT-EAP" :
			"WPA-EAP FT-EAP";
	}
#endif /* CONFIG_IEEE80211R */

	if (!key_mgmt)
		key_mgmt = wpa_s->conf->pmf != NO_MGMT_FRAME_PROTECTION ?
			"WPA-EAP WPA-EAP-SHA256" : "WPA-EAP";
	if (wpa_config_set(ssid, "key_mgmt", key_mgmt, 0) < 0 ||
	    wpa_config_set(ssid, "proto", "RSN", 0) < 0 ||
	    wpa_config_set(ssid, "ieee80211w", "1", 0) < 0 ||
	    wpa_config_set(ssid, "pairwise", "CCMP", 0) < 0)
		return -1;
	return 0;
}