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
typedef  scalar_t__ u8 ;
struct ieee80211_he_mu_edca_parameter_set {int dummy; } ;
struct hostapd_data {TYPE_2__* iface; } ;
struct TYPE_4__ {TYPE_1__* conf; } ;
struct TYPE_3__ {int /*<<< orphan*/  he_mu_edca; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WLAN_EID_EXTENSION ; 
 int /*<<< orphan*/  WLAN_EID_EXT_HE_MU_EDCA_PARAMS ; 
 int /*<<< orphan*/  os_memcpy (struct ieee80211_he_mu_edca_parameter_set*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__*,int) ; 

u8 * hostapd_eid_he_mu_edca_parameter_set(struct hostapd_data *hapd, u8 *eid)
{
	struct ieee80211_he_mu_edca_parameter_set *edca;
	u8 *pos;
	size_t i;

	pos = (u8 *) &hapd->iface->conf->he_mu_edca;
	for (i = 0; i < sizeof(*edca); i++) {
		if (pos[i])
			break;
	}
	if (i == sizeof(*edca))
		return eid; /* no MU EDCA Parameters configured */

	pos = eid;
	*pos++ = WLAN_EID_EXTENSION;
	*pos++ = 1 + sizeof(*edca);
	*pos++ = WLAN_EID_EXT_HE_MU_EDCA_PARAMS;

	edca = (struct ieee80211_he_mu_edca_parameter_set *) pos;
	os_memcpy(edca, &hapd->iface->conf->he_mu_edca, sizeof(*edca));

	wpa_hexdump(MSG_DEBUG, "HE: MU EDCA Parameter Set element",
		    pos, sizeof(*edca));

	pos += sizeof(*edca);

	return pos;
}