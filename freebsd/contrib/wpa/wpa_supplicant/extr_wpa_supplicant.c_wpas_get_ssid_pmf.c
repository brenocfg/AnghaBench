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
struct wpa_supplicant {int drv_enc; TYPE_1__* conf; } ;
struct wpa_ssid {scalar_t__ ieee80211w; int key_mgmt; } ;
struct TYPE_2__ {scalar_t__ pmf; } ;

/* Variables and functions */
 scalar_t__ MGMT_FRAME_PROTECTION_DEFAULT ; 
 scalar_t__ MGMT_FRAME_PROTECTION_OPTIONAL ; 
 int NO_MGMT_FRAME_PROTECTION ; 
 int WPA_DRIVER_CAPA_ENC_BIP ; 
 int WPA_KEY_MGMT_IEEE8021X_NO_WPA ; 
 int WPA_KEY_MGMT_NONE ; 
 int WPA_KEY_MGMT_WPS ; 

int wpas_get_ssid_pmf(struct wpa_supplicant *wpa_s, struct wpa_ssid *ssid)
{
#ifdef CONFIG_IEEE80211W
	if (ssid == NULL || ssid->ieee80211w == MGMT_FRAME_PROTECTION_DEFAULT) {
		if (wpa_s->conf->pmf == MGMT_FRAME_PROTECTION_OPTIONAL &&
		    !(wpa_s->drv_enc & WPA_DRIVER_CAPA_ENC_BIP)) {
			/*
			 * Driver does not support BIP -- ignore pmf=1 default
			 * since the connection with PMF would fail and the
			 * configuration does not require PMF to be enabled.
			 */
			return NO_MGMT_FRAME_PROTECTION;
		}

		if (ssid &&
		    (ssid->key_mgmt &
		     ~(WPA_KEY_MGMT_NONE | WPA_KEY_MGMT_WPS |
		       WPA_KEY_MGMT_IEEE8021X_NO_WPA)) == 0) {
			/*
			 * Do not use the default PMF value for non-RSN networks
			 * since PMF is available only with RSN and pmf=2
			 * configuration would otherwise prevent connections to
			 * all open networks.
			 */
			return NO_MGMT_FRAME_PROTECTION;
		}

		return wpa_s->conf->pmf;
	}

	return ssid->ieee80211w;
#else /* CONFIG_IEEE80211W */
	return NO_MGMT_FRAME_PROTECTION;
#endif /* CONFIG_IEEE80211W */
}