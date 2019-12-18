#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct hostapd_data {TYPE_3__* iface; TYPE_4__* conf; TYPE_1__* iconf; } ;
struct TYPE_6__ {scalar_t__ utf8_ssid; } ;
struct TYPE_8__ {int tdls; int wpa; int /*<<< orphan*/  wpa_key_mgmt; scalar_t__ mbo_enabled; scalar_t__ hs20; scalar_t__ ftm_responder; scalar_t__ ftm_initiator; TYPE_2__ ssid; scalar_t__ wnm_sleep_mode; scalar_t__ interworking; } ;
struct TYPE_7__ {int extended_capa_len; int* extended_capa_mask; int* extended_capa; } ;
struct TYPE_5__ {scalar_t__ obss_interval; } ;

/* Variables and functions */
 int TDLS_PROHIBIT ; 
 int TDLS_PROHIBIT_CHAN_SWITCH ; 
 int /*<<< orphan*/  WLAN_EID_EXT_CAPAB ; 
 int WPA_PROTO_RSN ; 
 int /*<<< orphan*/  hostapd_ext_capab_byte (struct hostapd_data*,int*,int) ; 
 scalar_t__ hostapd_sae_pw_id_in_use (TYPE_4__*) ; 
 int /*<<< orphan*/  wpa_key_mgmt_fils (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_key_mgmt_sae (int /*<<< orphan*/ ) ; 

u8 * hostapd_eid_ext_capab(struct hostapd_data *hapd, u8 *eid)
{
	u8 *pos = eid;
	u8 len = 0, i;

	if (hapd->conf->tdls & (TDLS_PROHIBIT | TDLS_PROHIBIT_CHAN_SWITCH))
		len = 5;
	if (len < 4 && hapd->conf->interworking)
		len = 4;
	if (len < 3 && hapd->conf->wnm_sleep_mode)
		len = 3;
	if (len < 1 && hapd->iconf->obss_interval)
		len = 1;
	if (len < 7 && hapd->conf->ssid.utf8_ssid)
		len = 7;
	if (len < 9 &&
	    (hapd->conf->ftm_initiator || hapd->conf->ftm_responder))
		len = 9;
#ifdef CONFIG_WNM_AP
	if (len < 4)
		len = 4;
#endif /* CONFIG_WNM_AP */
#ifdef CONFIG_HS20
	if (hapd->conf->hs20 && len < 6)
		len = 6;
#endif /* CONFIG_HS20 */
#ifdef CONFIG_MBO
	if (hapd->conf->mbo_enabled && len < 6)
		len = 6;
#endif /* CONFIG_MBO */
#ifdef CONFIG_FILS
	if ((!(hapd->conf->wpa & WPA_PROTO_RSN) ||
	     !wpa_key_mgmt_fils(hapd->conf->wpa_key_mgmt)) && len < 10)
		len = 10;
#endif /* CONFIG_FILS */
#ifdef CONFIG_SAE
	if (len < 11 && hapd->conf->wpa &&
	    wpa_key_mgmt_sae(hapd->conf->wpa_key_mgmt) &&
	    hostapd_sae_pw_id_in_use(hapd->conf))
		len = 11;
#endif /* CONFIG_SAE */
	if (len < hapd->iface->extended_capa_len)
		len = hapd->iface->extended_capa_len;
	if (len == 0)
		return eid;

	*pos++ = WLAN_EID_EXT_CAPAB;
	*pos++ = len;
	for (i = 0; i < len; i++, pos++) {
		hostapd_ext_capab_byte(hapd, pos, i);

		if (i < hapd->iface->extended_capa_len) {
			*pos &= ~hapd->iface->extended_capa_mask[i];
			*pos |= hapd->iface->extended_capa[i];
		}
	}

	while (len > 0 && eid[1 + len] == 0) {
		len--;
		eid[1] = len;
	}
	if (len == 0)
		return eid;

	return eid + 2 + len;
}