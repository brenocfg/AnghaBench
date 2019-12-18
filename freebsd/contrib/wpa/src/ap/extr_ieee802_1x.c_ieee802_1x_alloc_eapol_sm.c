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
struct sta_info {int flags; int /*<<< orphan*/  radius_cui; int /*<<< orphan*/  identity; int /*<<< orphan*/  p2p_ie; int /*<<< orphan*/  wps_ie; int /*<<< orphan*/  addr; scalar_t__ wpa_sm; } ;
struct hostapd_data {int /*<<< orphan*/  eapol_auth; } ;
struct eapol_state_machine {int dummy; } ;

/* Variables and functions */
 int EAPOL_SM_FROM_PMKSA_CACHE ; 
 int EAPOL_SM_PREAUTH ; 
 int EAPOL_SM_USES_WPA ; 
 int WLAN_STA_PREAUTH ; 
 struct eapol_state_machine* eapol_auth_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sta_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_auth_sta_get_pmksa (scalar_t__) ; 

struct eapol_state_machine *
ieee802_1x_alloc_eapol_sm(struct hostapd_data *hapd, struct sta_info *sta)
{
	int flags = 0;
	if (sta->flags & WLAN_STA_PREAUTH)
		flags |= EAPOL_SM_PREAUTH;
	if (sta->wpa_sm) {
		flags |= EAPOL_SM_USES_WPA;
		if (wpa_auth_sta_get_pmksa(sta->wpa_sm))
			flags |= EAPOL_SM_FROM_PMKSA_CACHE;
	}
	return eapol_auth_alloc(hapd->eapol_auth, sta->addr, flags,
				sta->wps_ie, sta->p2p_ie, sta,
				sta->identity, sta->radius_cui);
}