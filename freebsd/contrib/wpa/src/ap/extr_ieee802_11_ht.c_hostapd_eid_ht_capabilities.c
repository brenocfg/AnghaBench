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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_obss_scan_parameters {void* scan_activity_threshold; void* channel_transition_delay_factor; void* scan_active_total_per_channel; void* scan_passive_total_per_channel; void* scan_active_dwell; void* scan_passive_dwell; void* width_trigger_scan_interval; int /*<<< orphan*/  supported_mcs_set; int /*<<< orphan*/  a_mpdu_params; void* ht_capabilities_info; } ;
struct ieee80211_ht_capabilities {void* scan_activity_threshold; void* channel_transition_delay_factor; void* scan_active_total_per_channel; void* scan_passive_total_per_channel; void* scan_active_dwell; void* scan_passive_dwell; void* width_trigger_scan_interval; int /*<<< orphan*/  supported_mcs_set; int /*<<< orphan*/  a_mpdu_params; void* ht_capabilities_info; } ;
struct hostapd_data {TYPE_4__* iconf; TYPE_3__* iface; TYPE_1__* conf; } ;
struct TYPE_8__ {int ht_capab; int obss_interval; int /*<<< orphan*/  ieee80211n; } ;
struct TYPE_7__ {TYPE_2__* current_mode; } ;
struct TYPE_6__ {int /*<<< orphan*/  mcs_set; int /*<<< orphan*/  a_mpdu_params; } ;
struct TYPE_5__ {scalar_t__ disable_11n; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_HT_CAP ; 
 int /*<<< orphan*/  WLAN_EID_OVERLAPPING_BSS_SCAN_PARAMS ; 
 void* host_to_le16 (int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_memset (struct ieee80211_obss_scan_parameters*,int /*<<< orphan*/ ,int) ; 

u8 * hostapd_eid_ht_capabilities(struct hostapd_data *hapd, u8 *eid)
{
	struct ieee80211_ht_capabilities *cap;
	u8 *pos = eid;

	if (!hapd->iconf->ieee80211n || !hapd->iface->current_mode ||
	    hapd->conf->disable_11n)
		return eid;

	*pos++ = WLAN_EID_HT_CAP;
	*pos++ = sizeof(*cap);

	cap = (struct ieee80211_ht_capabilities *) pos;
	os_memset(cap, 0, sizeof(*cap));
	cap->ht_capabilities_info = host_to_le16(hapd->iconf->ht_capab);
	cap->a_mpdu_params = hapd->iface->current_mode->a_mpdu_params;
	os_memcpy(cap->supported_mcs_set, hapd->iface->current_mode->mcs_set,
		  16);

	/* TODO: ht_extended_capabilities (now fully disabled) */
	/* TODO: tx_bf_capability_info (now fully disabled) */
	/* TODO: asel_capabilities (now fully disabled) */

 	pos += sizeof(*cap);

	if (hapd->iconf->obss_interval) {
		struct ieee80211_obss_scan_parameters *scan_params;

		*pos++ = WLAN_EID_OVERLAPPING_BSS_SCAN_PARAMS;
		*pos++ = sizeof(*scan_params);

		scan_params = (struct ieee80211_obss_scan_parameters *) pos;
		os_memset(scan_params, 0, sizeof(*scan_params));
		scan_params->width_trigger_scan_interval =
			host_to_le16(hapd->iconf->obss_interval);

		/* Fill in default values for remaining parameters
		 * (IEEE Std 802.11-2012, 8.4.2.61 and MIB defval) */
		scan_params->scan_passive_dwell =
			host_to_le16(20);
		scan_params->scan_active_dwell =
			host_to_le16(10);
		scan_params->scan_passive_total_per_channel =
			host_to_le16(200);
		scan_params->scan_active_total_per_channel =
			host_to_le16(20);
		scan_params->channel_transition_delay_factor =
			host_to_le16(5);
		scan_params->scan_activity_threshold =
			host_to_le16(25);

		pos += sizeof(*scan_params);
	}

	return pos;
}