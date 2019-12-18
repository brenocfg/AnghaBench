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
struct wpa_ssid {int key_mgmt; int eapol_flags; int /*<<< orphan*/  owe_only; scalar_t__ mixed_cell; } ;
struct wpa_bss {int caps; } ;

/* Variables and functions */
 int EAPOL_FLAG_REQUIRE_KEY_BROADCAST ; 
 int EAPOL_FLAG_REQUIRE_KEY_UNICAST ; 
 int IEEE80211_CAP_PRIVACY ; 
 int WPA_KEY_MGMT_IEEE8021X_NO_WPA ; 
 int WPA_KEY_MGMT_OSEN ; 
 int WPA_KEY_MGMT_OWE ; 
 int WPA_KEY_MGMT_WPS ; 
 scalar_t__ has_wep_key (struct wpa_ssid*) ; 
 scalar_t__ wpa_key_mgmt_wpa (int) ; 

__attribute__((used)) static int wpa_supplicant_match_privacy(struct wpa_bss *bss,
					struct wpa_ssid *ssid)
{
	int privacy = 0;

	if (ssid->mixed_cell)
		return 1;

#ifdef CONFIG_WPS
	if (ssid->key_mgmt & WPA_KEY_MGMT_WPS)
		return 1;
#endif /* CONFIG_WPS */

#ifdef CONFIG_OWE
	if ((ssid->key_mgmt & WPA_KEY_MGMT_OWE) && !ssid->owe_only)
		return 1;
#endif /* CONFIG_OWE */

	if (has_wep_key(ssid))
		privacy = 1;

#ifdef IEEE8021X_EAPOL
	if ((ssid->key_mgmt & WPA_KEY_MGMT_IEEE8021X_NO_WPA) &&
	    ssid->eapol_flags & (EAPOL_FLAG_REQUIRE_KEY_UNICAST |
				 EAPOL_FLAG_REQUIRE_KEY_BROADCAST))
		privacy = 1;
#endif /* IEEE8021X_EAPOL */

	if (wpa_key_mgmt_wpa(ssid->key_mgmt))
		privacy = 1;

	if (ssid->key_mgmt & WPA_KEY_MGMT_OSEN)
		privacy = 1;

	if (bss->caps & IEEE80211_CAP_PRIVACY)
		return privacy;
	return !privacy;
}